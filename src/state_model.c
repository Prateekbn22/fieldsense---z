#include <stdbool.h>
#include <string.h>

#include "state_model.h"

static void set_node_health(struct state_model *model,
			    enum node_health_state next_state)
{
	if (model->node_health != next_state) {
		model->node_health = next_state;
		model->node_health_transition_count++;
	}
}

static void set_environmental_status(struct state_model *model,
				     enum environmental_status_state next_state)
{
	if (model->environmental_status != next_state) {
		model->environmental_status = next_state;
		model->environmental_transition_count++;
	}
}

static void enter_fault(struct state_model *model,
			enum state_fault_reason reason)
{
	model->last_fault_reason = reason;
	set_node_health(model, NODE_HEALTH_FAULT);
}

static bool input_is_recovery_valid(const struct state_model_input *input)
{
	return input->sample_received &&
	       input->sample_valid &&
	       !input->stale_data &&
	       !input->missed_deadline_event &&
	       !input->queue_overflow_event;
}

static bool input_has_health_problem(const struct state_model_input *input)
{
	return !input->sample_valid ||
	       input->stale_data ||
	       input->missed_deadline_event ||
	       input->queue_overflow_event;
}

static void update_health_counters(struct state_model *model,
				   const struct state_model_input *input)
{
	if (!input->sample_received) {
		return;
	}

	if (input->sample_valid) {
		model->consecutive_sensor_failures = 0U;
	} else {
		model->consecutive_sensor_failures++;
	}

	if (input->stale_data) {
		model->stale_data_event_count++;
	}

	if (input->missed_deadline_event) {
		model->missed_deadline_event_count++;
	}

	if (input->queue_overflow_event) {
		model->queue_overflow_event_count++;
	}

	if (input_is_recovery_valid(input)) {
		model->consecutive_recovery_valid_samples++;
	} else {
		model->consecutive_recovery_valid_samples = 0U;
	}
}

static void clear_recoverable_counters(struct state_model *model)
{
	model->consecutive_sensor_failures = 0U;
	model->consecutive_recovery_valid_samples = 0U;
	model->stale_data_event_count = 0U;
	model->missed_deadline_event_count = 0U;
	model->queue_overflow_event_count = 0U;
}

static void update_node_health(struct state_model *model,
			       const struct state_model_input *input)
{
	bool health_problem;

	if (!input->sample_received) {
		return;
	}

	update_health_counters(model, input);

	if (model->consecutive_sensor_failures >=
	    STATE_SENSOR_FAILURES_BEFORE_FAULT) {
		enter_fault(model, STATE_FAULT_SENSOR_FAILURES);
		return;
	}

	if (model->stale_data_event_count >=
	    STATE_STALE_EVENTS_BEFORE_FAULT) {
		enter_fault(model, STATE_FAULT_STALE_DATA);
		return;
	}

	if (model->missed_deadline_event_count >=
	    STATE_MISSED_DEADLINES_BEFORE_FAULT) {
		enter_fault(model, STATE_FAULT_MISSED_DEADLINES);
		return;
	}

	if (model->queue_overflow_event_count >=
	    STATE_QUEUE_OVERFLOWS_BEFORE_FAULT) {
		enter_fault(model, STATE_FAULT_QUEUE_OVERFLOWS);
		return;
	}

	health_problem = input_has_health_problem(input);

	switch (model->node_health) {
	case NODE_HEALTH_INITIALIZING:
		if (input_is_recovery_valid(input)) {
			set_node_health(model, NODE_HEALTH_HEALTHY);
			clear_recoverable_counters(model);
		} else {
			set_node_health(model, NODE_HEALTH_WARNING);
		}
		break;

	case NODE_HEALTH_HEALTHY:
		if (health_problem) {
			set_node_health(model, NODE_HEALTH_WARNING);
		}
		break;

	case NODE_HEALTH_WARNING:
		if (input_is_recovery_valid(input) &&
		    model->consecutive_recovery_valid_samples >=
		    STATE_RECOVERY_VALID_SAMPLE_COUNT) {
			set_node_health(model, NODE_HEALTH_HEALTHY);
			clear_recoverable_counters(model);
		}
		break;

	case NODE_HEALTH_FAULT:
		if (input_is_recovery_valid(input) &&
		    model->consecutive_recovery_valid_samples >=
		    STATE_RECOVERY_VALID_SAMPLE_COUNT) {
			set_node_health(model, NODE_HEALTH_HEALTHY);
			clear_recoverable_counters(model);
		}
		break;

	default:
		set_node_health(model, NODE_HEALTH_FAULT);
		model->last_fault_reason = STATE_FAULT_SENSOR_FAILURES;
		break;
	}
}

static bool high_temperature_active(enum environmental_status_state current,
				    int32_t temperature_milli_celsius)
{
	if (temperature_milli_celsius >= STATE_HIGH_TEMP_ENTER_MILLI_C) {
		return true;
	}

	if (current == ENV_STATUS_HIGH_TEMPERATURE &&
	    temperature_milli_celsius > STATE_HIGH_TEMP_CLEAR_MILLI_C) {
		return true;
	}

	return false;
}

static bool pressure_alert_active(enum environmental_status_state current,
				  int32_t pressure_pa)
{
	if (pressure_pa < STATE_PRESSURE_LOW_ENTER_PA ||
	    pressure_pa > STATE_PRESSURE_HIGH_ENTER_PA) {
		return true;
	}

	if (current == ENV_STATUS_PRESSURE_ALERT &&
	    (pressure_pa < STATE_PRESSURE_LOW_CLEAR_PA ||
	     pressure_pa > STATE_PRESSURE_HIGH_CLEAR_PA)) {
		return true;
	}

	return false;
}

static void update_environmental_status(struct state_model *model,
					const struct state_model_input *input)
{
	bool high_temperature;
	bool pressure_alert;

	if (!input->sample_received ||
	    !input->sample_valid ||
	    input->stale_data) {
		set_environmental_status(model, ENV_STATUS_UNKNOWN);
		return;
	}

	high_temperature =
		high_temperature_active(model->environmental_status,
					input->temperature_milli_celsius);

	pressure_alert =
		pressure_alert_active(model->environmental_status,
				      input->pressure_pa);

	if (high_temperature) {
		set_environmental_status(model, ENV_STATUS_HIGH_TEMPERATURE);
	} else if (pressure_alert) {
		set_environmental_status(model, ENV_STATUS_PRESSURE_ALERT);
	} else {
		set_environmental_status(model, ENV_STATUS_NORMAL);
	}
}

void state_model_init(struct state_model *model)
{
	if (model == NULL) {
		return;
	}

	memset(model, 0, sizeof(*model));

	model->node_health = NODE_HEALTH_INITIALIZING;
	model->environmental_status = ENV_STATUS_UNKNOWN;
	model->last_fault_reason = STATE_FAULT_NONE;
}

void state_model_update(struct state_model *model,
			const struct state_model_input *input)
{
	if (model == NULL || input == NULL) {
		return;
	}

	update_node_health(model, input);
	update_environmental_status(model, input);
}

const char *node_health_state_to_string(enum node_health_state state)
{
	switch (state) {
	case NODE_HEALTH_INITIALIZING:
		return "INITIALIZING";
	case NODE_HEALTH_HEALTHY:
		return "HEALTHY";
	case NODE_HEALTH_WARNING:
		return "WARNING";
	case NODE_HEALTH_FAULT:
		return "FAULT";
	default:
		return "UNKNOWN_NODE_HEALTH";
	}
}

const char *environmental_status_to_string(enum environmental_status_state state)
{
	switch (state) {
	case ENV_STATUS_UNKNOWN:
		return "UNKNOWN";
	case ENV_STATUS_NORMAL:
		return "NORMAL";
	case ENV_STATUS_HIGH_TEMPERATURE:
		return "HIGH_TEMPERATURE";
	case ENV_STATUS_PRESSURE_ALERT:
		return "PRESSURE_ALERT";
	default:
		return "UNKNOWN_ENVIRONMENTAL_STATUS";
	}
}

const char *state_fault_reason_to_string(enum state_fault_reason reason)
{
	switch (reason) {
	case STATE_FAULT_NONE:
		return "NONE";
	case STATE_FAULT_SENSOR_FAILURES:
		return "SENSOR_FAILURES";
	case STATE_FAULT_STALE_DATA:
		return "STALE_DATA";
	case STATE_FAULT_MISSED_DEADLINES:
		return "MISSED_DEADLINES";
	case STATE_FAULT_QUEUE_OVERFLOWS:
		return "QUEUE_OVERFLOWS";
	default:
		return "UNKNOWN_FAULT_REASON";
	}
}

static struct state_model_input normal_input(void)
{
	struct state_model_input input = {
		.sample_received = true,
		.sample_valid = true,
		.temperature_milli_celsius = 25000,
		.pressure_pa = 100000,
		.stale_data = false,
		.missed_deadline_event = false,
		.queue_overflow_event = false,
	};

	return input;
}

static struct state_model_input invalid_input(void)
{
	struct state_model_input input = normal_input();

	input.sample_valid = false;

	return input;
}

static bool expect_state(const struct state_model *model,
			 enum node_health_state health,
			 enum environmental_status_state env)
{
	return model->node_health == health &&
	       model->environmental_status == env;
}

bool state_model_controlled_self_test(void)
{
	struct state_model model;
	struct state_model_input input;

	/* 1. Normal startup */
	state_model_init(&model);
	input = normal_input();
	state_model_update(&model, &input);

	if (!expect_state(&model, NODE_HEALTH_HEALTHY, ENV_STATUS_NORMAL)) {
		return false;
	}

	/* 2. Transient sensor error */
	input = invalid_input();
	state_model_update(&model, &input);

	if (!expect_state(&model, NODE_HEALTH_WARNING, ENV_STATUS_UNKNOWN)) {
		return false;
	}

	for (uint32_t i = 0U; i < STATE_RECOVERY_VALID_SAMPLE_COUNT; i++) {
		input = normal_input();
		state_model_update(&model, &input);
	}

	if (!expect_state(&model, NODE_HEALTH_HEALTHY, ENV_STATUS_NORMAL)) {
		return false;
	}

	/* 3. Repeated sensor errors */
	state_model_init(&model);
	input = normal_input();
	state_model_update(&model, &input);

	for (uint32_t i = 0U; i < STATE_SENSOR_FAILURES_BEFORE_FAULT; i++) {
		input = invalid_input();
		state_model_update(&model, &input);
	}

	if (!expect_state(&model, NODE_HEALTH_FAULT, ENV_STATUS_UNKNOWN) ||
	    model.last_fault_reason != STATE_FAULT_SENSOR_FAILURES) {
		return false;
	}

	/* 4. Stale data */
	state_model_init(&model);
	input = normal_input();
	state_model_update(&model, &input);

	for (uint32_t i = 0U; i < STATE_STALE_EVENTS_BEFORE_FAULT; i++) {
		input = normal_input();
		input.stale_data = true;
		state_model_update(&model, &input);
	}

	if (!expect_state(&model, NODE_HEALTH_FAULT, ENV_STATUS_UNKNOWN) ||
	    model.last_fault_reason != STATE_FAULT_STALE_DATA) {
		return false;
	}

	/* 5. Environmental alert */
	state_model_init(&model);
	input = normal_input();
	input.temperature_milli_celsius = 31000;
	state_model_update(&model, &input);

	if (!expect_state(&model,
			  NODE_HEALTH_HEALTHY,
			  ENV_STATUS_HIGH_TEMPERATURE)) {
		return false;
	}

	input.temperature_milli_celsius = 29000;
	state_model_update(&model, &input);

	if (model.environmental_status != ENV_STATUS_HIGH_TEMPERATURE) {
		return false;
	}

	input.temperature_milli_celsius = 28000;
	state_model_update(&model, &input);

	if (model.environmental_status != ENV_STATUS_NORMAL) {
		return false;
	}

	/* 6. Qualified recovery from FAULT */
	state_model_init(&model);
	input = normal_input();
	state_model_update(&model, &input);

	for (uint32_t i = 0U; i < STATE_SENSOR_FAILURES_BEFORE_FAULT; i++) {
		input = invalid_input();
		state_model_update(&model, &input);
	}

	if (model.node_health != NODE_HEALTH_FAULT) {
		return false;
	}

	for (uint32_t i = 0U; i < STATE_RECOVERY_VALID_SAMPLE_COUNT; i++) {
		input = normal_input();
		state_model_update(&model, &input);
	}

	if (!expect_state(&model, NODE_HEALTH_HEALTHY, ENV_STATUS_NORMAL)) {
		return false;
	}

	return true;
}