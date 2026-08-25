#ifndef APP_TYPES_H_
#define APP_TYPES_H_

#include <stdbool.h>
#include <stdint.h>

enum sensor_sample_status {
SENSOR_SAMPLE_STATUS_OK = 0,
SENSOR_SAMPLE_STATUS_DEVICE_NOT_READY,
SENSOR_SAMPLE_STATUS_FETCH_FAILED,
SENSOR_SAMPLE_STATUS_TEMPERATURE_FAILED,
SENSOR_SAMPLE_STATUS_PRESSURE_FAILED,
SENSOR_SAMPLE_STATUS_HUMIDITY_FAILED,
};

struct sensor_sample {
uint32_t timestamp_ms;
uint32_t sequence;

int32_t temperature_milli_celsius;
int32_t pressure_pa;

bool humidity_supported;
int32_t humidity_milli_percent_rh;

bool valid;
enum sensor_sample_status status;
int driver_error;
};

#endif /* APP_TYPES_H_ */
