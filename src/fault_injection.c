#include <stdbool.h>
#include <stdint.h>

#include <zephyr/sys/atomic.h>

#include "fault_injection.h"

static atomic_t active_fault_injection_mask;

void fault_injection_init(void)
{
	atomic_set(&active_fault_injection_mask, 0);
}

void fault_injection_enable(uint32_t mask)
{
	atomic_or(&active_fault_injection_mask, (atomic_val_t)mask);
}

void fault_injection_clear(uint32_t mask)
{
	atomic_and(&active_fault_injection_mask, (atomic_val_t)(~mask));
}

void fault_injection_clear_all(void)
{
	atomic_set(&active_fault_injection_mask, 0);
}

uint32_t fault_injection_get_mask(void)
{
	return (uint32_t)atomic_get(&active_fault_injection_mask);
}

bool fault_injection_is_active(uint32_t mask)
{
	return (fault_injection_get_mask() & mask) != 0U;
}