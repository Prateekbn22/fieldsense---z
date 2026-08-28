#ifndef DIAGNOSTICS_H_
#define DIAGNOSTICS_H_

#include <stdbool.h>
#include <stdint.h>

#include "app_types.h"
#include "env_stats.h"
#include "state_model.h"
#include "timing_metrics.h"

struct diagnostics_snapshot_update {
	uint32_t processed_count;
	uint32_t valid_sample_count;
	uint32_t invalid_sample_count;
	uint32_t sequence_gap_count;
	uint32_t queue_full_count;

	bool latest_valid_available;
	struct sensor_sample latest_valid_sample;

	struct environmental_stats stats;
	struct timing_metrics timing;
	struct state_model system_state;

	uint32_t update_time_ms;
};

void diagnostics_init(void);

void diagnostics_publish_snapshot(
	const struct diagnostics_snapshot_update *update);

bool diagnostics_reset_stats_requested_take(void);

#endif /* DIAGNOSTICS_H_ */