# RTOS Design

## Threads

FieldSense-Z uses dedicated application threads:

| Thread | Purpose |
|---|---|
| fieldsense_acq | Sensor acquisition |
| fieldsense_proc | Sample processing, statistics, timing, and state updates |

Zephyr system threads such as shell, logging, idle, and ISR context were also visible in thread analyzer output.

## Message queue

The acquisition thread sends sensor_sample objects into a Zephyr message queue.

Queue depth:

- 4 samples

Queue pressure behavior:

- non-blocking publish
- preserve existing queued samples
- drop newest sample on full queue
- count queue_full events
- expose queue counters through node status and node faults

## Sampling timing

Configured sampling period:

- 2000 ms

Measured normal and stability timing:

| Metric | Observed value |
|---|---:|
| latest_interval | about 2070 to 2071 ms |
| mean_interval | about 2070 ms |
| missed_deadlines during normal/stability | 0 |

## Fault behavior related to RTOS timing

Processing-delay and queue-pressure injection produced:

- queue_full_count increase
- queue overflow logs
- missed deadlines
- sequence gaps
- FAULT state
- later recovery to HEALTHY after injections were cleared

## Stack usage

Measured stack high-water results from the stability run:

| Thread | Used | Allocated | Usage |
|---|---:|---:|---:|
| fieldsense_proc | 1152 bytes | 2048 bytes | 56 percent |
| fieldsense_acq | 800 bytes | 2048 bytes | 39 percent |
| shell_uart | 1920 bytes | 2048 bytes | 93 percent |
| logging | 288 bytes | 1024 bytes | 28 percent |
| idle | 208 bytes | 1024 bytes | 20 percent |
| ISR0 | 544 bytes | 2048 bytes | 26 percent |

Stacks were not reduced just to make the results look better.
