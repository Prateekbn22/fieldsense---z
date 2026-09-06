# Resource Analysis

## Goal

This document explains how FieldSense-Z measures runtime and build-time resource usage.

The goal is to measure stack, RAM, flash, queue memory, logging overhead, shell overhead, and timing behavior instead of guessing.

## Terms

### Allocated thread stack

Allocated thread stack is the amount of RAM reserved for a thread stack.

FieldSense-Z has application threads for:

```text
fieldsense_acq
fieldsense_proc
```

The firmware also uses Zephyr/system threads such as:

```text
system workqueue
shell
idle
logging-related threads or backend work
```

### Stack high-water usage

Stack high-water usage is the largest amount of stack observed as used at runtime.

The project measures this using Zephyr thread analyzer output.

The important fields are:

```text
STACK: unused X usage Y / Z
```

Where:

```text
Z = allocated stack
Y = observed high-water used stack
X = unused stack
```

Stacks should not be reduced just to make numbers look tight.

A safe embedded design keeps margin because future logging, error paths, shell commands, and driver behavior can use more stack.

### Static RAM

Static RAM is RAM allocated at build time.

This includes:

```text
global variables
kernel objects
thread stacks
message queue storage
logging buffers
shell buffers
driver state
```

### Flash

Flash stores firmware code and read-only data.

This includes:

```text
application code
Zephyr kernel code
drivers
shell command tables
logging strings
constant data
```

### Queue memory

FieldSense-Z uses a finite Zephyr message queue for sensor samples.

The main queue payload allocation is:

```text
sizeof(struct sensor_sample) × SENSOR_SAMPLE_QUEUE_DEPTH
```

The firmware also has kernel metadata for the queue object.

### Logging overhead

Logging overhead comes from:

```text
log strings
log formatting code
log buffers
logging backend code
deferred logging support
```

Logging is useful during validation, but it increases flash and RAM use.

### Shell overhead

Shell overhead comes from:

```text
serial shell backend
shell command tables
shell buffers
shell thread stack
command parsing code
```

The shell is valuable for diagnostics and interview demonstration, but it is not free.

## Measurement method

Resource usage is measured using:

```text
Zephyr build memory summary
ram_report
rom_report
thread analyzer
node timing
node status
node faults
```

Build-time evidence shows flash and static RAM.

Runtime evidence shows stack high-water usage and sampling timing.

## What was measured

The resource analysis measured:

```text
acquisition stack usage
processing stack usage
system workqueue stack usage
shell stack usage
flash usage
RAM usage
message queue allocation
sampling timing
missed deadlines
```

## Important rule

Stacks were not reduced in this milestone.

The goal was to measure and document actual usage first.

Optimization should only happen after enough evidence is collected across normal operation, fault injection, shell usage, and recovery paths.

## Blog-ready paragraph

For FieldSense-Z, I measured resource usage instead of guessing. In embedded systems, it is tempting to choose stack sizes and buffers based only on what seems reasonable, but that can hide real failure modes. I enabled Zephyr stack and thread analysis, collected runtime high-water stack usage for the acquisition thread, processing thread, shell, and system workqueue, and compared that with build-time flash and RAM reports. This gave me evidence for how much memory the firmware actually used during normal sampling, diagnostic-shell activity, and delayed-processing fault scenarios. I intentionally did not shrink stacks just to make the numbers look better, because safe embedded design needs margin for future code, logging, drivers, and rare error paths.

## Evidence files

Actual evidence is saved in:

```text
results/logs/thread_analysis.txt
results/resource_usage.md
```
