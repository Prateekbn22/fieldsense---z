#ifndef STATE_MODEL_H_
#define STATE_MODEL_H_

#include <stdbool.h>
#include <stdint.h>

#define STATE_SENSOR_FAILURES_BEFORE_FAULT 3U
#define STATE_RECOVERY_VALID_SAMPLE_COUNT 5U

#define STATE_STALE_EVENTS_BEFORE_FAULT 2U
#define STATE_MISSED_DEADLINES_BEFORE_FAULT 3U
#define STATE_QUEUE_OVERFLOWS_BEFORE_FAULT 3U

#define STATE_HIGH_TEMP_ENTER_MILLI_C 30000
#define STATE_HIGH_TEMP_CLEAR_MILLI_C 28000

#define STATE_PRESSURE_LOW_ENTER_PA 95000
#define STATE_PRESSURE_HIGH_ENTER_PA 105000
#define STATE_PRESSURE_LOW_CLEAR_PA 97000
#define STATE_PRESSURE_HIGH_CLEAR_PA 103000

enum node_health_state {
	NODE_HEALTH_INITIALIZING = 0,
	NODE_HEALTH_HEALTHY,
	NODE_HEALTH_WARNING,
	NODE_HEALTH_FAULT,
};

enum environmental_status_state {
	ENV_STATUS_UNKNOWN = 0,
	ENV_STATUS_NORMAL,
	ENV_STATUS_HIGH_TEMPERATURE,
	ENV_STATUS_PRESSURE_ALERT,
};

enum state_fault_reason {
	STATE_FAULT_NONE = 0,
	STATE_FAULT_SENSOR_FAILURES,
	STATE_FAULT_STALE_DATA,
	STATE_FAULT_MISSED_DEADLINES,
	STATE_FAULT_QUEUE_OVERFLOWS,
};

struct state_model_input {
	bool sample_received;
	bool sample_valid;

	int32_t temperature_milli_celsius;
	int32_t pressure_pa;

	bool stale_data;
	bool missed_deadline_event;
	bool queue_overflow_event;
};

struct state_model {
	enum node_health_state node_health;
	enum environmental_status_state environmental_status;
	enum state_fault_reason last_fault_reason;

	uint32_t node_health_transition_count;
	uint32_t environmental_transition_count;

	uint32_t consecutive_sensor_failures;
	uint32_t consecutive_recovery_valid_samples;

	uint32_t stale_data_event_count;
	uint32_t missed_deadline_event_count;
	uint32_t queue_overflow_event_count;
};

void state_model_init(struct state_model *model);

void state_model_update(struct state_model *model,
			const struct state_model_input *input);

const char *node_health_state_to_string(enum node_health_state state);

const char *environmental_status_to_string(enum environmental_status_state state);

const char *state_fault_reason_to_string(enum state_fault_reason reason);

bool state_model_controlled_self_test(void);

#endif /* STATE_MODEL_H_ */