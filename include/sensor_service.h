#ifndef SENSOR_SERVICE_H_
#define SENSOR_SERVICE_H_

#include "app_types.h"

int sensor_service_init(void);

int sensor_service_read(struct sensor_sample *sample);

const char *sensor_service_device_name(void);

const char *sensor_sample_status_to_string(enum sensor_sample_status status);

#endif /* SENSOR_SERVICE_H_ */
