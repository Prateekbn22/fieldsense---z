\# Diagnostic Interface



\## Goal



FieldSense-Z now includes a runtime diagnostic shell for embedded validation.



The shell allows runtime inspection without rebuilding or reflashing firmware.



\## Why a runtime shell is useful



A runtime shell improves observability.



It allows the developer to inspect the node while it is running, including health state, environmental state, latest sample, statistics, timing metrics, fault counters, and configured thresholds.



This is useful during embedded validation because many problems only appear while the system is running on real hardware.



\## Runtime introspection



The shell supports these commands:



```text

node status

node latest

node stats

node timing

node faults

node reset-stats

node thresholds

