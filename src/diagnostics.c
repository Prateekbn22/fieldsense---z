#include <errno.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/shell/shell.h>
#include <zephyr/sys/atomic.h>
#include <zephyr/sys/util.h>

#include "diagnostics.h"
#include "fault_injection.h"
#include "sensor_service.h"
#include "state_model.h"

LOG_MODULE_REGISTER(health, LOG_LEVEL_INF);

K_MUTEX_DEFINE(diagnostics_mutex);

static struct diagnostics_snapshot_update diagnostics_snapshot;
static bool diagnostics_snapshot_valid;
static atomic_t reset_stats_requested;

void diagnostics_init(void)
{
	(void)k_mutex_lock(&diagnostics_mutex, K_FOREVER);

	memset(&diagnostics_snapshot, 0, sizeof(diagnostics_snapshot));
	diagnostics_snapshot_valid = false;
	atomic_set(&reset_stats_requested, 0);

	(void)k_mutex_unlock(&diagnostics_mutex);
}

void diagnostics_publish_snapshot(
	const struct diagnostics_snapshot_update *update)
{
	if (update == NULL) {
		return;
	}

	if (k_mutex_lock(&diagnostics_mutex, K_MSEC(20)) != 0) {
		LOG_WRN("diagnostic snapshot update skipped: mutex busy");
		return;
	}

	diagnostics_snapshot = *update;
	diagnostics_snapshot_valid = true;

	(void)k_mutex_unlock(&diagnostics_mutex);
}

bool diagnostics_reset_stats_requested_take(void)
{
	return atomic_cas(&reset_stats_requested, 1, 0);
}

static int copy_snapshot(struct diagnostics_snapshot_update *copy)
{
	if (copy == NULL) {
		return -EINVAL;
	}

	if (k_mutex_lock(&diagnostics_mutex, K_MSEC(100)) != 0) {
		return -EBUSY;
	}

	if (!diagnostics_snapshot_valid) {
		(void)k_mutex_unlock(&diagnostics_mutex);
		return -ENODATA;
	}

	*copy = diagnostics_snapshot;

	(void)k_mutex_unlock(&diagnostics_mutex);

	return 0;
}

static void shell_print_milli_c(const struct shell *sh, const char *label,
				int32_t milli_c)
{
	int32_t abs_value;
	int32_t whole;
	int32_t frac;

	abs_value = milli_c < 0 ? -milli_c : milli_c;
	whole = abs_value / 1000;
	frac = abs_value % 1000;

	if (milli_c < 0) {
		shell_print(sh, "%s: -%d.%03d C (%d mC)",
			    label, whole, frac, milli_c);
	} else {
		shell_print(sh, "%s: %d.%03d C (%d mC)",
			    label, whole, frac, milli_c);
	}
}

static void shell_print_pressure(const struct shell *sh, const char *label,
				 int32_t pressure_pa)
{
	int32_t kpa_whole = pressure_pa / 1000;
	int32_t kpa_frac = pressure_pa % 1000;

	shell_print(sh, "%s: %d.%03d kPa (%d Pa)",
		    label, kpa_whole, kpa_frac, pressure_pa);
}

static int require_snapshot(const struct shell *sh,
			    struct diagnostics_snapshot_update *snapshot)
{
	int ret;

	ret = copy_snapshot(snapshot);
	if (ret == -ENODATA) {
		shell_error(sh, "no diagnostic snapshot available yet");
		return ret;
	}

	if (ret == -EBUSY) {
		shell_error(sh, "diagnostic snapshot busy, try again");
		return ret;
	}

	if (ret != 0) {
		shell_error(sh, "failed to read diagnostic snapshot, ret=%d", ret);
		return ret;
	}

	return 0;
}

static void shell_print_fault_injections(const struct shell *sh,
					 uint32_t mask)
{
	shell_print(sh, "fault_injection_mask: 0x%08x",
		    (unsigned int)mask);

	if (mask == 0U) {
		shell_print(sh, "active_injections: none");
		return;
	}

	shell_print(sh, "active_injections:");

	if ((mask & FAULT_INJECTION_SENSOR_READ_FAILURE) != 0U) {
		shell_print(sh, "- sensor-read-failure");
	}

	if ((mask & FAULT_INJECTION_STALE_PUBLICATION) != 0U) {
		shell_print(sh, "- stale-publication");
	}

	if ((mask & FAULT_INJECTION_PROCESSING_DELAY) != 0U) {
		shell_print(sh, "- processing-delay");
	}

	if ((mask & FAULT_INJECTION_QUEUE_PRESSURE) != 0U) {
		shell_print(sh, "- queue-pressure");
	}

	if ((mask & FAULT_INJECTION_INVALID_MEASUREMENT) != 0U) {
		shell_print(sh, "- invalid-measurement");
	}
}

static int cmd_node_status(const struct shell *sh)
{
	struct diagnostics_snapshot_update snapshot;
	uint32_t current_injection_mask;
	int ret;

	ret = require_snapshot(sh, &snapshot);
	if (ret != 0) {
		return ret;
	}

	current_injection_mask = fault_injection_get_mask();

	shell_print(sh, "Node status");
	shell_print(sh, "health: %s",
		    node_health_state_to_string(
			    snapshot.system_state.node_health));
	shell_print(sh, "environment: %s",
		    environmental_status_to_string(
			    snapshot.system_state.environmental_status));
	shell_print(sh, "last_fault_reason: %s",
		    state_fault_reason_to_string(
			    snapshot.system_state.last_fault_reason));
	shell_print(sh, "processed_count: %u samples",
		    (unsigned int)snapshot.processed_count);
	shell_print(sh, "valid_count: %u samples",
		    (unsigned int)snapshot.valid_sample_count);
	shell_print(sh, "invalid_count: %u samples",
		    (unsigned int)snapshot.invalid_sample_count);
	shell_print(sh, "queue_full_count: %u events",
		    (unsigned int)snapshot.queue_full_count);

	shell_print_fault_injections(sh, current_injection_mask);

	shell_print(sh, "snapshot_fault_injection_mask: 0x%08x",
		    (unsigned int)snapshot.fault_injection_mask);
	shell_print(sh, "snapshot_age_reference_ms: %u ms uptime",
		    (unsigned int)snapshot.update_time_ms);

	return 0;
}

static int cmd_node_latest(const struct shell *sh)
{
	struct diagnostics_snapshot_update snapshot;
	const struct sensor_sample *sample;
	int ret;

	ret = require_snapshot(sh, &snapshot);
	if (ret != 0) {
		return ret;
	}

	if (!snapshot.latest_valid_available) {
		shell_error(sh, "no latest valid sample available");
		return -ENODATA;
	}

	sample = &snapshot.latest_valid_sample;

	shell_print(sh, "Latest valid sample");
	shell_print(sh, "sequence: %u", (unsigned int)sample->sequence);
	shell_print(sh, "timestamp: %u ms", (unsigned int)sample->timestamp_ms);
	shell_print(sh, "status: %s",
		    sensor_sample_status_to_string(sample->status));

	shell_print_milli_c(sh, "temperature", sample->temperature_milli_celsius);
	shell_print_pressure(sh, "pressure", sample->pressure_pa);

	if (sample->humidity_supported) {
		shell_print(sh, "humidity: %d m%%RH",
			    sample->humidity_milli_percent_rh);
	} else {
		shell_print(sh, "humidity: unsupported by verified BMP280 hardware");
	}

	return 0;
}

static int cmd_node_stats(const struct shell *sh)
{
	struct diagnostics_snapshot_update snapshot;
	const struct environmental_stats *stats;
	int ret;

	ret = require_snapshot(sh, &snapshot);
	if (ret != 0) {
		return ret;
	}

	stats = &snapshot.stats;

	shell_print(sh, "Environmental statistics");
	shell_print(sh, "valid samples: %u",
		    (unsigned int)snapshot.valid_sample_count);
	shell_print(sh, "invalid samples: %u",
		    (unsigned int)snapshot.invalid_sample_count);

	if (!stats->temperature_milli_celsius.has_value) {
		shell_print(sh, "temperature: no valid samples yet");
	} else {
		shell_print(sh, "temperature count: %u samples",
			    (unsigned int)
			    stats->temperature_milli_celsius.valid_count);
		shell_print_milli_c(sh, "temperature latest",
				    stats->temperature_milli_celsius.latest);
		shell_print_milli_c(sh, "temperature minimum",
				    stats->temperature_milli_celsius.minimum);
		shell_print_milli_c(sh, "temperature maximum",
				    stats->temperature_milli_celsius.maximum);
		shell_print_milli_c(sh, "temperature moving_average",
				    stats->temperature_milli_celsius.moving_average);
	}

	if (!stats->pressure_pa.has_value) {
		shell_print(sh, "pressure: no valid samples yet");
	} else {
		shell_print(sh, "pressure count: %u samples",
			    (unsigned int)stats->pressure_pa.valid_count);
		shell_print_pressure(sh, "pressure latest",
				     stats->pressure_pa.latest);
		shell_print_pressure(sh, "pressure minimum",
				     stats->pressure_pa.minimum);
		shell_print_pressure(sh, "pressure maximum",
				     stats->pressure_pa.maximum);
		shell_print_pressure(sh, "pressure moving_average",
				     stats->pressure_pa.moving_average);
	}

	shell_print(sh, "humidity statistics: unsupported by verified BMP280 hardware");

	return 0;
}

static int cmd_node_timing(const struct shell *sh)
{
	struct diagnostics_snapshot_update snapshot;
	const struct timing_metrics *timing;
	int ret;

	ret = require_snapshot(sh, &snapshot);
	if (ret != 0) {
		return ret;
	}

	timing = &snapshot.timing;

	shell_print(sh, "Timing metrics");
	shell_print(sh, "requested_period: %u ms",
		    (unsigned int)timing->requested_period_ms);
	shell_print(sh, "missed_deadline_threshold: %u ms",
		    (unsigned int)(timing->requested_period_ms +
				   timing->missed_tolerance_ms));
	shell_print(sh, "stale_threshold: %u ms",
		    (unsigned int)timing->stale_threshold_ms);

	if (timing->interval_count == 0U) {
		shell_print(sh, "intervals: waiting for second sample");
	} else {
		shell_print(sh, "latest_interval: %u ms",
			    (unsigned int)timing->latest_interval_ms);
		shell_print(sh, "minimum_interval: %u ms",
			    (unsigned int)timing->minimum_interval_ms);
		shell_print(sh, "maximum_interval: %u ms",
			    (unsigned int)timing->maximum_interval_ms);
		shell_print(sh, "mean_interval: %u ms",
			    (unsigned int)timing->mean_interval_ms);
		shell_print(sh, "scheduler_delay: %d ms",
			    timing->latest_scheduler_delay_ms);
	}

	shell_print(sh, "missed_deadlines: %u events",
		    (unsigned int)timing->missed_deadline_count);

	if (timing->have_last_valid_sample) {
		shell_print(sh, "last_valid_sample_age: %u ms",
			    (unsigned int)timing->last_valid_sample_age_ms);
		shell_print(sh, "stale_data: %s",
			    timing->stale_data ? "yes" : "no");
	} else {
		shell_print(sh, "last_valid_sample_age: unavailable");
		shell_print(sh, "stale_data: unknown");
	}

	return 0;
}

static int cmd_node_faults(const struct shell *sh)
{
	struct diagnostics_snapshot_update snapshot;
	const struct state_model *state;
	int ret;

	ret = require_snapshot(sh, &snapshot);
	if (ret != 0) {
		return ret;
	}

	state = &snapshot.system_state;

	shell_print(sh, "Fault and transition counters");
	shell_print(sh, "node_health: %s",
		    node_health_state_to_string(state->node_health));
	shell_print(sh, "environment_status: %s",
		    environmental_status_to_string(state->environmental_status));
	shell_print(sh, "last_fault_reason: %s",
		    state_fault_reason_to_string(state->last_fault_reason));
	shell_print(sh, "node_health_transitions: %u",
		    (unsigned int)state->node_health_transition_count);
	shell_print(sh, "environment_transitions: %u",
		    (unsigned int)state->environmental_transition_count);
	shell_print(sh, "consecutive_sensor_failures: %u",
		    (unsigned int)state->consecutive_sensor_failures);
	shell_print(sh, "recovery_valid_samples: %u",
		    (unsigned int)state->consecutive_recovery_valid_samples);
	shell_print(sh, "stale_data_events: %u",
		    (unsigned int)state->stale_data_event_count);
	shell_print(sh, "missed_deadline_events: %u",
		    (unsigned int)state->missed_deadline_event_count);
	shell_print(sh, "queue_overflow_events: %u",
		    (unsigned int)state->queue_overflow_event_count);

	shell_print_fault_injections(sh, fault_injection_get_mask());

	return 0;
}

static int cmd_node_reset_stats(const struct shell *sh)
{
	atomic_set(&reset_stats_requested, 1);

	shell_print(sh, "reset-stats requested");
	shell_print(sh, "processing, statistics, timing, and sequence counters will reset on the next processed sample");
	shell_print(sh, "node health state is not forcibly changed by this command");

	return 0;
}

static int cmd_node_thresholds(const struct shell *sh)
{
	shell_print(sh, "Thresholds");

	shell_print(sh, "sensor failures before FAULT: %u consecutive failures",
		    (unsigned int)STATE_SENSOR_FAILURES_BEFORE_FAULT);
	shell_print(sh, "recovery requirement: %u consecutive valid samples",
		    (unsigned int)STATE_RECOVERY_VALID_SAMPLE_COUNT);
	shell_print(sh, "stale events before FAULT: %u events",
		    (unsigned int)STATE_STALE_EVENTS_BEFORE_FAULT);
	shell_print(sh, "missed deadlines before FAULT: %u events",
		    (unsigned int)STATE_MISSED_DEADLINES_BEFORE_FAULT);
	shell_print(sh, "queue overflows before FAULT: %u events",
		    (unsigned int)STATE_QUEUE_OVERFLOWS_BEFORE_FAULT);

	shell_print_milli_c(sh, "high temperature enter",
			    STATE_HIGH_TEMP_ENTER_MILLI_C);
	shell_print_milli_c(sh, "high temperature clear",
			    STATE_HIGH_TEMP_CLEAR_MILLI_C);

	shell_print_pressure(sh, "pressure low enter",
			     STATE_PRESSURE_LOW_ENTER_PA);
	shell_print_pressure(sh, "pressure high enter",
			     STATE_PRESSURE_HIGH_ENTER_PA);
	shell_print_pressure(sh, "pressure low clear",
			     STATE_PRESSURE_LOW_CLEAR_PA);
	shell_print_pressure(sh, "pressure high clear",
			     STATE_PRESSURE_HIGH_CLEAR_PA);

	return 0;
}

static int cmd_node_inject(const struct shell *sh, size_t argc, char **argv)
{
	const char *fault_name;

	if (argc != 3) {
		shell_error(sh, "usage: node inject <sensor-failure|stale-publication|processing-delay|queue-pressure|invalid-measurement|clear>");
		return -EINVAL;
	}

	fault_name = argv[2];

	if (strcmp(fault_name, "sensor-failure") == 0) {
		fault_injection_enable(FAULT_INJECTION_SENSOR_READ_FAILURE);
		shell_print(sh, "enabled injection: sensor-read-failure");
		return 0;
	}

	if (strcmp(fault_name, "stale-publication") == 0) {
		fault_injection_enable(FAULT_INJECTION_STALE_PUBLICATION);
		shell_print(sh, "enabled injection: stale-publication");
		return 0;
	}

	if (strcmp(fault_name, "processing-delay") == 0) {
		fault_injection_enable(FAULT_INJECTION_PROCESSING_DELAY);
		shell_print(sh, "enabled injection: processing-delay");
		return 0;
	}

	if (strcmp(fault_name, "queue-pressure") == 0) {
		fault_injection_enable(FAULT_INJECTION_QUEUE_PRESSURE);
		shell_print(sh, "enabled injection: queue-pressure");
		return 0;
	}

	if (strcmp(fault_name, "invalid-measurement") == 0) {
		fault_injection_enable(FAULT_INJECTION_INVALID_MEASUREMENT);
		shell_print(sh, "enabled injection: invalid-measurement");
		return 0;
	}

	if (strcmp(fault_name, "clear") == 0) {
		fault_injection_clear_all();
		shell_print(sh, "all injected faults cleared");
		return 0;
	}

	shell_error(sh, "unknown injection: %s", fault_name);
	shell_error(sh, "valid injections: sensor-failure stale-publication processing-delay queue-pressure invalid-measurement clear");

	return -EINVAL;
}

static int cmd_node(const struct shell *sh, size_t argc, char **argv)
{
	const char *subcmd;

	if (argc < 2 || argc > 3) {
		shell_error(sh, "usage: node <status|latest|stats|timing|faults|reset-stats|thresholds|inject>");
		return -EINVAL;
	}

	subcmd = argv[1];

	if (strcmp(subcmd, "inject") == 0) {
		return cmd_node_inject(sh, argc, argv);
	}

	if (argc != 2) {
		shell_error(sh, "command does not accept extra arguments: %s",
			    subcmd);
		return -EINVAL;
	}

	if (strcmp(subcmd, "status") == 0) {
		return cmd_node_status(sh);
	}

	if (strcmp(subcmd, "latest") == 0) {
		return cmd_node_latest(sh);
	}

	if (strcmp(subcmd, "stats") == 0) {
		return cmd_node_stats(sh);
	}

	if (strcmp(subcmd, "timing") == 0) {
		return cmd_node_timing(sh);
	}

	if (strcmp(subcmd, "faults") == 0) {
		return cmd_node_faults(sh);
	}

	if (strcmp(subcmd, "reset-stats") == 0) {
		return cmd_node_reset_stats(sh);
	}

	if (strcmp(subcmd, "thresholds") == 0) {
		return cmd_node_thresholds(sh);
	}

	shell_error(sh, "unknown node command: %s", subcmd);
	shell_error(sh, "valid commands: status latest stats timing faults reset-stats thresholds inject");

	return -EINVAL;
}

SHELL_CMD_ARG_REGISTER(node,
		       NULL,
		       "FieldSense-Z diagnostic commands",
		       cmd_node,
		       2,
		       1);