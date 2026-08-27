#ifndef TIMING_METRICS_H_
#define TIMING_METRICS_H_

#include <stdbool.h>
#include <stdint.h>

#include "app_types.h"

struct timing_metrics {
	uint32_t requested_period_ms;
	uint32_t missed_tolerance_ms;
	uint32_t stale_threshold_ms;

	bool have_previous_sample;
	uint32_t previous_sample_timestamp_ms;

	bool have_last_valid_sample;
	uint32_t last_valid_sample_timestamp_ms;

	uint32_t interval_count;
	uint32_t latest_interval_ms;
	uint32_t minimum_interval_ms;
	uint32_t maximum_interval_ms;
	uint64_t interval_sum_ms;
	uint32_t mean_interval_ms;

	int32_t latest_scheduler_delay_ms;
	uint32_t missed_deadline_count;

	uint32_t last_valid_sample_age_ms;
	bool stale_data;
};

void timing_metrics_init(struct timing_metrics *metrics,
			 uint32_t requested_period_ms,
			 uint32_t missed_tolerance_ms,
			 uint32_t stale_threshold_ms);

void timing_metrics_update(struct timing_metrics *metrics,
			   const struct sensor_sample *sample,
			   uint32_t now_ms);

#endif /* TIMING_METRICS_H_ */