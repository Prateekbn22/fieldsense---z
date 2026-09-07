# Resource Analysis

## Purpose

This document records measured resource usage for the implemented FieldSense-Z firmware.

The goal was to measure resource usage instead of guessing and not to shrink stacks only for better-looking numbers.

## Runtime stack measurements

Measured at the end of the 40-minute stability run using node threads.

| Thread | Unused stack | Used stack | Allocated stack | Usage |
|---|---:|---:|---:|---:|
| fieldsense_proc | 896 bytes | 1152 bytes | 2048 bytes | 56 percent |
| fieldsense_acq | 1248 bytes | 800 bytes | 2048 bytes | 39 percent |
| shell_uart | 128 bytes | 1920 bytes | 2048 bytes | 93 percent |
| logging | 736 bytes | 288 bytes | 1024 bytes | 28 percent |
| idle | 816 bytes | 208 bytes | 1024 bytes | 20 percent |
| ISR0 | 1504 bytes | 544 bytes | 2048 bytes | 26 percent |

The shell stack had the highest measured usage. It was not reduced.

## System workqueue note

The requested resource checklist included system workqueue stack usage. The captured thread analyzer output did not list a system workqueue entry. The measured results only claim the threads that appeared in the captured output.

## Queue memory

The implemented sample queue depth is:

- 4 samples

The queue stores sensor_sample objects and exposes queue usage through diagnostics:

- queue_used_count
- queue_free_count
- queue_depth
- queue_full_count

During normal and stability validation, queue_full_count remained 0. During queue pressure validation, queue_full_count increased as expected.

## Timing results

Stability run timing:

| Metric | Value |
|---|---:|
| requested_period | 2000 ms |
| latest_interval | 2071 ms |
| mean_interval | 2070 ms |
| missed_deadlines | 0 |
| stale_data | no |

## Boot-time memory section evidence

Cold boot output included ESP32 boot section information:

| Section | Captured size |
|---|---:|
| DRAM | 8432 bytes |
| IRAM | 43344 bytes |
| RTC_DATA | 40 bytes |
| IROM | 50896 bytes |
| DROM | 65536 bytes |
| libc heap | 175 kB |

These boot lines are useful evidence, but they are not a replacement for a full Zephyr rom_report or ram_report.

## Logging overhead

Logging was enabled and contributed to:

- log strings
- log formatting code
- logging thread stack
- logging backend behavior

Measured logging thread stack usage:

- 288 / 1024 bytes

## Shell overhead

The serial shell is useful for validation but has real cost.

Measured shell stack usage:

- 1920 / 2048 bytes

The shell was kept because it is central to diagnostics and validation.

## Blog-ready paragraph

For FieldSense-Z, I measured resource usage instead of guessing. In embedded systems, it is tempting to choose stack sizes and buffers based only on what seems reasonable, but that can hide real failure modes. I enabled Zephyr stack and thread analysis, collected runtime high-water stack usage for the acquisition thread, processing thread, shell, logging, idle, and ISR stack, and compared that with timing behavior from normal operation and a 40-minute stability run. This gave me evidence for how much memory the firmware actually used during sensor sampling, diagnostic-shell activity, fault injection, and recovery. I intentionally did not shrink stacks just to make the numbers look better, because safe embedded design needs margin for future code, logging, drivers, and rare error paths.
