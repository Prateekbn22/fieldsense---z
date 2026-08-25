#include <stdbool.h>
#include <stdint.h>

#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <zephyr/sys/util.h>

#include "sensor_service.h"

#define SENSOR_ACQ_THREAD_STACK_SIZE 2048
#define SENSOR_CONSUMER_THREAD_STACK_SIZE 2048

#define SENSOR_ACQ_THREAD_PRIORITY 5
#define SENSOR_CONSUMER_THREAD_PRIORITY 6

#define SENSOR_ACQ_PERIOD_MS 2000
#define SENSOR_SAMPLE_QUEUE_DEPTH 4

K_MSGQ_DEFINE(sensor_sample_msgq,
	      sizeof(struct sensor_sample),
	      SENSOR_SAMPLE_QUEUE_DEPTH,
	      4);

static uint32_t queue_full_count;

static int32_t abs_i32(int32_t value)
{
	return value < 0 ? -value : value;
}

static void print_milli_value(const char *label, int32_t milli_value,
			      const char *unit)
{
	int32_t whole;
	int32_t frac;

	if (milli_value < 0) {
		int32_t abs_value = abs_i32(milli_value);

		whole = abs_value / 1000;
		frac = abs_value % 1000;

		printk("%s: -%d.%03d %s\n", label, whole, frac, unit);
		return;
	}

	whole = milli_value / 1000;
	frac = milli_value % 1000;

	printk("%s: %d.%03d %s\n", label, whole, frac, unit);
}

static void print_pressure_pa(int32_t pressure_pa)
{
	int32_t kpa_whole = pressure_pa / 1000;
	int32_t kpa_frac = pressure_pa % 1000;

	printk("Pressure: %d.%03d kPa (%d Pa)\n",
	       kpa_whole, kpa_frac, pressure_pa);
}

static void print_consumed_sample(const struct sensor_sample *sample)
{
	printk("\n[CONSUMER] Consumed sample %u at %u ms: status=%s, valid=%d\n",
	       sample->sequence,
	       sample->timestamp_ms,
	       sensor_sample_status_to_string(sample->status),
	       sample->valid ? 1 : 0);

	if (!sample->valid) {
		printk("[CONSUMER] Sample read failed before queue publish: driver_error=%d\n",
		       sample->driver_error);
		return;
	}

	print_milli_value("Temperature",
			  sample->temperature_milli_celsius,
			  "deg C");

	print_pressure_pa(sample->pressure_pa);

	if (sample->humidity_supported) {
		print_milli_value("Humidity",
				  sample->humidity_milli_percent_rh,
				  "%RH");
	} else {
		printk("Humidity: not supported by current BMP280 hardware\n");
	}
}

static void publish_sample(const struct sensor_sample *sample)
{
	int ret;

	ret = k_msgq_put(&sensor_sample_msgq, sample, K_NO_WAIT);
	if (ret != 0) {
		queue_full_count++;

		printk("\n[ACQ] QUEUE FULL: sample %u was not enqueued, ret=%d\n",
		       sample->sequence,
		       ret);
		printk("[ACQ] queue_full_count=%u. Oldest queued samples preserved, newest sample dropped.\n",
		       queue_full_count);
		return;
	}

	printk("\n[ACQ] Published sample %u, valid=%d, queue_used=%u, queue_free=%u, queue_full_count=%u\n",
	       sample->sequence,
	       sample->valid ? 1 : 0,
	       (unsigned int)k_msgq_num_used_get(&sensor_sample_msgq),
	       (unsigned int)k_msgq_num_free_get(&sensor_sample_msgq),
	       queue_full_count);
}

static void sensor_acquisition_thread(void *p1, void *p2, void *p3)
{
	struct sensor_sample sample;
	int ret;

	ARG_UNUSED(p1);
	ARG_UNUSED(p2);
	ARG_UNUSED(p3);

	printk("[ACQ] Sensor acquisition thread started\n");
	printk("[ACQ] Priority=%d, stack=%d bytes, period=%d ms\n",
	       SENSOR_ACQ_THREAD_PRIORITY,
	       SENSOR_ACQ_THREAD_STACK_SIZE,
	       SENSOR_ACQ_PERIOD_MS);

	ret = sensor_service_init();
	if (ret != 0) {
		printk("[ACQ] sensor_service_init() failed, ret=%d\n", ret);
		printk("[ACQ] Thread will keep running and publish failure samples when reads fail\n");
	} else {
		printk("[ACQ] Sensor device is ready: %s\n",
		       sensor_service_device_name());
	}

	while (1) {
		ret = sensor_service_read(&sample);

		if (ret != 0 || !sample.valid) {
			printk("\n[ACQ] Read failure captured in sample %u: status=%s, driver_error=%d, ret=%d\n",
			       sample.sequence,
			       sensor_sample_status_to_string(sample.status),
			       sample.driver_error,
			       ret);
		}

		publish_sample(&sample);

		k_sleep(K_MSEC(SENSOR_ACQ_PERIOD_MS));
	}
}

static void temporary_consumer_thread(void *p1, void *p2, void *p3)
{
	struct sensor_sample sample;
	int ret;

	ARG_UNUSED(p1);
	ARG_UNUSED(p2);
	ARG_UNUSED(p3);

	printk("[CONSUMER] Temporary consumer thread started\n");
	printk("[CONSUMER] Blocking on k_msgq_get(K_FOREVER)\n");

	while (1) {
		ret = k_msgq_get(&sensor_sample_msgq, &sample, K_FOREVER);
		if (ret != 0) {
			printk("[CONSUMER] k_msgq_get() failed, ret=%d\n", ret);
			continue;
		}

		printk("[CONSUMER] queue_used_after_get=%u, queue_free_after_get=%u\n",
		       (unsigned int)k_msgq_num_used_get(&sensor_sample_msgq),
		       (unsigned int)k_msgq_num_free_get(&sensor_sample_msgq));

		print_consumed_sample(&sample);
	}
}

K_THREAD_DEFINE(sensor_acq_thread_id,
		SENSOR_ACQ_THREAD_STACK_SIZE,
		sensor_acquisition_thread,
		NULL, NULL, NULL,
		SENSOR_ACQ_THREAD_PRIORITY,
		0,
		0);

K_THREAD_DEFINE(sensor_consumer_thread_id,
		SENSOR_CONSUMER_THREAD_STACK_SIZE,
		temporary_consumer_thread,
		NULL, NULL, NULL,
		SENSOR_CONSUMER_THREAD_PRIORITY,
		0,
		0);

int main(void)
{
	printk("FieldSense-Z RTOS sensor message queue checkpoint\n");
	printk("main(): startup complete\n");
	printk("main(): acquisition publishes complete sensor_sample structures to k_msgq\n");
	printk("main(): temporary consumer receives complete samples from k_msgq\n");

	printk("Queue item size: %u bytes\n",
	       (unsigned int)sizeof(struct sensor_sample));
	printk("Queue depth: %u samples\n",
	       SENSOR_SAMPLE_QUEUE_DEPTH);
	printk("Queue storage estimate: %u bytes\n",
	       (unsigned int)(sizeof(struct sensor_sample) *
			      SENSOR_SAMPLE_QUEUE_DEPTH));

	printk("Queue-full policy: non-blocking publish, count event, preserve oldest queued samples, drop newest failed publish\n");

	return 0;
}