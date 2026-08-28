\## Health and environmental alert requirements



\### Sensor capability requirement



FieldSense-Z shall base environmental status only on channels supported by the verified sensor hardware.



The current verified sensor is BMP280-compatible hardware.



Supported channels:



\- temperature

\- pressure



Unsupported channels:



\- humidity



Humidity-based states such as `HIGH\_HUMIDITY` and `LOW\_HUMIDITY` shall not be used unless the hardware is replaced with a verified BME280 or another humidity-capable sensor.



\### Node health states



FieldSense-Z shall define the following node health states:



\- `INITIALIZING`

\- `HEALTHY`

\- `WARNING`

\- `FAULT`



Node health describes whether the embedded node itself is operating correctly.



\### Environmental status states



FieldSense-Z shall define the following environmental status states:



\- `NORMAL`

\- `HIGH\_TEMPERATURE`

\- `PRESSURE\_ALERT`

\- `UNKNOWN`



Environmental status describes the measured environment, not whether the node itself is broken.



\### Health requirements



The node shall start in `INITIALIZING`.



The node shall enter `HEALTHY` after initialization succeeds and valid samples are received.



The node shall enter `WARNING` if recoverable problems are detected, such as a single sensor read failure, stale data warning, or missed-deadline warning.



The node shall enter `FAULT` if repeated failures occur.



The node shall enter `FAULT` after `3` consecutive sensor read failures.



The node shall treat data as stale if the latest valid sample is older than `6000 ms`.



The node shall count a missed deadline when the measured sample interval is greater than `2250 ms`.



The node shall require `5` consecutive valid samples before recovering from `FAULT`.



\### Demonstration environmental thresholds



The following thresholds are for demonstration and interview validation only.



High-temperature enter threshold:



\- enter `HIGH\_TEMPERATURE` when temperature is greater than or equal to `30.000 C`



High-temperature clear threshold:



\- return from `HIGH\_TEMPERATURE` when temperature is less than or equal to `28.000 C`



Pressure-alert enter threshold:



\- enter `PRESSURE\_ALERT` when pressure is less than `95000 Pa`

\- enter `PRESSURE\_ALERT` when pressure is greater than `105000 Pa`



Pressure-alert clear threshold:



\- return from `PRESSURE\_ALERT` when pressure is between `97000 Pa` and `103000 Pa`



\### Separation requirement



FieldSense-Z shall keep node health separate from environmental status.



A high-temperature environmental condition shall not automatically mean the node is faulty.



Example:



If the sensor is working, timing is normal, and the queue is healthy, but the measured temperature is high, the system can report:



```text

Node health: HEALTHY

Environmental status: HIGH\_TEMPERATURE


## Health and environmental alert model

FieldSense-Z now defines two separate decision systems.

```text
Node health system
  |
  +-- INITIALIZING
  +-- HEALTHY
  +-- WARNING
  +-- FAULT

Environmental status system
  |
  +-- UNKNOWN
  +-- NORMAL
  +-- HIGH_TEMPERATURE
  +-- PRESSURE_ALERT