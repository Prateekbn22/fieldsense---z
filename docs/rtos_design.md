\## Sensor acquisition thread



FieldSense-Z now has one dedicated Zephyr thread for periodic environmental sensor acquisition.



\### Thread purpose



The acquisition thread is responsible for:



\- waking periodically,

\- reading the environmental sensor through `sensor\_service\_read()`,

\- receiving a timestamped `sensor\_sample`,

\- logging success or failure,

\- continuing after recoverable read errors.



No message queue is used in this milestone. The acquisition thread logs samples directly.



\### RTOS concepts learned



A thread is an independent path of execution with its own stack, entry function, and priority.



The scheduler decides which ready thread runs.



A running thread is currently executing on the CPU.



A ready thread can run but has not been selected yet.



A sleeping thread is waiting for time to pass, such as after `k\_sleep()`.



A blocked thread is waiting for an operation or kernel object, such as an I2C transfer or a future message queue.



A context switch happens when the kernel saves one thread's CPU state and restores another thread's state.



\### Initial configuration



The acquisition thread uses:



\- Priority: `5`

\- Stack size: `2048` bytes

\- Sample period: `2000` ms



Priority `5` was chosen because environmental sampling is periodic and not urgent.



Stack size `2048` bytes was chosen as a conservative starting value because the thread calls logging, sensor service code, Zephyr sensor APIs, and the I2C driver path. This value should later be measured and tuned instead of treated as permanent.



The sample period of `2000` ms was chosen to match the previous working sensor application and make timestamp verification easy in serial logs.



\### Verification



The serial log showed:



\- increasing sequence numbers,

\- increasing timestamps,

\- approximately 2000 ms between samples,

\- valid temperature and pressure readings,

\- humidity reported as unsupported for BMP280,

\- the acquisition thread continuing instead of crashing.

## Sensor message queue

FieldSense-Z now uses a Zephyr message queue between the sensor acquisition thread and a temporary consumer thread.

Current data path:

```text
sensor acquisition thread
        |
        v
      k_msgq
        |
        v
temporary consumer thread

## Environmental processing thread

FieldSense-Z now separates sensor acquisition from environmental processing.

Current data path:

```text
sensor acquisition thread
        |
        v
      k_msgq
        |
        v
environmental processing thread

## Sampling timing and freshness metrics

FieldSense-Z now measures requested timing versus actual RTOS behavior.

### Requested period

The requested sampling period is:

```text
2000 ms

## Structured Zephyr logging

FieldSense-Z now uses Zephyr structured logging instead of temporary `printk()` output.

### Why structured logging was added

The project now has multiple RTOS responsibilities:

- sensor acquisition,
- message queue publishing,
- processing,
- statistics,
- timing metrics,
- node health state,
- environmental status state.

Printing every internal operation creates log flooding and makes real problems harder to see.

Structured logging improves observability by logging important events without overwhelming the serial console.

### Logging concepts used

A log module identifies the source of a message.

Severity levels describe importance:

- `ERR`: real error or fault condition
- `WRN`: abnormal but recoverable condition
- `INF`: important normal event
- `DBG`: detailed debug information

Deferred logging is enabled so application threads do not spend as much time directly printing to the console.

### Events logged

The firmware now logs:

- boot,
- logging mode,
- sensor initialization,
- self-test results,
- health transitions,
- environmental transitions,
- queue overflow,
- missed deadlines,
- stale data,
- qualified recovery,
- periodic summaries.

### Log flooding control

The firmware avoids printing every internal operation.

Normal per-sample publish details are debug-level only.

The processing thread prints periodic summaries instead of printing every statistic every cycle.

Important events such as queue overflow, missed deadlines, stale data, and state transitions are logged immediately.

### Example observation

During the structured logging run, the node reached:

```text
Node health: HEALTHY
Environmental status: HIGH_TEMPERATURE

## Runtime diagnostic shell

FieldSense-Z now includes a runtime diagnostic shell for validation.

The shell provides runtime introspection without reflashing firmware.

Commands include:

```text
node status
node latest
node stats
node timing
node faults
node reset-stats
node thresholds
## Queue backpressure and recovery validation

FieldSense-Z uses a producer/consumer RTOS structure.

The acquisition thread is the producer. It reads the BMP280 sensor and publishes samples into a finite Zephyr message queue.

The processing thread is the consumer. It removes samples from the queue, validates them, updates statistics, updates timing metrics, and updates the health state machine.

### Producer/consumer rate imbalance

A producer/consumer rate imbalance happens when the producer creates samples faster than the consumer can process them.

In FieldSense-Z, this can happen during processing-delay injection. The acquisition thread continues producing samples every 2000 ms, but the processing thread is intentionally slowed down.

### Finite queue capacity

The sample queue has a fixed depth.

Because the queue is finite, it can absorb temporary bursts but cannot grow forever.

Queue occupancy is visible through the diagnostic shell using:

```text
node status
```

The shell reports:

```text
queue_used_count
queue_free_count
queue_depth
queue_full_count
```

### Dropping newest versus oldest

FieldSense-Z uses a drop-newest policy.

When the queue is full, the newest failed publication is dropped and the oldest queued samples are preserved.

This keeps already accepted work in order and prevents the acquisition thread from blocking forever.

### Blocking versus nonblocking publication

A blocking publish could stall the acquisition thread when the processing thread is slow.

FieldSense-Z uses nonblocking publication with `K_NO_WAIT`.

If the queue is full, publication fails immediately, the queue-full counter increases, and the sample is dropped.

### Backpressure

Backpressure means the firmware can observe that the consumer is falling behind.

In this project, backpressure is visible through:

- queue occupancy,
- queue-full count,
- queue-overflow events,
- missed-deadline events,
- health-state transitions.

### Controlled validation sequence

The controlled sequence verified was:

```text
normal operation
→ slow processing
→ queue occupancy rises
→ queue-full policy activates
→ normal processing resumes
→ queue drains
→ recovery criteria are met
```

### Shared-state safety

The processing thread owns the live statistics, timing metrics, and state model.

The diagnostic shell does not directly read live processing-thread variables.

Instead, the processing thread publishes a diagnostic snapshot.

The diagnostic snapshot is protected by a mutex.

The queue-full counter is atomic because it can be updated by the acquisition thread and read by the processing thread and diagnostic shell.

The fault-injection mask is accessed through the fault-injection service instead of exposing raw shared state directly.

