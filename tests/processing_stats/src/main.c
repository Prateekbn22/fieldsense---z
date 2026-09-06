#include <stdbool.h>
#include <stdint.h>

#include <zephyr/ztest.h>

#include "app_types.h"
#include "env_stats.h"

#define TEST_PRESSURE_PA 100000

enum sequence_result {
SEQUENCE_RESULT_EXPECTED = 0,
SEQUENCE_RESULT_GAP,
SEQUENCE_RESULT_DUPLICATE_OR_OUT_OF_ORDER,
};

struct sequence_tracker {
uint32_t expected_sequence;
uint32_t gap_count;
};

static void sequence_tracker_init(struct sequence_tracker *tracker,
  uint32_t first_expected_sequence)
{
tracker->expected_sequence = first_expected_sequence;
tracker->gap_count = 0U;
}

static enum sequence_result sequence_tracker_update(
struct sequence_tracker *tracker,
uint32_t received_sequence,
uint32_t *missed_count)
{
if (missed_count != NULL) {
*missed_count = 0U;
}

if (received_sequence > tracker->expected_sequence) {
if (missed_count != NULL) {
*missed_count =
received_sequence - tracker->expected_sequence;
}

tracker->gap_count++;
tracker->expected_sequence = received_sequence + 1U;

return SEQUENCE_RESULT_GAP;
}

if (received_sequence < tracker->expected_sequence) {
return SEQUENCE_RESULT_DUPLICATE_OR_OUT_OF_ORDER;
}

tracker->expected_sequence = received_sequence + 1U;

return SEQUENCE_RESULT_EXPECTED;
}

static bool sample_is_valid_for_processing(const struct sensor_sample *sample)
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

return true;
}

static struct sensor_sample make_valid_sample(uint32_t sequence,
      int32_t temperature_milli_c,
      int32_t pressure_pa)
{
struct sensor_sample sample = {
.timestamp_ms = sequence * 2000U,
.sequence = sequence,
.temperature_milli_celsius = temperature_milli_c,
.pressure_pa = pressure_pa,
.humidity_supported = false,
.humidity_milli_percent_rh = 0,
.valid = true,
.status = SENSOR_SAMPLE_STATUS_OK,
.driver_error = 0,
};

return sample;
}

static struct sensor_sample make_invalid_sample(uint32_t sequence)
{
struct sensor_sample sample = {
.timestamp_ms = sequence * 2000U,
.sequence = sequence,
.temperature_milli_celsius = 26000,
.pressure_pa = TEST_PRESSURE_PA,
.humidity_supported = false,
.humidity_milli_percent_rh = 0,
.valid = false,
.status = SENSOR_SAMPLE_STATUS_FETCH_FAILED,
.driver_error = -5,
};

return sample;
}

ZTEST(processing_stats, test_first_sample_initializes_statistics)
{
struct environmental_stats stats;
struct sensor_sample sample;

env_stats_init(&stats);

sample = make_valid_sample(1U, 22000, TEST_PRESSURE_PA);
env_stats_update_from_sample(&stats, &sample);

zassert_true(stats.temperature_milli_celsius.has_value,
     "temperature should have a value after first sample");
zassert_equal(stats.temperature_milli_celsius.valid_count, 1U,
      "temperature count should be 1");
zassert_equal(stats.temperature_milli_celsius.latest, 22000,
      "latest temperature should match first sample");
zassert_equal(stats.temperature_milli_celsius.minimum, 22000,
      "minimum temperature should match first sample");
zassert_equal(stats.temperature_milli_celsius.maximum, 22000,
      "maximum temperature should match first sample");
zassert_equal(stats.temperature_milli_celsius.moving_average, 22000,
      "moving average should match first sample");
}

ZTEST(processing_stats, test_minimum_temperature_updates)
{
struct environmental_stats stats;
struct sensor_sample sample;

env_stats_init(&stats);

sample = make_valid_sample(1U, 25000, TEST_PRESSURE_PA);
env_stats_update_from_sample(&stats, &sample);

sample = make_valid_sample(2U, 23000, TEST_PRESSURE_PA);
env_stats_update_from_sample(&stats, &sample);

sample = make_valid_sample(3U, 24000, TEST_PRESSURE_PA);
env_stats_update_from_sample(&stats, &sample);

zassert_equal(stats.temperature_milli_celsius.minimum, 23000,
      "minimum temperature should be 23.000 C");
}

ZTEST(processing_stats, test_maximum_temperature_updates)
{
struct environmental_stats stats;
struct sensor_sample sample;

env_stats_init(&stats);

sample = make_valid_sample(1U, 22000, TEST_PRESSURE_PA);
env_stats_update_from_sample(&stats, &sample);

sample = make_valid_sample(2U, 27000, TEST_PRESSURE_PA);
env_stats_update_from_sample(&stats, &sample);

sample = make_valid_sample(3U, 26000, TEST_PRESSURE_PA);
env_stats_update_from_sample(&stats, &sample);

zassert_equal(stats.temperature_milli_celsius.maximum, 27000,
      "maximum temperature should be 27.000 C");
}

ZTEST(processing_stats, test_moving_average_startup_window)
{
struct environmental_stats stats;
struct sensor_sample sample;

env_stats_init(&stats);

sample = make_valid_sample(1U, 22000, TEST_PRESSURE_PA);
env_stats_update_from_sample(&stats, &sample);

sample = make_valid_sample(2U, 24000, TEST_PRESSURE_PA);
env_stats_update_from_sample(&stats, &sample);

zassert_equal(stats.temperature_milli_celsius.valid_count, 2U,
      "startup average should use available samples");
zassert_equal(stats.temperature_milli_celsius.moving_average, 23000,
      "average of 22.000 C and 24.000 C should be 23.000 C");
}

ZTEST(processing_stats, test_full_averaging_window)
{
struct environmental_stats stats;
struct sensor_sample sample;

env_stats_init(&stats);

sample = make_valid_sample(1U, 22000, TEST_PRESSURE_PA);
env_stats_update_from_sample(&stats, &sample);

sample = make_valid_sample(2U, 23000, TEST_PRESSURE_PA);
env_stats_update_from_sample(&stats, &sample);

sample = make_valid_sample(3U, 21000, TEST_PRESSURE_PA);
env_stats_update_from_sample(&stats, &sample);

sample = make_valid_sample(4U, 24000, TEST_PRESSURE_PA);
env_stats_update_from_sample(&stats, &sample);

sample = make_valid_sample(5U, 25000, TEST_PRESSURE_PA);
env_stats_update_from_sample(&stats, &sample);

zassert_equal(stats.temperature_milli_celsius.valid_count, 5U,
      "full moving average window should contain five samples");
zassert_equal(stats.temperature_milli_celsius.moving_average, 23000,
      "average of 22, 23, 21, 24, 25 C should be 23.000 C");
}

ZTEST(processing_stats, test_full_window_rolls_forward)
{
struct environmental_stats stats;
struct sensor_sample sample;

env_stats_init(&stats);

sample = make_valid_sample(1U, 22000, TEST_PRESSURE_PA);
env_stats_update_from_sample(&stats, &sample);

sample = make_valid_sample(2U, 23000, TEST_PRESSURE_PA);
env_stats_update_from_sample(&stats, &sample);

sample = make_valid_sample(3U, 21000, TEST_PRESSURE_PA);
env_stats_update_from_sample(&stats, &sample);

sample = make_valid_sample(4U, 24000, TEST_PRESSURE_PA);
env_stats_update_from_sample(&stats, &sample);

sample = make_valid_sample(5U, 25000, TEST_PRESSURE_PA);
env_stats_update_from_sample(&stats, &sample);

sample = make_valid_sample(6U, 26000, TEST_PRESSURE_PA);
env_stats_update_from_sample(&stats, &sample);

zassert_equal(stats.temperature_milli_celsius.valid_count, 6U,
      "valid count should include all accepted samples");
zassert_equal(stats.temperature_milli_celsius.moving_average, 23800,
      "rolling average should use last five samples");
}

ZTEST(processing_stats, test_negative_temperature)
{
struct environmental_stats stats;
struct sensor_sample sample;

env_stats_init(&stats);

sample = make_valid_sample(1U, -5000, TEST_PRESSURE_PA);
env_stats_update_from_sample(&stats, &sample);

sample = make_valid_sample(2U, 1000, TEST_PRESSURE_PA);
env_stats_update_from_sample(&stats, &sample);

zassert_equal(stats.temperature_milli_celsius.minimum, -5000,
      "minimum should support negative temperatures");
zassert_equal(stats.temperature_milli_celsius.moving_average, -2000,
      "average of -5.000 C and 1.000 C should be -2.000 C");
}

ZTEST(processing_stats, test_large_scaled_values)
{
struct environmental_stats stats;
struct sensor_sample sample;

env_stats_init(&stats);

sample = make_valid_sample(1U, 85000, 110000);
env_stats_update_from_sample(&stats, &sample);

sample = make_valid_sample(2U, 84000, 109000);
env_stats_update_from_sample(&stats, &sample);

zassert_equal(stats.temperature_milli_celsius.maximum, 85000,
      "large milli-Celsius value should be preserved");
zassert_equal(stats.pressure_pa.maximum, 110000,
      "large pressure value should be preserved");
zassert_equal(stats.pressure_pa.moving_average, 109500,
      "pressure average should use scaled integer values");
}

ZTEST(processing_stats, test_invalid_sample_is_rejected_by_processing_gate)
{
struct environmental_stats stats;
struct sensor_sample invalid_sample;
struct sensor_sample valid_sample;

env_stats_init(&stats);

invalid_sample = make_invalid_sample(1U);
valid_sample = make_valid_sample(2U, 26000, TEST_PRESSURE_PA);

if (sample_is_valid_for_processing(&invalid_sample)) {
env_stats_update_from_sample(&stats, &invalid_sample);
}

zassert_false(stats.temperature_milli_celsius.has_value,
      "invalid sample should not update statistics");

if (sample_is_valid_for_processing(&valid_sample)) {
env_stats_update_from_sample(&stats, &valid_sample);
}

zassert_true(stats.temperature_milli_celsius.has_value,
     "valid sample should update statistics");
zassert_equal(stats.temperature_milli_celsius.valid_count, 1U,
      "only one valid sample should be counted");
zassert_equal(stats.temperature_milli_celsius.latest, 26000,
      "latest value should come from the valid sample");
}

ZTEST(processing_stats, test_sequence_gap_detection)
{
struct sequence_tracker tracker;
enum sequence_result result;
uint32_t missed_count;

sequence_tracker_init(&tracker, 1U);

result = sequence_tracker_update(&tracker, 1U, &missed_count);
zassert_equal(result, SEQUENCE_RESULT_EXPECTED,
      "sequence 1 should be expected");
zassert_equal(missed_count, 0U,
      "no samples missed for expected sequence");

result = sequence_tracker_update(&tracker, 4U, &missed_count);
zassert_equal(result, SEQUENCE_RESULT_GAP,
      "sequence 4 should create a gap when 2 was expected");
zassert_equal(missed_count, 2U,
      "sequences 2 and 3 should be counted as missed");
zassert_equal(tracker.gap_count, 1U,
      "gap counter should increment once");

result = sequence_tracker_update(&tracker, 4U, &missed_count);
zassert_equal(result, SEQUENCE_RESULT_DUPLICATE_OR_OUT_OF_ORDER,
      "duplicate sequence should not create a new gap");
zassert_equal(tracker.gap_count, 1U,
      "duplicate should not increment gap count");
}

ZTEST_SUITE(processing_stats, NULL, NULL, NULL, NULL, NULL);
