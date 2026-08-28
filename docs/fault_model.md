\# FieldSense-Z Fault and Alert Model



\## Purpose



This document defines the difference between node health and environmental status.



Node health describes whether the embedded node itself is working correctly.



Environmental status describes the condition being measured by the sensor.



These are intentionally separate systems.



\## Key concepts



\### State



A state describes the current condition of a system.



Example node health states:



\- `INITIALIZING`

\- `HEALTHY`

\- `WARNING`

\- `FAULT`



Example environmental status states:



\- `NORMAL`

\- `HIGH\_TEMPERATURE`

\- `PRESSURE\_ALERT`

\- `UNKNOWN`



\### Event



An event is something that happens and may cause a state transition.



Examples:



\- valid sample received

\- sensor read failed

\- latest valid sample became stale

\- missed deadline detected

\- temperature crossed threshold

\- pressure crossed threshold



\### Transition



A transition is movement from one state to another.



Example:



```text

HEALTHY -> WARNING

## Implementation checkpoint — State machines

The documented health and environmental alert model has now been implemented in firmware.

The implementation keeps two separate state systems:

- node health,
- environmental status.

### Implemented node health states

- `INITIALIZING`
- `HEALTHY`
- `WARNING`
- `FAULT`

### Implemented environmental states

The verified sensor is BMP280-compatible, so the implemented environmental states are:

- `UNKNOWN`
- `NORMAL`
- `HIGH_TEMPERATURE`
- `PRESSURE_ALERT`

Humidity states are still intentionally excluded because the current hardware does not support humidity.

### Implemented health behavior

The state model supports:

- normal startup from `INITIALIZING`,
- transient sensor error handling,
- repeated sensor-error transition to `FAULT`,
- stale-data detection,
- missed-deadline awareness,
- queue-overflow awareness,
- qualified recovery using multiple valid samples,
- transition counters,
- last fault reason tracking.

### Recovery rule

A node does not recover immediately after one good sample.

Recovery requires:

```text
5 consecutive valid samples