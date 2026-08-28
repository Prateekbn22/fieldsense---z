#include <errno.h>
#include <stdint.h>
#include <string.h>

#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/kernel.h>

#include "sensor_service.h"
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(sensor_service, LOG_LEVEL_INF);

#define FIELDSENSE_SENSOR_NODE DT_ALIAS(fieldsense_env_sensor)

#if !DT_NODE_HAS_STATUS(FIELDSENSE_SENSOR_NODE, okay)
#error "FieldSense-Z environmental sensor alias is not defined or not okay"
#endif

static const struct device *const env_sensor =
	DEVICE_DT_GET(FIELDSENSE_SENSOR_NODE);

static uint32_t next_sequence = 1;

static int32_t fieldsense_sensor_value_to_milli(const struct sensor_value *value)
{
	return (int32_t)(((int64_t)value->val1 * 1000) +
			(value->val2 / 1000));
}

static int32_t fieldsense_sensor_value_kpa_to_pa(const struct sensor_value *value)
{
	return (int32_t)(((int64_t)value->val1 * 1000) +
			(value->val2 / 1000));
}

static void sensor_sample_clear(struct sensor_sample *sample)
{
	memset(sample, 0, sizeof(*sample));

	sample->timestamp_ms = k_uptime_get_32();
	sample->sequence = next_sequence++;
	sample->valid = false;
	sample->status = SENSOR_SAMPLE_STATUS_DEVICE_NOT_READY;
	sample->driver_error = 0;
}

int sensor_service_init(void)
{
	if (!device_is_ready(env_sensor)) {
                LOG_ERR("sensor device not ready: %s", env_sensor->name);
		return -ENODEV;
	}
        LOG_INF("sensor initialized: %s", env_sensor->name);

	return 0;
}

const char *sensor_service_device_name(void)
{
	return env_sensor->name;
}

int sensor_service_read(struct sensor_sample *sample)
{
	struct sensor_value value;
	int ret;

	if (sample == NULL) {
		return -EINVAL;
	}

	sensor_sample_clear(sample);

	if (!device_is_ready(env_sensor)) {
		sample->status = SENSOR_SAMPLE_STATUS_DEVICE_NOT_READY;
		sample->driver_error = -ENODEV;
		return -ENODEV;
	}

	ret = sensor_sample_fetch(env_sensor);
	if (ret != 0) {
		sample->status = SENSOR_SAMPLE_STATUS_FETCH_FAILED;
		sample->driver_error = ret;
                LOG_WRN("sensor sample fetch failed ret=%d", ret);
		return ret;
	}

	ret = sensor_channel_get(env_sensor, SENSOR_CHAN_AMBIENT_TEMP, &value);
	if (ret != 0) {
		sample->status = SENSOR_SAMPLE_STATUS_TEMPERATURE_FAILED;
		sample->driver_error = ret;
		return ret;
	}

	sample->temperature_milli_celsius =
		fieldsense_sensor_value_to_milli(&value);

	ret = sensor_channel_get(env_sensor, SENSOR_CHAN_PRESS, &value);
	if (ret != 0) {
		sample->status = SENSOR_SAMPLE_STATUS_PRESSURE_FAILED;
		sample->driver_error = ret;
		return ret;
	}

	sample->pressure_pa =
		fieldsense_sensor_value_kpa_to_pa(&value);

	ret = sensor_channel_get(env_sensor, SENSOR_CHAN_HUMIDITY, &value);
	if (ret == 0) {
		sample->humidity_supported = true;
		sample->humidity_milli_percent_rh =
			fieldsense_sensor_value_to_milli(&value);
	} else if (ret == -ENOTSUP) {
		sample->humidity_supported = false;
		sample->humidity_milli_percent_rh = 0;
	} else {
		sample->status = SENSOR_SAMPLE_STATUS_HUMIDITY_FAILED;
		sample->driver_error = ret;
		return ret;
	}

	sample->valid = true;
	sample->status = SENSOR_SAMPLE_STATUS_OK;
	sample->driver_error = 0;

	return 0;
}

const char *sensor_sample_status_to_string(enum sensor_sample_status status)
{
	switch (status) {
	case SENSOR_SAMPLE_STATUS_OK:
		return "OK";
	case SENSOR_SAMPLE_STATUS_DEVICE_NOT_READY:
		return "DEVICE_NOT_READY";
	case SENSOR_SAMPLE_STATUS_FETCH_FAILED:
		return "FETCH_FAILED";
	case SENSOR_SAMPLE_STATUS_TEMPERATURE_FAILED:
		return "TEMPERATURE_FAILED";
	case SENSOR_SAMPLE_STATUS_PRESSURE_FAILED:
		return "PRESSURE_FAILED";
	case SENSOR_SAMPLE_STATUS_HUMIDITY_FAILED:
		return "HUMIDITY_FAILED";
	default:
		return "UNKNOWN";
	}
}