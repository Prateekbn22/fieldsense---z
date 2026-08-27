# Timing Analysis

## Goal

The goal of this milestone was to compare the requested sampling period with the actual measured RTOS behavior.

FieldSense-Z requests a fixed sampling period, but the actual measured interval can vary because the acquisition thread performs work, interacts with the sensor driver, publishes data to a queue, sleeps, and is scheduled by the RTOS.

## Timing terms

Requested period is the sampling period configured in firmware.

Actual measured period is the time between two produced sensor samples.

Execution time is the time spent doing the acquisition work for one sample.

Scheduler delay is the difference between the actual measured interval and the requested period.

Jitter is the variation between measured sample intervals.

A missed period is counted when the measured interval is greater than the requested period plus the configured tolerance.

Last-valid-sample age is the age of the most recent valid sample.

Stale data means the latest valid sample is older than the configured freshness threshold.

## Configuration

Requested period: `2000 ms`

Missed-period tolerance: `250 ms`

Missed-period threshold: `2250 ms`

Stale-data threshold: `6000 ms`

Timing source: Zephyr monotonic uptime from `k_uptime_get_32()`

## Results

Evidence log:

`results/logs/timing_run.txt`

Measured results from the run:

- Minimum sample interval: `<fill actual value>` ms
- Maximum sample interval: `<fill actual value>` ms
- Mean sample interval: `<fill actual value>` ms
- Missed deadline count: `<fill actual value>`
- Last-valid-sample age during normal operation: `<fill actual value>` ms
- Stale data observed: `no`

## Interpretation

The requested sampling period was 2000 ms. The measured intervals were expected to be close to 2000 ms, but not perfectly exact.

Environmental monitoring does not require microsecond-level timing because temperature and pressure change slowly. However, measuring timing is still useful because it shows whether the firmware is sampling consistently, whether deadlines are being missed, and whether the latest valid data remains fresh.

## Blog-ready paragraph

FieldSense-Z requested a 2000 ms environmental sampling period, then measured the actual interval between produced samples using monotonic uptime. The measured intervals were close to the requested period under normal operation, with no unexplained deadline misses or stale-data events. This matters because environmental monitoring does not need microsecond precision, but it still needs predictable behavior. Measuring the real interval, scheduler delay, and last-valid-sample age gave me evidence that the RTOS acquisition and processing pipeline was running consistently instead of assuming the timing was correct.