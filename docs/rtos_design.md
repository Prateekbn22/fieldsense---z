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

