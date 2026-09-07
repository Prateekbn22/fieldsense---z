# Timing Analysis

## Configured timing

The firmware uses a requested sampling period of:

- 2000 ms

Missed deadline threshold:

- 2250 ms

Stale data threshold:

- 6000 ms

## Normal measurement timing

Measured normal timing:

| Metric | Value |
|---|---:|
| requested_period | 2000 ms |
| latest_interval | 2070 ms |
| minimum_interval | 2070 ms |
| maximum_interval | 2071 ms |
| mean_interval | 2070 ms |
| scheduler_delay | about 70 ms |
| missed_deadlines | 0 |
| stale_data | no |

## Stale-data test

During stale-publication injection:

| Metric | Observed behavior |
|---|---|
| last_valid_sample_age | 7000 ms |
| stale_data | yes |
| node_health | FAULT |
| last_fault_reason | STALE_DATA |

After clearing injection:

| Metric | Observed behavior |
|---|---|
| node_health | HEALTHY |
| stale_data | no |
| active_injections | none |

## Queue-pressure timing

During queue pressure and processing delay:

| Metric | Observed behavior |
|---|---|
| queue_full_count | increased up to 101 |
| missed deadlines | increased during stress |
| stale_data | yes during stress |
| node_health | FAULT during stress |
| recovery | returned to HEALTHY after clearing injections |

## Stability run timing

The 40-minute stability run showed:

| Metric | Value |
|---|---:|
| requested_period | 2000 ms |
| latest_interval | 2071 ms |
| minimum_interval | 2070 ms |
| maximum_interval | 2071 ms |
| mean_interval | 2070 ms |
| scheduler_delay | 71 ms |
| missed_deadlines | 0 |
| stale_data | no |

## Interpretation

The normal and stability timing results show that the implemented pipeline maintained a consistent sampling interval and did not miss deadlines under normal operating conditions. Missed deadlines appeared during intentional stress testing, which is expected behavior for the processing-delay and queue-pressure validation.
