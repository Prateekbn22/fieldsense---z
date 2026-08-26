#ifndef ENV_STATS_H_
#define ENV_STATS_H_

#include <stdbool.h>
#include <stdint.h>

#include "app_types.h"

#define ENV_STATS_WINDOW_SIZE 5U

struct measurement_stats {
	bool has_value;
	uint32_t valid_count;

	int32_t latest;
	int32_t minimum;
	int32_t maximum;

	int32_t moving_average;
	int32_t window[ENV_STATS_WINDOW_SIZE];
	uint8_t window_count;
	uint8_t window_index;
	int64_t window_sum;
};

struct environmental_stats {
	struct measurement_stats temperature_milli_celsius;
	struct measurement_stats pressure_pa;
};

void env_stats_init(struct environmental_stats *stats);

void env_stats_measurement_reset(struct measurement_stats *stats);

void env_stats_measurement_update(struct measurement_stats *stats,
				  int32_t value);

void env_stats_update_from_sample(struct environmental_stats *stats,
				  const struct sensor_sample *sample);

bool env_stats_controlled_self_test(void);

#endif /* ENV_STATS_H_ */