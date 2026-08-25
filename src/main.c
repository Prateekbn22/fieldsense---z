#include <stdbool.h>
#include <stdint.h>

#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <zephyr/sys/util.h>

#include "sensor_service.h"

#define SENSOR_ACQ_THREAD_STACK_SIZE 2048
#define SENSOR_ACQ_THREAD_PRIORITY 5
#define SENSOR_ACQ_PERIOD_MS 2000

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

static void print_successful_sample(const struct sensor_sample *sample)
{
	printk("\n[ACQ] Sample %u at %u ms: status=%s\n",
	       sample->sequence,
	       sample->timestamp_ms,
	       sensor_sample_status_to_string(sample->status));

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

static void print_failed_sample(const struct sensor_sample *sample, int ret)
{
	printk("\n[ACQ] Sample %u at %u ms: status=%s, valid=%d, driver_error=%d, ret=%d\n",
	       sample->sequence,
	       sample->timestamp_ms,
	       sensor_sample_status_to_string(sample->status),
	       sample->valid ? 1 : 0,
	       sample->driver_error,
	       ret);

	printk("[ACQ] Recoverable read failure. Continuing to next period.\n");
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
		printk("[ACQ] Thread will keep running and retry reads periodically\n");
	} else {
		printk("[ACQ] Sensor device is ready: %s\n",
		       sensor_service_device_name());
	}

	while (1) {
		ret = sensor_service_read(&sample);

		if (ret == 0 && sample.valid) {
			print_successful_sample(&sample);
		} else {
			print_failed_sample(&sample, ret);
		}

		k_sleep(K_MSEC(SENSOR_ACQ_PERIOD_MS));
	}
}

K_THREAD_DEFINE(sensor_acq_thread_id,
		SENSOR_ACQ_THREAD_STACK_SIZE,
		sensor_acquisition_thread,
		NULL, NULL, NULL,
		SENSOR_ACQ_THREAD_PRIORITY,
		0,
		0);
int main(void)
{
	printk("FieldSense-Z RTOS sensor acquisition checkpoint\n");
	printk("main(): application startup complete\n");
	printk("main(): sensor acquisition is handled by a dedicated Zephyr thread\n");

	return 0;
}