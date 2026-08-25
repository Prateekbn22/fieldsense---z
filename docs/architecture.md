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



