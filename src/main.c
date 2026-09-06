#include <errno.h>
#include <stdbool.h>
#include <stdint.h>

#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/sys/atomic.h>
#include <zephyr/sys/util.h>

#include "env_stats.h"
#include "sensor_service.h"
#include "timing_metrics.h"
#include "state_model.h"
#include "diagnostics.h"
#include "fault_injection.h"

LOG_MODULE_REGISTER(app, LOG_LEVEL_INF);

#define SENSOR_ACQ_THREAD_STACK_SIZE 2048
#define SENSOR_PROCESSING_THREAD_STACK_SIZE 2048

#define SENSOR_ACQ_THREAD_PRIORITY 5
#define SENSOR_PROCESSING_THREAD_PRIORITY 6

#define SENSOR_ACQ_PERIOD_MS 2000
#define SENSOR_SAMPLE_QUEUE_DEPTH 4

#define SENSOR_MISSED_PERIOD_TOLERANCE_MS 250
#define SENSOR_STALE_DATA_THRESHOLD_MS (SENSOR_ACQ_PERIOD_MS * 3U)

#define THREAD_START_DELAY_MS 1000

#define PERIODIC_SUMMARY_SAMPLE_COUNT 10U

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

static atomic_t queue_full_count;

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

static void publish_sample(const struct sensor_sample *sample)
{
	int ret;

	ret = k_msgq_put(&sensor_sample_msgq, sample, K_NO_WAIT);
	if (ret != 0) {
		atomic_inc(&queue_full_count);

		LOG_ERR("queue overflow: sample=%u ret=%d queue_full_count=%u policy=drop_newest_preserve_oldest",
			(unsigned int)sample->sequence,
			ret,
			(unsigned int)atomic_get(&queue_full_count));
		return;
	}

	LOG_DBG("published sample=%u valid=%d queue_used=%u queue_free=%u",
		(unsigned int)sample->sequence,
		sample->valid ? 1 : 0,
		(unsigned int)k_msgq_num_used_get(&sensor_sample_msgq),
		(unsigned int)k_msgq_num_free_get(&sensor_sample_msgq));
}

static void log_health_transition(enum node_health_state previous_health,
				  const struct state_model *system_state)
{
	if (system_state->node_health == NODE_HEALTH_FAULT) {
		LOG_ERR("health transition: %s -> %s reason=%s",
			node_health_state_to_string(previous_health),
			node_health_state_to_string(system_state->node_health),
			state_fault_reason_to_string(system_state->last_fault_reason));
	} else if (system_state->node_health == NODE_HEALTH_WARNING) {
		LOG_WRN("health transition: %s -> %s reason=%s",
			node_health_state_to_string(previous_health),
			node_health_state_to_string(system_state->node_health),
			state_fault_reason_to_string(system_state->last_fault_reason));
	} else {
		LOG_INF("health transition: %s -> %s",
			node_health_state_to_string(previous_health),
			node_health_state_to_string(system_state->node_health));
	}
}

static void log_environment_transition(
	enum environmental_status_state previous_environment,
	const struct state_model *system_state)
{
	if (system_state->environmental_status == ENV_STATUS_HIGH_TEMPERATURE ||
	    system_state->environmental_status == ENV_STATUS_PRESSURE_ALERT) {
		LOG_WRN("environment transition: %s -> %s",
			environmental_status_to_string(previous_environment),
			environmental_status_to_string(
				system_state->environmental_status));
	} else {
		LOG_INF("environment transition: %s -> %s",
			environmental_status_to_string(previous_environment),
			environmental_status_to_string(
				system_state->environmental_status));
	}
}

static void log_periodic_summary(
	uint32_t processed_count,
	uint32_t valid_sample_count,
	uint32_t invalid_sample_count,
	uint32_t sequence_gap_count,
	const struct sensor_sample *latest_valid_sample,
	bool latest_valid_available,
	const struct environmental_stats *stats,
	const struct timing_metrics *timing,
	const struct state_model *system_state)
{
	if (!latest_valid_available) {
		LOG_INF("summary: processed=%u valid=%u invalid=%u sequence_gaps=%u queue_full=%u health=%s environment=%s latest_valid=no missed_deadlines=%u stale=%d",
			(unsigned int)processed_count,
			(unsigned int)valid_sample_count,
			(unsigned int)invalid_sample_count,
			(unsigned int)sequence_gap_count,
			(unsigned int)atomic_get(&queue_full_count),
			node_health_state_to_string(system_state->node_health),
			environmental_status_to_string(
				system_state->environmental_status),
			(unsigned int)timing->missed_deadline_count,
			timing->stale_data ? 1 : 0);
		return;
	}

	LOG_INF("summary: processed=%u valid=%u invalid=%u sequence_gaps=%u queue_full=%u health=%s environment=%s latest_seq=%u temp_mC=%d pressure_pa=%d interval_mean_ms=%u missed_deadlines=%u stale=%d",
		(unsigned int)processed_count,
		(unsigned int)valid_sample_count,
		(unsigned int)invalid_sample_count,
		(unsigned int)sequence_gap_count,
		(unsigned int)atomic_get(&queue_full_count),
		node_health_state_to_string(system_state->node_health),
		environmental_status_to_string(system_state->environmental_status),
		(unsigned int)latest_valid_sample->sequence,
		(int)latest_valid_sample->temperature_milli_celsius,
		(int)latest_valid_sample->pressure_pa,
		(unsigned int)timing->mean_interval_ms,
		(unsigned int)timing->missed_deadline_count,
		timing->stale_data ? 1 : 0);

	LOG_INF("stats: temp_latest_mC=%d temp_min_mC=%d temp_max_mC=%d temp_avg_mC=%d pressure_latest_pa=%d pressure_min_pa=%d pressure_max_pa=%d pressure_avg_pa=%d",
		(int)stats->temperature_milli_celsius.latest,
		(int)stats->temperature_milli_celsius.minimum,
		(int)stats->temperature_milli_celsius.maximum,
		(int)stats->temperature_milli_celsius.moving_average,
		(int)stats->pressure_pa.latest,
		(int)stats->pressure_pa.minimum,
		(int)stats->pressure_pa.maximum,
		(int)stats->pressure_pa.moving_average);
}

static void apply_fault_injection_to_sample(struct sensor_sample *sample,
					    int *ret)
{
	uint32_t mask;
	uint32_t now_ms;

	mask = fault_injection_get_mask();
	now_ms = k_uptime_get_32();

	if ((mask & FAULT_INJECTION_SENSOR_READ_FAILURE) != 0U) {
		sample->timestamp_ms = now_ms;
		sample->valid = false;
		sample->status = SENSOR_SAMPLE_STATUS_FETCH_FAILED;
		sample->driver_error = -EIO;
		*ret = -EIO;

		LOG_WRN("injection active: sensor-read-failure sample=%u",
			(unsigned int)sample->sequence);
		return;
	}

	if ((mask & FAULT_INJECTION_INVALID_MEASUREMENT) != 0U) {
		sample->timestamp_ms = now_ms;
		sample->valid = true;
		sample->status = SENSOR_SAMPLE_STATUS_OK;
		sample->driver_error = 0;
		sample->temperature_milli_celsius =
			FAULT_INJECTION_INVALID_TEMP_MILLI_C;
		sample->pressure_pa =
			FAULT_INJECTION_INVALID_PRESSURE_PA;
		*ret = 0;

		LOG_WRN("injection active: invalid-measurement sample=%u temp_mC=%d pressure_pa=%d",
			(unsigned int)sample->sequence,
			(int)sample->temperature_milli_celsius,
			(int)sample->pressure_pa);
	}

	if ((mask & FAULT_INJECTION_NORMAL_ENVIRONMENT) != 0U) {
		sample->timestamp_ms = now_ms;
		sample->valid = true;
		sample->status = SENSOR_SAMPLE_STATUS_OK;
		sample->driver_error = 0;
		sample->temperature_milli_celsius =
			FAULT_INJECTION_NORMAL_TEMP_MILLI_C;
		sample->pressure_pa =
			FAULT_INJECTION_NORMAL_PRESSURE_PA;
		sample->humidity_supported = false;
		sample->humidity_milli_percent_rh = 0;
		*ret = 0;

		LOG_WRN("injection active: normal-environment sample=%u temp_mC=%d pressure_pa=%d",
			(unsigned int)sample->sequence,
			(int)sample->temperature_milli_celsius,
			(int)sample->pressure_pa);
	}

	if ((mask & FAULT_INJECTION_STALE_PUBLICATION) != 0U) {
		sample->timestamp_ms = now_ms - FAULT_INJECTION_STALE_AGE_MS;

		LOG_WRN("injection active: stale-publication sample=%u age_ms=%u",
			(unsigned int)sample->sequence,
			(unsigned int)FAULT_INJECTION_STALE_AGE_MS);
	}
}

static void sensor_acquisition_thread(void *p1, void *p2, void *p3)
{
	struct sensor_sample sample;
	int ret;

	k_thread_name_set(k_current_get(), "fieldsense_acq");

	ARG_UNUSED(p1);
	ARG_UNUSED(p2);
	ARG_UNUSED(p3);

	LOG_INF("acquisition thread started: priority=%d stack=%d period_ms=%d",
		SENSOR_ACQ_THREAD_PRIORITY,
		SENSOR_ACQ_THREAD_STACK_SIZE,
		SENSOR_ACQ_PERIOD_MS);

	ret = sensor_service_init();
	if (ret != 0) {
		LOG_WRN("sensor service init failed ret=%d; acquisition will continue and publish failure samples",
			ret);
	} else {
		LOG_INF("sensor service ready: device=%s",
			sensor_service_device_name());
	}

	while (1) {
		uint32_t acq_start_ms;
		uint32_t acq_end_ms;
		uint32_t acq_execution_time_ms;

		acq_start_ms = k_uptime_get_32();

		ret = sensor_service_read(&sample);

		apply_fault_injection_to_sample(&sample, &ret);

		acq_end_ms = k_uptime_get_32();
		acq_execution_time_ms = acq_end_ms - acq_start_ms;

		LOG_DBG("acquisition timing: sample=%u execution_time_ms=%u",
			(unsigned int)sample.sequence,
			(unsigned int)acq_execution_time_ms);

		if (ret != 0 || !sample.valid) {
			LOG_WRN("sensor read failure captured: sample=%u status=%s driver_error=%d ret=%d",
				(unsigned int)sample.sequence,
				sensor_sample_status_to_string(sample.status),
				sample.driver_error,
				ret);
		}

		publish_sample(&sample);

		if (fault_injection_is_active(FAULT_INJECTION_QUEUE_PRESSURE)) {
			for (uint32_t i = 0U;
			     i < FAULT_INJECTION_QUEUE_PRESSURE_BURST_COUNT;
			     i++) {
				LOG_WRN("injection active: queue-pressure burst=%u sample=%u",
					(unsigned int)(i + 1U),
					(unsigned int)sample.sequence);

				publish_sample(&sample);
			}
		}

		k_sleep(K_MSEC(SENSOR_ACQ_PERIOD_MS));
	}
}

static void sensor_processing_thread(void *p1, void *p2, void *p3)
{
	struct sensor_sample sample;
	struct sensor_sample latest_valid_sample = {0};
	struct environmental_stats stats;
	struct timing_metrics timing;
	struct state_model system_state;

	bool latest_valid_available = false;
	bool previous_stale_data = false;

	uint32_t previous_missed_deadline_count = 0U;
	uint32_t previous_queue_full_count = 0U;

	uint32_t valid_sample_count = 0U;
	uint32_t invalid_sample_count = 0U;
	uint32_t sequence_gap_count = 0U;
	uint32_t expected_sequence = 1U;
	uint32_t processed_count = 0U;

	int ret;

	k_thread_name_set(k_current_get(), "fieldsense_proc");

	ARG_UNUSED(p1);
	ARG_UNUSED(p2);
	ARG_UNUSED(p3);

	env_stats_init(&stats);

	timing_metrics_init(&timing,
			    SENSOR_ACQ_PERIOD_MS,
			    SENSOR_MISSED_PERIOD_TOLERANCE_MS,
			    SENSOR_STALE_DATA_THRESHOLD_MS);

	state_model_init(&system_state);

	LOG_INF("processing thread started: priority=%d stack=%d",
		SENSOR_PROCESSING_THREAD_PRIORITY,
		SENSOR_PROCESSING_THREAD_STACK_SIZE);
	LOG_INF("processing thread blocking on k_msgq_get(K_FOREVER)");

	while (1) {
		bool sample_is_valid;
		uint32_t current_missed_deadline_count;
		uint32_t current_queue_full_count;
		bool missed_deadline_event;
		bool queue_overflow_event;
		enum node_health_state previous_health;
		enum environmental_status_state previous_environment;
		struct state_model_input state_input;

		ret = k_msgq_get(&sensor_sample_msgq, &sample, K_FOREVER);
		if (ret != 0) {
			LOG_ERR("k_msgq_get failed ret=%d", ret);
			continue;
		}

		if (diagnostics_reset_stats_requested_take()) {
			env_stats_init(&stats);

			timing_metrics_init(&timing,
					    SENSOR_ACQ_PERIOD_MS,
					    SENSOR_MISSED_PERIOD_TOLERANCE_MS,
					    SENSOR_STALE_DATA_THRESHOLD_MS);

			latest_valid_sample = (struct sensor_sample){0};
			latest_valid_available = false;

			valid_sample_count = 0U;
			invalid_sample_count = 0U;
			sequence_gap_count = 0U;
			processed_count = 0U;
			expected_sequence = sample.sequence;

			atomic_set(&queue_full_count, 0);

			previous_missed_deadline_count =
				timing.missed_deadline_count;
			previous_queue_full_count = 0U;
			previous_stale_data = false;

			LOG_INF("diagnostic statistics reset applied");
		}

		if (fault_injection_is_active(FAULT_INJECTION_PROCESSING_DELAY)) {
			LOG_WRN("injection active: processing-delay delay_ms=%u",
				(unsigned int)FAULT_INJECTION_PROCESSING_DELAY_MS);

			k_sleep(K_MSEC(FAULT_INJECTION_PROCESSING_DELAY_MS));
		}

		processed_count++;

		timing_metrics_update(&timing, &sample, k_uptime_get_32());

		sample_is_valid = validate_sample_data(&sample);

		current_missed_deadline_count = timing.missed_deadline_count;
		current_queue_full_count =
			(uint32_t)atomic_get(&queue_full_count);

		missed_deadline_event =
			current_missed_deadline_count >
			previous_missed_deadline_count;

		queue_overflow_event =
			current_queue_full_count > previous_queue_full_count;

		previous_missed_deadline_count = current_missed_deadline_count;
		previous_queue_full_count = current_queue_full_count;

		state_input.sample_received = true;
		state_input.sample_valid = sample_is_valid;
		state_input.temperature_milli_celsius =
			sample.temperature_milli_celsius;
		state_input.pressure_pa = sample.pressure_pa;
		state_input.stale_data = timing.stale_data;
		state_input.missed_deadline_event = missed_deadline_event;
		state_input.queue_overflow_event = queue_overflow_event;

		previous_health = system_state.node_health;
		previous_environment = system_state.environmental_status;

		state_model_update(&system_state, &state_input);

		if (system_state.node_health != previous_health) {
			log_health_transition(previous_health, &system_state);
		}

		if (system_state.environmental_status != previous_environment) {
			log_environment_transition(previous_environment,
						   &system_state);
		}

		if (missed_deadline_event) {
			LOG_WRN("missed deadline detected: interval_ms=%u threshold_ms=%u missed_count=%u",
				(unsigned int)timing.latest_interval_ms,
				(unsigned int)(SENSOR_ACQ_PERIOD_MS +
					       SENSOR_MISSED_PERIOD_TOLERANCE_MS),
				(unsigned int)timing.missed_deadline_count);
		}

		if (timing.stale_data && !previous_stale_data) {
			LOG_WRN("stale data detected: last_valid_age_ms=%u threshold_ms=%u",
				(unsigned int)timing.last_valid_sample_age_ms,
				(unsigned int)timing.stale_threshold_ms);
		}

		if (previous_health == NODE_HEALTH_FAULT &&
		    system_state.node_health == NODE_HEALTH_HEALTHY) {
			LOG_INF("qualified recovery complete: required_valid_samples=%u",
				(unsigned int)STATE_RECOVERY_VALID_SAMPLE_COUNT);
		}

		previous_stale_data = timing.stale_data;

		if (sample.sequence > expected_sequence) {
			uint32_t missed;

			missed = sample.sequence - expected_sequence;
			sequence_gap_count++;

			LOG_WRN("sequence gap detected: expected=%u received=%u missed=%u gap_count=%u",
				(unsigned int)expected_sequence,
				(unsigned int)sample.sequence,
				(unsigned int)missed,
				(unsigned int)sequence_gap_count);

			expected_sequence = sample.sequence + 1U;
		} else if (sample.sequence < expected_sequence) {
			LOG_WRN("duplicate or out-of-order sample observed: expected=%u received=%u",
				(unsigned int)expected_sequence,
				(unsigned int)sample.sequence);
		} else {
			expected_sequence = sample.sequence + 1U;
		}

		if (sample_is_valid) {
			latest_valid_sample = sample;
			latest_valid_available = true;
			valid_sample_count++;

			env_stats_update_from_sample(&stats, &sample);
		} else {
			invalid_sample_count++;

			LOG_WRN("invalid sample processed: sample=%u timestamp_ms=%u status=%s driver_error=%d",
				(unsigned int)sample.sequence,
				(unsigned int)sample.timestamp_ms,
				sensor_sample_status_to_string(sample.status),
				sample.driver_error);
		}

		{
			struct diagnostics_snapshot_update diagnostic_update = {
				.processed_count = processed_count,
				.valid_sample_count = valid_sample_count,
				.invalid_sample_count = invalid_sample_count,
				.sequence_gap_count = sequence_gap_count,
				.queue_full_count =
					(uint32_t)atomic_get(&queue_full_count),
				.queue_used_count =
					(uint32_t)k_msgq_num_used_get(
						&sensor_sample_msgq),
				.queue_free_count =
					(uint32_t)k_msgq_num_free_get(
						&sensor_sample_msgq),
				.queue_depth = SENSOR_SAMPLE_QUEUE_DEPTH,
				.fault_injection_mask = fault_injection_get_mask(),
				.latest_valid_available = latest_valid_available,
				.latest_valid_sample = latest_valid_sample,
				.stats = stats,
				.timing = timing,
				.system_state = system_state,
				.update_time_ms = k_uptime_get_32(),
			};

			diagnostics_publish_snapshot(&diagnostic_update);
		}

		if ((processed_count % PERIODIC_SUMMARY_SAMPLE_COUNT) == 0U) {
			log_periodic_summary(processed_count,
					     valid_sample_count,
					     invalid_sample_count,
					     sequence_gap_count,
					     &latest_valid_sample,
					     latest_valid_available,
					     &stats,
					     &timing,
					     &system_state);
		}
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
	bool env_stats_test_passed;
	bool state_model_test_passed;

	fault_injection_init();
	diagnostics_init();

	LOG_INF("boot: FieldSense-Z queue backpressure checkpoint");
	LOG_INF("logging mode: deferred");
	LOG_INF("pipeline: acquisition -> k_msgq -> processing -> diagnostics shell -> fault injection");
	LOG_INF("supported sensor channels: temperature pressure; humidity unsupported on verified BMP280 hardware");
	LOG_INF("fault injection: software-only, reversible, diagnostic-shell controlled");
	LOG_INF("queue backpressure: finite queue, nonblocking publish, drop newest on full queue");

	env_stats_test_passed = env_stats_controlled_self_test();
	if (env_stats_test_passed) {
		LOG_INF("selftest env_stats=PASS");
	} else {
		LOG_ERR("selftest env_stats=FAIL");
	}

	state_model_test_passed = state_model_controlled_self_test();
	if (state_model_test_passed) {
		LOG_INF("selftest state_model=PASS");
	} else {
		LOG_ERR("selftest state_model=FAIL");
	}

	LOG_INF("queue item size=%u bytes depth=%u storage_estimate=%u bytes",
		(unsigned int)sizeof(struct sensor_sample),
		(unsigned int)SENSOR_SAMPLE_QUEUE_DEPTH,
		(unsigned int)(sizeof(struct sensor_sample) *
			       SENSOR_SAMPLE_QUEUE_DEPTH));

	LOG_INF("queue policy: non-blocking publish, count overflow, preserve oldest queued samples, drop newest failed publish");

	return 0;
}