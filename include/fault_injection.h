#ifndef FAULT_INJECTION_H_
#define FAULT_INJECTION_H_

#include <stdbool.h>
#include <stdint.h>

#include <zephyr/sys/util.h>

#define FAULT_INJECTION_SENSOR_READ_FAILURE BIT(0)
#define FAULT_INJECTION_STALE_PUBLICATION  BIT(1)
#define FAULT_INJECTION_PROCESSING_DELAY   BIT(2)
#define FAULT_INJECTION_QUEUE_PRESSURE     BIT(3)
#define FAULT_INJECTION_INVALID_MEASUREMENT BIT(4)

#define FAULT_INJECTION_ALL_MASK \
	(FAULT_INJECTION_SENSOR_READ_FAILURE | \
	 FAULT_INJECTION_STALE_PUBLICATION | \
	 FAULT_INJECTION_PROCESSING_DELAY | \
	 FAULT_INJECTION_QUEUE_PRESSURE | \
	 FAULT_INJECTION_INVALID_MEASUREMENT)

#define FAULT_INJECTION_STALE_AGE_MS 7000U
#define FAULT_INJECTION_PROCESSING_DELAY_MS 3500U
#define FAULT_INJECTION_QUEUE_PRESSURE_BURST_COUNT 6U

#define FAULT_INJECTION_INVALID_TEMP_MILLI_C 200000
#define FAULT_INJECTION_INVALID_PRESSURE_PA 100000

void fault_injection_init(void);

void fault_injection_enable(uint32_t mask);

void fault_injection_clear(uint32_t mask);

void fault_injection_clear_all(void);

uint32_t fault_injection_get_mask(void);

bool fault_injection_is_active(uint32_t mask);

#endif /* FAULT_INJECTION_H_ */