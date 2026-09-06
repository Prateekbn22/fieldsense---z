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

## Deterministic software fault injection

FieldSense-Z now supports controlled software fault injection for validation.

The goal is to verify the fault model without depending only on random physical faults.

Physical tests are still useful, but they are harder to repeat exactly. Software injection allows the same fault to be triggered repeatedly with known expected behavior.

### Supported injected faults

```text
node inject sensor-failure
node inject stale-publication
node inject processing-delay
node inject queue-pressure
node inject invalid-measurement
node inject clear
## Queue backpressure fault behavior

Queue backpressure is treated as a recoverable fault condition.

When the processing thread is slowed down, the acquisition thread can continue publishing samples faster than the consumer can process them.

As queue occupancy rises, the finite queue can become full.

When the queue is full, FieldSense-Z uses a nonblocking drop-newest policy:

```text
preserve oldest queued samples
drop newest failed publication
increment queue_full_count
log queue overflow
```

Repeated queue overflow events can move the node health state toward `FAULT`.

### Recovery hysteresis

Recovery is hysteretic.

The node does not immediately return to `HEALTHY` after one good sample.

After a fault is cleared, the node must receive the configured number of consecutive recovery-valid samples before returning to `HEALTHY`.

This prevents unstable behavior where the node rapidly switches between `FAULT` and `HEALTHY`.

### Repeated sensor error

Repeated sensor read failures are treated as a health fault.

Expected behavior:

```text
HEALTHY
→ WARNING
→ FAULT
```

The fault reason becomes:

```text
SENSOR_FAILURES
```

After clearing the injected sensor failure, recovery requires consecutive valid samples.

### Stale data

Stale data is detected when the latest valid sample age exceeds the stale threshold.

Expected behavior during stale-publication injection:

```text
stale_data: yes
last_fault_reason: STALE_DATA
```

After clearing the injection, stale data must return to:

```text
stale_data: no
```

### Environmental alert clearing

The environmental state uses hysteresis.

For high temperature:

```text
enter HIGH_TEMPERATURE at or above 30.000 C
clear HIGH_TEMPERATURE at or below 28.000 C
```

Because the real BMP280 temperature may stay above the clear threshold during testing, a software-only `normal-environment` validation stimulus is used.

The `normal-environment` stimulus injects a safe, valid environmental sample:

```text
temperature: 26.000 C
pressure: 100.000 kPa
```

This verifies environmental alert clearing without changing hardware wiring or physically cooling the sensor.

### Final recovery result

After clearing injected faults, the node returned to:

```text
health: HEALTHY
last_fault_reason: NONE
fault_injection_mask: 0x00000000
active_injections: none
```

