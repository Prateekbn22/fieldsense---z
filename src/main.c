#include <stdbool.h>
#include <stdint.h>

#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <zephyr/sys/util.h>

#include "env_stats.h"
#include "sensor_service.h"
#include "timing_metrics.h"
#include "state_model.h"

#define SENSOR_ACQ_THREAD_STACK_SIZE 2048
#define SENSOR_PROCESSING_THREAD_STACK_SIZE 2048

#define SENSOR_ACQ_THREAD_PRIORITY 5
#define SENSOR_PROCESSING_THREAD_PRIORITY 6

#define SENSOR_ACQ_PERIOD_MS 2000
#define SENSOR_SAMPLE_QUEUE_DEPTH 4
#define SENSOR_MISSED_PERIOD_TOLERANCE_MS 250
#define SENSOR_STALE_DATA_THRESHOLD_MS (SENSOR_ACQ_PERIOD_MS * 3U)

#define THREAD_START_DELAY_MS 1000

#define TEMP_MIN_MILLI_C  (-40000)
#define TEMP_MAX_MILLI_C  85000
#define PRESS_MIN_PA      30000
#define PRESS_MAX_PA      110000
#define RH_MIN_MILLI_PCT  0
#define RH_MAX_MILLI_PCT  100000

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

static void print_pressure_value(const char *label, int32_t pressure_pa)
{
	int32_t kpa_whole = pressure_pa / 1000;
	int32_t kpa_frac = pressure_pa % 1000;

	printk("%s: %d.%03d kPa (%d Pa)\n",
	       label,
	       kpa_whole,
	       kpa_frac,
	       pressure_pa);
}

static bool validate_sample_data(const struct sensor_sample *sample)
{
	if (!sample->valid) {
		return false;
	}

	if (sample->status != SENSOR_SAMPLE_STATUS_OK) {
		return false;
	}

	if (sample->driver_error != 0) {
		return false;
	}

	if (sample->temperature_milli_celsius < TEMP_MIN_MILLI_C ||
	    sample->temperature_milli_celsius > TEMP_MAX_MILLI_C) {
		return false;
	}

	if (sample->pressure_pa < PRESS_MIN_PA ||
	    sample->pressure_pa > PRESS_MAX_PA) {
		return false;
	}

	if (sample->humidity_supported) {
		if (sample->humidity_milli_percent_rh < RH_MIN_MILLI_PCT ||
		    sample->humidity_milli_percent_rh > RH_MAX_MILLI_PCT) {
			return false;
		}
	}

	return true;
}

static void print_processed_sample(const struct sensor_sample *sample)
{
	print_milli_value("Temperature",
			  sample->temperature_milli_celsius,
			  "deg C");

	print_pressure_value("Pressure", sample->pressure_pa);

	if (sample->humidity_supported) {
		print_milli_value("Humidity",
				  sample->humidity_milli_percent_rh,
				  "%RH");
	} else {
		printk("Humidity: not supported by current BMP280 hardware\n");
	}
}

static void print_milli_stats(const char *label,
			      const struct measurement_stats *stats,
			      const char *unit)
{
	if (!stats->has_value) {
		printk("[STATS] %s: no valid samples yet\n", label);
		return;
	}

	printk("[STATS] %s valid_count=%u, window_count=%u\n",
	       label,
	       (unsigned int)stats->valid_count,
	       (unsigned int)stats->window_count);

	print_milli_value("[STATS] latest", stats->latest, unit);
	print_milli_value("[STATS] minimum", stats->minimum, unit);
	print_milli_value("[STATS] maximum", stats->maximum, unit);
	print_milli_value("[STATS] moving_average", stats->moving_average, unit);
}

static void print_pressure_stats(const struct measurement_stats *stats)
{
	if (!stats->has_value) {
		printk("[STATS] Pressure: no valid samples yet\n");
		return;
	}

	printk("[STATS] Pressure valid_count=%u, window_count=%u\n",
	       (unsigned int)stats->valid_count,
	       (unsigned int)stats->window_count);

	print_pressure_value("[STATS] latest", stats->latest);
	print_pressure_value("[STATS] minimum", stats->minimum);
	print_pressure_value("[STATS] maximum", stats->maximum);
	print_pressure_value("[STATS] moving_average", stats->moving_average);
}

static void print_environmental_stats(const struct environmental_stats *stats)
{
	printk("[STATS] Supported channels: temperature, pressure\n");
	print_milli_stats("Temperature",
			  &stats->temperature_milli_celsius,
			  "deg C");
	print_pressure_stats(&stats->pressure_pa);
	printk("[STATS] Humidity statistics skipped: BMP280 hardware does not support humidity\n");
}

static void print_timing_metrics(const struct timing_metrics *metrics)
{
	if (metrics->interval_count == 0U) {
		printk("[TIME] Waiting for second sample before interval statistics are available\n");
	} else {
		printk("[TIME] interval_ms=%u, min_ms=%u, max_ms=%u, mean_ms=%u, scheduler_delay_ms=%d, missed_deadlines=%u\n",
		       metrics->latest_interval_ms,
		       metrics->minimum_interval_ms,
		       metrics->maximum_interval_ms,
		       metrics->mean_interval_ms,
		       metrics->latest_scheduler_delay_ms,
		       metrics->missed_deadline_count);
	}

	if (metrics->have_last_valid_sample) {
		printk("[TIME] last_valid_age_ms=%u, stale=%d, stale_threshold_ms=%u\n",
		       metrics->last_valid_sample_age_ms,
		       metrics->stale_data ? 1 : 0,
		       metrics->stale_threshold_ms);
	} else {
		printk("[TIME] No valid sample received yet\n");
	}
}

static void print_state_model(const struct state_model *model)
{
	printk("[STATE] node=%s, environment=%s\n",
	       node_health_state_to_string(model->node_health),
	       environmental_status_to_string(model->environmental_status));

	printk("[STATE] transitions: node=%u, environment=%u\n",
	       model->node_health_transition_count,
	       model->environmental_transition_count);

	printk("[STATE] counters: sensor_failures=%u, recovery_valid=%u, stale_events=%u, missed_deadlines=%u, queue_overflows=%u\n",
	       model->consecutive_sensor_failures,
	       model->consecutive_recovery_valid_samples,
	       model->stale_data_event_count,
	       model->missed_deadline_event_count,
	       model->queue_overflow_event_count);

	printk("[STATE] last_fault_reason=%s\n",
	       state_fault_reason_to_string(model->last_fault_reason));
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
	       (unsigned int)queue_full_count);
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
		uint32_t acq_start_ms;
uint32_t acq_end_ms;
uint32_t acq_execution_time_ms;

acq_start_ms = k_uptime_get_32();

ret = sensor_service_read(&sample);

acq_end_ms = k_uptime_get_32();
acq_execution_time_ms = acq_end_ms - acq_start_ms;

printk("[ACQ-TIME] sample=%u, execution_time_ms=%u\n",
       sample.sequence,
       acq_execution_time_ms);

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

static void sensor_processing_thread(void *p1, void *p2, void *p3)
{
	struct sensor_sample sample;
	struct sensor_sample latest_valid_sample;
	struct environmental_stats stats;
        struct timing_metrics timing;
        struct state_model system_state;

        uint32_t previous_missed_deadline_count = 0U;
        uint32_t previous_queue_full_count = 0U;
	bool latest_valid_available = false;
	uint32_t valid_sample_count = 0;
	uint32_t invalid_sample_count = 0;
	uint32_t sequence_gap_count = 0;
	uint32_t expected_sequence = 1;
	uint32_t processed_count = 0;
	int ret;

	ARG_UNUSED(p1);
	ARG_UNUSED(p2);
	ARG_UNUSED(p3);

	env_stats_init(&stats);
        timing_metrics_init(&timing,
		    SENSOR_ACQ_PERIOD_MS,
		    SENSOR_MISSED_PERIOD_TOLERANCE_MS,
		    SENSOR_STALE_DATA_THRESHOLD_MS);
         state_model_init(&system_state);

	printk("[PROC] Environmental processing thread started\n");
	printk("[PROC] Priority=%d, stack=%d bytes\n",
	       SENSOR_PROCESSING_THREAD_PRIORITY,
	       SENSOR_PROCESSING_THREAD_STACK_SIZE);
	printk("[PROC] Blocking on k_msgq_get(K_FOREVER)\n");

	while (1) {
		ret = k_msgq_get(&sensor_sample_msgq, &sample, K_FOREVER);
		if (ret != 0) {
			printk("[PROC] k_msgq_get() failed, ret=%d\n", ret);
			continue;
		}

		processed_count++;
        timing_metrics_update(&timing, &sample, k_uptime_get_32());
        bool sample_is_valid;
uint32_t current_missed_deadline_count;
uint32_t current_queue_full_count;
bool missed_deadline_event;
bool queue_overflow_event;
struct state_model_input state_input;

sample_is_valid = validate_sample_data(&sample);

current_missed_deadline_count = timing.missed_deadline_count;
current_queue_full_count = queue_full_count;

missed_deadline_event =
	current_missed_deadline_count > previous_missed_deadline_count;

queue_overflow_event =
	current_queue_full_count > previous_queue_full_count;

previous_missed_deadline_count = current_missed_deadline_count;
previous_queue_full_count = current_queue_full_count;

state_input.sample_received = true;
state_input.sample_valid = sample_is_valid;
state_input.temperature_milli_celsius = sample.temperature_milli_celsius;
state_input.pressure_pa = sample.pressure_pa;
state_input.stale_data = timing.stale_data;
state_input.missed_deadline_event = missed_deadline_event;
state_input.queue_overflow_event = queue_overflow_event;

state_model_update(&system_state, &state_input);
print_state_model(&system_state);

		if (sample.sequence != expected_sequence) {
			uint32_t missed = 0;

			if (sample.sequence > expected_sequence) {
				missed = sample.sequence - expected_sequence;
			}

			sequence_gap_count++;

			printk("\n[PROC] SEQUENCE GAP: expected=%u, received=%u, missed=%u, gap_count=%u\n",
			       expected_sequence,
			       sample.sequence,
			       missed,
			       sequence_gap_count);
		}

		expected_sequence = sample.sequence + 1;

		if (sample_is_valid) {
			latest_valid_sample = sample;
			latest_valid_available = true;
			valid_sample_count++;

			env_stats_update_from_sample(&stats, &sample);

			printk("\n[PROC] Processed valid sample %u at %u ms\n",
			       sample.sequence,
			       sample.timestamp_ms);

			print_processed_sample(&sample);
			print_environmental_stats(&stats);
                        print_timing_metrics(&timing);
		} else {
			invalid_sample_count++;

			printk("\n[PROC] Processed invalid sample %u at %u ms: status=%s, valid=%d, driver_error=%d\n",
			       sample.sequence,
			       sample.timestamp_ms,
			       sensor_sample_status_to_string(sample.status),
			       sample.valid ? 1 : 0,
			       sample.driver_error);
		}

		printk("[PROC] Counters: processed=%u, valid=%u, invalid=%u, sequence_gaps=%u, latest_valid=%s\n",
		       processed_count,
		       valid_sample_count,
		       invalid_sample_count,
		       sequence_gap_count,
		       latest_valid_available ? "yes" : "no");

		if (latest_valid_available) {
			printk("[PROC] Latest valid sample sequence=%u, timestamp=%u ms\n",
			       latest_valid_sample.sequence,
			       latest_valid_sample.timestamp_ms);
		}

		printk("[PROC] queue_used_after_get=%u, queue_free_after_get=%u\n",
		       (unsigned int)k_msgq_num_used_get(&sensor_sample_msgq),
		       (unsigned int)k_msgq_num_free_get(&sensor_sample_msgq));
	}
}

K_THREAD_DEFINE(sensor_acq_thread_id,
		SENSOR_ACQ_THREAD_STACK_SIZE,
		sensor_acquisition_thread,
		NULL, NULL, NULL,
		SENSOR_ACQ_THREAD_PRIORITY,
		0,
		THREAD_START_DELAY_MS);

K_THREAD_DEFINE(sensor_processing_thread_id,
		SENSOR_PROCESSING_THREAD_STACK_SIZE,
		sensor_processing_thread,
		NULL, NULL, NULL,
		SENSOR_PROCESSING_THREAD_PRIORITY,
		0,
		THREAD_START_DELAY_MS);

int main(void)
{
	bool self_test_passed;
        bool state_model_test_passed;

	printk("FieldSense-Z environmental statistics checkpoint\n");
	printk("main(): startup complete\n");
	printk("main(): statistics are calculated outside the hardware layer\n");

	printk("[SELFTEST] Controlled values: 22000, 23000, 21000, 24000, 25000, 26000 milli-C\n");
	printk("[SELFTEST] Window size: %u\n", ENV_STATS_WINDOW_SIZE);
	printk("[SELFTEST] Expected latest=26000, min=21000, max=26000, count=6, moving_average=23800\n");

	self_test_passed = env_stats_controlled_self_test();

	printk("[SELFTEST] Environmental stats controlled test: %s\n",
	       self_test_passed ? "PASS" : "FAIL");
        state_model_test_passed = state_model_controlled_self_test();

       printk("[SELFTEST] State model controlled test: %s\n",
       state_model_test_passed ? "PASS" : "FAIL");

	printk("Queue item size: %u bytes\n",
	       (unsigned int)sizeof(struct sensor_sample));
	printk("Queue depth: %u samples\n",
	       SENSOR_SAMPLE_QUEUE_DEPTH);
	printk("Queue storage estimate: %u bytes\n",
	       (unsigned int)(sizeof(struct sensor_sample) *
			      SENSOR_SAMPLE_QUEUE_DEPTH));

	printk("Statistics apply only to verified BMP280-supported channels: temperature and pressure\n");

	return 0;
}