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



