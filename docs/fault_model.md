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

