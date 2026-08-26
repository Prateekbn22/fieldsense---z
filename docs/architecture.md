\## Sensor service refactor



I refactored the environmental sensor logic out of `main.c` and into a small reusable module.



The purpose of this refactor was to separate hardware access from application flow.



\### Module responsibilities



`src/main.c`



\- Starts the application

\- Calls the sensor service

\- Prints samples

\- Handles the two-second loop

\- Does not directly call Zephyr sensor-driver APIs



`src/sensor\_service.c`



\- Owns access to the Zephyr sensor device

\- Calls `sensor\_sample\_fetch()`

\- Calls `sensor\_channel\_get()`

\- Converts Zephyr sensor values into explicit integer units

\- Propagates driver errors to the application



`include/sensor\_service.h`



\- Exposes the sensor service API

\- Keeps `main.c` independent of driver details



`include/app\_types.h`



\- Defines shared application data structures

\- Defines the `sensor\_sample` structure

\- Defines explicit units and sample status



\### Sensor sample data structure



The `sensor\_sample` structure contains only fields justified by FieldSense-Z:



\- `timestamp\_ms`: milliseconds from boot

\- `sequence`: increasing sample number

\- `temperature\_milli\_celsius`: temperature in thousandths of a degree Celsius

\- `pressure\_pa`: pressure in pascals

\- `humidity\_supported`: false for the current BMP280 hardware

\- `humidity\_milli\_percent\_rh`: humidity in thousandths of percent RH, only valid if supported

\- `valid`: true only when required channels were read successfully

\- `status`: application-level sample status

\- `driver\_error`: raw Zephyr driver error code



\### Why this matters



This keeps the project easier to grow. Later, when I add threads, queues, statistics, health states, or fault detection, those modules can consume `sensor\_sample` without knowing Bosch register details or Zephyr driver calls.

## RTOS acquisition architecture

The application now separates startup, acquisition, and sensor access.

Current structure:

`src/main.c`

- Starts the application
- Defines the sensor acquisition thread
- Keeps the main application entry point simple

`sensor_acquisition_thread`

- Runs periodically
- Calls `sensor_service_read()`
- Logs each sample directly for this milestone
- Continues after recoverable sensor read errors

`src/sensor_service.c`

- Owns Zephyr sensor API access
- Fetches sensor data
- Converts values into explicit integer units
- Fills the `sensor_sample` structure

`include/app_types.h`

- Defines the `sensor_sample` data structure and status values

Current architecture:

```text
main()
  |
  +-- sensor acquisition thread
        |
        +-- sensor_service_read()
              |
              +-- Zephyr sensor driver
                    |
                    +-- I2C BMP280 hardware


---

## 4. Update `docs/learning_journal.md`

Run:

```powershell
notepad C:\dev\fieldsense-z\docs\learning_journal.md


## Entry — First Zephyr sensor acquisition thread

### What I was trying to achieve

I wanted to move from a simple main-loop sensor read to a dedicated RTOS thread that periodically acquires environmental data.

### What I changed

I added one Zephyr thread called the sensor acquisition thread.

The thread wakes every 2000 ms, calls `sensor_service_read()`, logs successful samples, records failures, and continues running after recoverable errors.

### What I learned

I learned that a thread is an independent execution path with its own stack and priority.

I learned that the scheduler chooses which ready thread runs, and that a sleeping or blocked thread does not need to occupy the CPU.

I also learned why I2C can block. A sensor read depends on bus activity, ACKs, timing, and driver completion. If the acquisition thread blocks during I2C, that does not mean the whole application must stop.

### Design choices

I chose priority `5` because the sensor acquisition task is periodic and not urgent.

I chose a stack size of `2048` bytes as an initial conservative value. This is not final. Later I should measure stack usage and tune it.

I chose a sample period of `2000` ms because it matches the previous working sensor application and makes serial-log verification easy.

### Result

The acquisition thread produced repeated sensor samples with increasing sequence numbers and timestamps.

### Evidence

Serial output was saved in:

`results/logs/sensor_acq_thread.txt`

### Blog seed

After refactoring the sensor access into a reusable service, I moved the sampling loop into a dedicated Zephyr thread. This is an important RTOS step because sensor acquisition is now an independent periodic task instead of being hard-coded inside `main()`. The thread wakes every two seconds, reads the BMP280 through the sensor service, timestamps the result, assigns a sequence number, and logs success or failure. If a read fails, the thread records the error and continues instead of crashing the application. This separation makes the system easier to extend later with message queues, statistics, health monitoring, and fault handling.

## RTOS queue architecture

The application now has a producer-consumer structure.

```text
main()
  |
  +-- sensor acquisition thread
  |     |
  |     +-- sensor_service_read()
  |     |
  |     +-- k_msgq_put(sensor_sample)
  |
  +-- temporary consumer thread
        |
        +-- k_msgq_get(sensor_sample)
        |
        +-- log complete sample


---

## 4. Update `docs/learning_journal.md`

Open:

```powershell
notepad C:\dev\fieldsense-z\docs\learning_journal.md


## Entry — RTOS sensor message queue

### What I was trying to achieve

I wanted to separate sensor acquisition from sample consumption using a Zephyr message queue.

### What I changed

I added a `k_msgq` between the acquisition thread and a temporary consumer thread.

The acquisition thread now produces complete `sensor_sample` structures and publishes them to the queue.

The temporary consumer blocks on the queue, receives complete samples, and logs them.

### What I learned

I learned that a message queue is useful because it avoids sharing one mutable global sample between threads.

The producer owns its local sample until it publishes it. The queue stores a copy. The consumer receives its own local copy.

I also learned that queue depth is a design decision. A deeper queue gives more buffering but uses more RAM and can hide slow consumers for longer.

### Queue-full policy

The acquisition thread uses non-blocking sends.

If the queue is full, the newest sample is not enqueued. The code increments `queue_full_count` and logs the event. Older queued samples are preserved.

This means data is not silently lost.

### Result

Under normal operation, produced and consumed sequence numbers matched, samples moved correctly through the queue, and queue-full count stayed zero.

### Evidence

Serial output was saved in:

`results/logs/sensor_msgq.txt`

### Blog seed

After moving sensor acquisition into a dedicated Zephyr thread, I added a message queue between acquisition and a temporary consumer. This changed the design from direct logging to a producer-consumer pipeline. The acquisition thread now creates a complete `sensor_sample` with timestamp, sequence number, measurements, and status, then publishes that structure to a fixed-depth queue. The consumer blocks until a sample is available and then logs its own copy. This avoids shared mutable state and makes the design easier to extend later with processing, statistics, fault detection, or logging threads. I also added an explicit queue-full policy so overload is counted and visible instead of silently losing data.


## Entry — Environmental processing thread

### What I was trying to achieve

I wanted to separate sensor acquisition from sensor processing using a producer-consumer RTOS architecture.

### What I changed

I replaced the temporary queue consumer with a dedicated environmental processing thread.

The acquisition thread still reads the sensor periodically and publishes complete `sensor_sample` structures to the message queue.

The processing thread now receives samples, validates them, counts valid and invalid samples, detects sequence gaps, and stores the latest valid sample.

### What I learned

I learned that acquisition and processing are different responsibilities.

Acquisition is timing-sensitive and hardware-facing. It should focus on waking periodically, reading the sensor, timestamping data, assigning sequence numbers, and publishing samples.

Processing should block on the message queue until a sample arrives. This is better than polling because the processing thread does not waste CPU when there is no work.

I also learned how data ownership works in the design. The acquisition thread owns the local sample before publishing, the queue owns the copied message while it waits, and the processing thread owns the received copy after `k_msgq_get()`.

### Interview explanation

I used a producer-consumer architecture. The acquisition thread is the producer because it periodically creates sensor samples. The processing thread is the consumer because it waits on the queue, receives complete samples, validates them, and updates processing state.

This avoids shared mutable state. Instead of two threads reading and writing the same global sample, the sample is copied through a Zephyr message queue. That makes the data flow easier to reason about and helps prevent race conditions.

I also chose acquisition priority higher than processing priority because acquisition owns periodic timing. The processing thread blocks on the queue and only runs when data is available.

### Result

The system was run for at least 50 samples under normal operation. Sequence numbers increased as expected, no unexpected sequence gaps were observed, queue-full count stayed zero, and acquisition continued independently of processing.

### Evidence

Serial output was saved in:

`results/logs/sensor_processing_thread.txt`

### Blog seed

After adding a message queue between acquisition and consumption, I replaced the temporary consumer with a dedicated environmental processing thread. This made the design closer to a real embedded RTOS system. The acquisition thread now focuses only on periodic sensor reads and publishing complete samples. The processing thread blocks on the queue, wakes only when data is available, validates each sample, checks sequence continuity, counts valid and invalid samples, and stores the latest valid reading. This producer-consumer design avoids shared mutable state and makes the project easier to extend later with statistics, health monitoring, and fault detection.


