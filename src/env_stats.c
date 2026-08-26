#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "env_stats.h"

void env_stats_measurement_reset(struct measurement_stats *stats)
{
	if (stats == NULL) {
		return;
	}

	memset(stats, 0, sizeof(*stats));
}

void env_stats_init(struct environmental_stats *stats)
{
	if (stats == NULL) {
		return;
	}

	env_stats_measurement_reset(&stats->temperature_milli_celsius);
	env_stats_measurement_reset(&stats->pressure_pa);
}

void env_stats_measurement_update(struct measurement_stats *stats,
				  int32_t value)
{
	if (stats == NULL) {
		return;
	}

	stats->latest = value;

	if (!stats->has_value) {
		stats->minimum = value;
		stats->maximum = value;
		stats->has_value = true;
	} else {
		if (value < stats->minimum) {
			stats->minimum = value;
		}

		if (value > stats->maximum) {
			stats->maximum = value;
		}
	}

	stats->valid_count++;

	if (stats->window_count < ENV_STATS_WINDOW_SIZE) {
		stats->window[stats->window_index] = value;
		stats->window_sum += value;
		stats->window_count++;
		stats->window_index =
			(stats->window_index + 1U) % ENV_STATS_WINDOW_SIZE;
	} else {
		stats->window_sum -= stats->window[stats->window_index];
		stats->window[stats->window_index] = value;
		stats->window_sum += value;
		stats->window_index =
			(stats->window_index + 1U) % ENV_STATS_WINDOW_SIZE;
	}

	stats->moving_average =
		(int32_t)(stats->window_sum / (int64_t)stats->window_count);
}

void env_stats_update_from_sample(struct environmental_stats *stats,
				  const struct sensor_sample *sample)
{
	if (stats == NULL || sample == NULL) {
		return;
	}

	if (!sample->valid ||
	    sample->status != SENSOR_SAMPLE_STATUS_OK ||
	    sample->driver_error != 0) {
		return;
	}

	/*
	 * Current verified hardware is BMP280.
	 * Supported channels: temperature and pressure.
	 * Humidity statistics are intentionally not calculated.
	 */
	env_stats_measurement_update(&stats->temperature_milli_celsius,
				     sample->temperature_milli_celsius);

	env_stats_measurement_update(&stats->pressure_pa,
				     sample->pressure_pa);
}

bool env_stats_controlled_self_test(void)
{
	struct measurement_stats stats;
	const int32_t values[] = {
		22000,
		23000,
		21000,
		24000,
		25000,
		26000,
	};

	env_stats_measurement_reset(&stats);

	for (size_t i = 0; i < (sizeof(values) / sizeof(values[0])); i++) {
		env_stats_measurement_update(&stats, values[i]);
	}

	return stats.has_value &&
	       stats.latest == 26000 &&
	       stats.minimum == 21000 &&
	       stats.maximum == 26000 &&
	       stats.valid_count == 6 &&
	       stats.window_count == ENV_STATS_WINDOW_SIZE &&
	       stats.moving_average == 23800;
}