#include <string.h>

#include "timing_metrics.h"

static bool sample_is_valid_for_freshness(const struct sensor_sample *sample)
{
	return sample->valid &&
	       sample->status == SENSOR_SAMPLE_STATUS_OK &&
	       sample->driver_error == 0;
}

void timing_metrics_init(struct timing_metrics *metrics,
			 uint32_t requested_period_ms,
			 uint32_t missed_tolerance_ms,
			 uint32_t stale_threshold_ms)
{
	if (metrics == NULL) {
		return;
	}

	memset(metrics, 0, sizeof(*metrics));

	metrics->requested_period_ms = requested_period_ms;
	metrics->missed_tolerance_ms = missed_tolerance_ms;
	metrics->stale_threshold_ms = stale_threshold_ms;
}

void timing_metrics_update(struct timing_metrics *metrics,
			   const struct sensor_sample *sample,
			   uint32_t now_ms)
{
	uint32_t interval_ms;

	if (metrics == NULL || sample == NULL) {
		return;
	}

	if (metrics->have_previous_sample) {
		interval_ms = sample->timestamp_ms -
			      metrics->previous_sample_timestamp_ms;

		metrics->latest_interval_ms = interval_ms;

		if (metrics->interval_count == 0U) {
			metrics->minimum_interval_ms = interval_ms;
			metrics->maximum_interval_ms = interval_ms;
		} else {
			if (interval_ms < metrics->minimum_interval_ms) {
				metrics->minimum_interval_ms = interval_ms;
			}

			if (interval_ms > metrics->maximum_interval_ms) {
				metrics->maximum_interval_ms = interval_ms;
			}
		}

		metrics->interval_count++;
		metrics->interval_sum_ms += interval_ms;
		metrics->mean_interval_ms =
			(uint32_t)(metrics->interval_sum_ms /
				   metrics->interval_count);

		metrics->latest_scheduler_delay_ms =
			(int32_t)interval_ms -
			(int32_t)metrics->requested_period_ms;

		if (interval_ms >
		    (metrics->requested_period_ms +
		     metrics->missed_tolerance_ms)) {
			metrics->missed_deadline_count++;
		}
	}

	metrics->previous_sample_timestamp_ms = sample->timestamp_ms;
	metrics->have_previous_sample = true;

	if (sample_is_valid_for_freshness(sample)) {
		metrics->last_valid_sample_timestamp_ms =
			sample->timestamp_ms;
		metrics->have_last_valid_sample = true;
	}

	if (metrics->have_last_valid_sample) {
		metrics->last_valid_sample_age_ms =
			now_ms - metrics->last_valid_sample_timestamp_ms;

		metrics->stale_data =
			metrics->last_valid_sample_age_ms >
			metrics->stale_threshold_ms;
	}
}