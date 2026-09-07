# Architecture

## Overview

FieldSense-Z is organized as a small RTOS application with a hardware-facing acquisition path, a processing path, and a diagnostic path.

## Main modules

| Module | Responsibility |
|---|---|
| main.c | RTOS thread setup, queue handling, processing loop |
| sensor_service.c | Sensor initialization and sample reads |
| app_types.h | Shared sample data types |
| env_stats.c | Environmental statistics |
| timing_metrics.c | Sampling interval, stale data, and deadline metrics |
| state_model.c | Node health and environmental status state machines |
| fault_injection.c | Deterministic software fault injection |
| diagnostics.c | Serial shell command interface |

## Runtime data flow

1. The acquisition thread fetches a sensor sample.
2. The sample is timestamped and assigned a sequence number.
3. The sample is published to a finite message queue.
4. The processing thread receives the sample.
5. Processing updates statistics, timing metrics, state model, and diagnostics snapshot.
6. Shell commands read the latest diagnostics snapshot.

## Queue behavior

The sample queue has depth 4.

When the queue is full, the implemented policy is:

- preserve older queued samples
- drop the newest sample
- increment queue_full_count
- record queue overflow behavior

This policy was validated during the queue pressure test.

## Diagnostic design

The diagnostic shell does not directly mutate internal processing state except through explicit commands such as reset-stats and fault injection. Runtime state is published as a snapshot so shell reads can be separated from the processing thread.
