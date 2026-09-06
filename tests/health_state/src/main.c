#include <stdbool.h>
#include <stdint.h>

#include <zephyr/ztest.h>

#include "app_types.h"
#include "state_model.h"
#include "timing_metrics.h"

#define TEST_PERIOD_MS 2000U
#define TEST_MISSED_TOLERANCE_MS 250U
#define TEST_STALE_THRESHOLD_MS 6000U

#define NORMAL_TEMP_MC 26000
#define NORMAL_PRESSURE_PA 100000

static struct state_model_input make_state_input(bool sample_valid,
 int32_t temp_mc,
 int32_t pressure_pa,
 bool stale_data,
 bool missed_deadline_event,
 bool queue_overflow_event)
{
struct state_model_input input = {
.sample_received = true,
.sample_valid = sample_valid,
.temperature_milli_celsius = temp_mc,
.pressure_pa = pressure_pa,
.stale_data = stale_data,
.missed_deadline_event = missed_deadline_event,
.queue_overflow_event = queue_overflow_event,
};

return input;
}

static struct state_model_input normal_input(void)
{
return make_state_input(true,
NORMAL_TEMP_MC,
NORMAL_PRESSURE_PA,
false,
false,
false);
}

static struct state_model_input sensor_failure_input(void)
{
return make_state_input(false,
NORMAL_TEMP_MC,
NORMAL_PRESSURE_PA,
false,
false,
false);
}

static struct sensor_sample make_sample(uint32_t sequence,
uint32_t timestamp_ms,
bool valid,
int32_t temp_mc,
int32_t pressure_pa)
{
struct sensor_sample sample = {
.timestamp_ms = timestamp_ms,
.sequence = sequence,
.temperature_milli_celsius = temp_mc,
.pressure_pa = pressure_pa,
.humidity_supported = false,
.humidity_milli_percent_rh = 0,
.valid = valid,
.status = valid ? SENSOR_SAMPLE_STATUS_OK :
  SENSOR_SAMPLE_STATUS_FETCH_FAILED,
.driver_error = valid ? 0 : -5,
};

return sample;
}

static bool sample_is_valid_for_pipeline(const struct sensor_sample *sample)
{
return sample->valid &&
       sample->status == SENSOR_SAMPLE_STATUS_OK &&
       sample->driver_error == 0;
}

static void start_healthy(struct state_model *model)
{
struct state_model_input input;

state_model_init(model);

input = normal_input();
state_model_update(model, &input);

zassert_equal(model->node_health,
      NODE_HEALTH_HEALTHY,
      "model should enter HEALTHY after first valid sample");
}

static void drive_sensor_failure_fault(struct state_model *model)
{
struct state_model_input input;

input = sensor_failure_input();

for (uint32_t i = 0U; i < STATE_SENSOR_FAILURES_BEFORE_FAULT; i++) {
state_model_update(model, &input);
}

zassert_equal(model->node_health,
      NODE_HEALTH_FAULT,
      "repeated sensor failures should enter FAULT");
}

static void recover_to_healthy(struct state_model *model)
{
struct state_model_input input;

input = normal_input();

for (uint32_t i = 0U; i < STATE_RECOVERY_VALID_SAMPLE_COUNT; i++) {
state_model_update(model, &input);
}
}

static void process_pipeline_sample(struct state_model *model,
    struct timing_metrics *timing,
    const struct sensor_sample *sample,
    uint32_t now_ms,
    bool missed_deadline_event,
    bool queue_overflow_event)
{
struct state_model_input input;
bool sample_valid;

timing_metrics_update(timing, sample, now_ms);

sample_valid = sample_is_valid_for_pipeline(sample);

input = make_state_input(sample_valid,
 sample->temperature_milli_celsius,
 sample->pressure_pa,
 timing->stale_data,
 missed_deadline_event,
 queue_overflow_event);

state_model_update(model, &input);
}

ZTEST(health_state, test_initializing_to_healthy)
{
struct state_model model;
struct state_model_input input;

state_model_init(&model);

zassert_equal(model.node_health,
      NODE_HEALTH_INITIALIZING,
      "initial node state should be INITIALIZING");

input = normal_input();
state_model_update(&model, &input);

zassert_equal(model.node_health,
      NODE_HEALTH_HEALTHY,
      "valid first sample should move INITIALIZING to HEALTHY");
zassert_equal(model.environmental_status,
      ENV_STATUS_NORMAL,
      "normal first sample should set environment NORMAL");
}

ZTEST(health_state, test_healthy_to_warning)
{
struct state_model model;
struct state_model_input input;

start_healthy(&model);

input = sensor_failure_input();
state_model_update(&model, &input);

zassert_equal(model.node_health,
      NODE_HEALTH_WARNING,
      "single sensor failure should move HEALTHY to WARNING");
zassert_true(model.consecutive_sensor_failures > 0U,
     "sensor failure counter should increase");
}

ZTEST(health_state, test_warning_to_fault)
{
struct state_model model;

start_healthy(&model);
drive_sensor_failure_fault(&model);

zassert_equal(model.node_health,
      NODE_HEALTH_FAULT,
      "repeated sensor failures should move WARNING to FAULT");
zassert_equal(model.consecutive_sensor_failures,
      STATE_SENSOR_FAILURES_BEFORE_FAULT,
      "sensor failure counter should reach fault threshold");
}

ZTEST(health_state, test_fault_to_healthy_recovery)
{
struct state_model model;

start_healthy(&model);
drive_sensor_failure_fault(&model);

recover_to_healthy(&model);

zassert_equal(model.node_health,
      NODE_HEALTH_HEALTHY,
      "FAULT should recover to HEALTHY after required valid samples");
zassert_equal(model.consecutive_sensor_failures,
      0U,
      "sensor failure counter should clear after recovery");
}

ZTEST(health_state, test_stale_data_detection)
{
struct timing_metrics timing;
struct sensor_sample sample;

timing_metrics_init(&timing,
    TEST_PERIOD_MS,
    TEST_MISSED_TOLERANCE_MS,
    TEST_STALE_THRESHOLD_MS);

sample = make_sample(1U,
     1000U,
     true,
     NORMAL_TEMP_MC,
     NORMAL_PRESSURE_PA);

timing_metrics_update(&timing, &sample, 8000U);

zassert_true(timing.have_last_valid_sample,
     "timing should remember the last valid sample");
zassert_equal(timing.last_valid_sample_age_ms,
      7000U,
      "synthetic timestamp should create a 7000 ms age");
zassert_true(timing.stale_data,
     "sample age beyond threshold should set stale_data");
}

ZTEST(health_state, test_stale_data_moves_health_toward_fault)
{
struct state_model model;
struct state_model_input input;

start_healthy(&model);

input = make_state_input(true,
 NORMAL_TEMP_MC,
 NORMAL_PRESSURE_PA,
 true,
 false,
 false);

for (uint32_t i = 0U; i < STATE_STALE_EVENTS_BEFORE_FAULT; i++) {
state_model_update(&model, &input);
}

zassert_equal(model.node_health,
      NODE_HEALTH_FAULT,
      "repeated stale-data events should enter FAULT");
zassert_equal(model.stale_data_event_count,
      STATE_STALE_EVENTS_BEFORE_FAULT,
      "stale event counter should reach threshold");
}

ZTEST(health_state, test_queue_overflow_behavior)
{
struct state_model model;
struct state_model_input input;

start_healthy(&model);

input = make_state_input(true,
 NORMAL_TEMP_MC,
 NORMAL_PRESSURE_PA,
 false,
 false,
 true);

for (uint32_t i = 0U; i < STATE_QUEUE_OVERFLOWS_BEFORE_FAULT; i++) {
state_model_update(&model, &input);
}

zassert_equal(model.node_health,
      NODE_HEALTH_FAULT,
      "repeated queue-overflow events should enter FAULT");
zassert_equal(model.queue_overflow_event_count,
      STATE_QUEUE_OVERFLOWS_BEFORE_FAULT,
      "queue overflow counter should reach threshold");
}

ZTEST(health_state, test_single_transient_error_does_not_fault)
{
struct state_model model;
struct state_model_input input;

start_healthy(&model);

input = sensor_failure_input();
state_model_update(&model, &input);

zassert_not_equal(model.node_health,
  NODE_HEALTH_FAULT,
  "one transient error should not immediately enter FAULT");

recover_to_healthy(&model);

zassert_equal(model.node_health,
      NODE_HEALTH_HEALTHY,
      "transient error should recover after valid samples");
}

ZTEST(health_state, test_environmental_alert_while_node_is_healthy)
{
struct state_model model;
struct state_model_input input;

start_healthy(&model);

input = make_state_input(true,
 STATE_HIGH_TEMP_ENTER_MILLI_C,
 NORMAL_PRESSURE_PA,
 false,
 false,
 false);

state_model_update(&model, &input);

zassert_equal(model.node_health,
      NODE_HEALTH_HEALTHY,
      "environmental alert should not automatically fault the node");
zassert_equal(model.environmental_status,
      ENV_STATUS_HIGH_TEMPERATURE,
      "high temperature threshold should set HIGH_TEMPERATURE");
}

ZTEST(health_state, test_temperature_threshold_boundaries)
{
struct state_model model;
struct state_model_input input;

state_model_init(&model);

input = make_state_input(true,
 STATE_HIGH_TEMP_ENTER_MILLI_C - 1,
 NORMAL_PRESSURE_PA,
 false,
 false,
 false);
state_model_update(&model, &input);

zassert_equal(model.environmental_status,
      ENV_STATUS_NORMAL,
      "one mC below high-temp enter should remain NORMAL");

input = make_state_input(true,
 STATE_HIGH_TEMP_ENTER_MILLI_C,
 NORMAL_PRESSURE_PA,
 false,
 false,
 false);
state_model_update(&model, &input);

zassert_equal(model.environmental_status,
      ENV_STATUS_HIGH_TEMPERATURE,
      "high-temp enter boundary should trigger alert");

input = make_state_input(true,
 STATE_HIGH_TEMP_CLEAR_MILLI_C + 1,
 NORMAL_PRESSURE_PA,
 false,
 false,
 false);
state_model_update(&model, &input);

zassert_equal(model.environmental_status,
      ENV_STATUS_HIGH_TEMPERATURE,
      "one mC above clear boundary should keep alert active");

input = make_state_input(true,
 STATE_HIGH_TEMP_CLEAR_MILLI_C,
 NORMAL_PRESSURE_PA,
 false,
 false,
 false);
state_model_update(&model, &input);

zassert_equal(model.environmental_status,
      ENV_STATUS_NORMAL,
      "high-temp clear boundary should return to NORMAL");
}

ZTEST(health_state, test_pressure_threshold_boundaries)
{
	struct state_model model;
	struct state_model_input input;

	state_model_init(&model);

	input = make_state_input(true,
				 NORMAL_TEMP_MC,
				 STATE_PRESSURE_HIGH_ENTER_PA,
				 false,
				 false,
				 false);
	state_model_update(&model, &input);

	zassert_equal(model.environmental_status,
		      ENV_STATUS_NORMAL,
		      "equal to pressure high enter boundary should remain NORMAL when enter comparison is strict");

	input = make_state_input(true,
				 NORMAL_TEMP_MC,
				 STATE_PRESSURE_HIGH_ENTER_PA + 1,
				 false,
				 false,
				 false);
	state_model_update(&model, &input);

	zassert_equal(model.environmental_status,
		      ENV_STATUS_PRESSURE_ALERT,
		      "one Pa above pressure high enter boundary should trigger alert");

	input = make_state_input(true,
				 NORMAL_TEMP_MC,
				 STATE_PRESSURE_HIGH_CLEAR_PA + 1,
				 false,
				 false,
				 false);
	state_model_update(&model, &input);

	zassert_equal(model.environmental_status,
		      ENV_STATUS_PRESSURE_ALERT,
		      "one Pa above pressure high clear boundary should keep alert active");

	input = make_state_input(true,
				 NORMAL_TEMP_MC,
				 STATE_PRESSURE_HIGH_CLEAR_PA,
				 false,
				 false,
				 false);
	state_model_update(&model, &input);

	zassert_equal(model.environmental_status,
		      ENV_STATUS_NORMAL,
		      "pressure high clear boundary should return to NORMAL");

	input = make_state_input(true,
				 NORMAL_TEMP_MC,
				 STATE_PRESSURE_LOW_ENTER_PA,
				 false,
				 false,
				 false);
	state_model_update(&model, &input);

	zassert_equal(model.environmental_status,
		      ENV_STATUS_NORMAL,
		      "equal to pressure low enter boundary should remain NORMAL when enter comparison is strict");

	input = make_state_input(true,
				 NORMAL_TEMP_MC,
				 STATE_PRESSURE_LOW_ENTER_PA - 1,
				 false,
				 false,
				 false);
	state_model_update(&model, &input);

	zassert_equal(model.environmental_status,
		      ENV_STATUS_PRESSURE_ALERT,
		      "one Pa below pressure low enter boundary should trigger alert");

	input = make_state_input(true,
				 NORMAL_TEMP_MC,
				 STATE_PRESSURE_LOW_CLEAR_PA - 1,
				 false,
				 false,
				 false);
	state_model_update(&model, &input);

	zassert_equal(model.environmental_status,
		      ENV_STATUS_PRESSURE_ALERT,
		      "one Pa below pressure low clear boundary should keep alert active");

	input = make_state_input(true,
				 NORMAL_TEMP_MC,
				 STATE_PRESSURE_LOW_CLEAR_PA,
				 false,
				 false,
				 false);
	state_model_update(&model, &input);

	zassert_equal(model.environmental_status,
		      ENV_STATUS_NORMAL,
		      "pressure low clear boundary should return to NORMAL");
}
ZTEST(health_state, test_small_pipeline_without_physical_hardware)
{
struct state_model model;
struct timing_metrics timing;
struct sensor_sample sample;

state_model_init(&model);

timing_metrics_init(&timing,
    TEST_PERIOD_MS,
    TEST_MISSED_TOLERANCE_MS,
    TEST_STALE_THRESHOLD_MS);

sample = make_sample(1U,
     1000U,
     true,
     NORMAL_TEMP_MC,
     NORMAL_PRESSURE_PA);

process_pipeline_sample(&model,
&timing,
&sample,
1000U,
false,
false);

zassert_equal(model.node_health,
      NODE_HEALTH_HEALTHY,
      "first synthetic valid sample should make node HEALTHY");
zassert_equal(model.environmental_status,
      ENV_STATUS_NORMAL,
      "normal synthetic sample should make environment NORMAL");

sample = make_sample(2U,
     3000U,
     true,
     STATE_HIGH_TEMP_ENTER_MILLI_C,
     NORMAL_PRESSURE_PA);

process_pipeline_sample(&model,
&timing,
&sample,
3000U,
false,
false);

zassert_equal(model.node_health,
      NODE_HEALTH_HEALTHY,
      "high environmental reading should leave node health HEALTHY");
zassert_equal(model.environmental_status,
      ENV_STATUS_HIGH_TEMPERATURE,
      "pipeline should propagate high temperature alert");

sample = make_sample(3U,
     5000U,
     false,
     NORMAL_TEMP_MC,
     NORMAL_PRESSURE_PA);

process_pipeline_sample(&model,
&timing,
&sample,
5000U,
false,
false);

zassert_equal(model.node_health,
      NODE_HEALTH_WARNING,
      "invalid synthetic sample should move node to WARNING");
}

ZTEST_SUITE(health_state, NULL, NULL, NULL, NULL, NULL);
