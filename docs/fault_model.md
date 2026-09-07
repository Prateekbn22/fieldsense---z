# Fault Model

## Node health states

Node health describes the health of the embedded node itself.

Implemented states:

- INITIALIZING
- HEALTHY
- WARNING
- FAULT

## Environmental states

Environmental status describes the measured environment.

Implemented states:

- UNKNOWN
- NORMAL
- HIGH_TEMPERATURE
- PRESSURE_ALERT

## Fault categories

Implemented and validated fault categories:

| Fault category | Validation method |
|---|---|
| Sensor unavailable | Physical wiring disconnect |
| Sensor read failure | Software fault injection |
| Stale data | Software fault injection |
| Queue pressure | Software fault injection |
| Missed deadline | Processing delay and queue pressure |
| Invalid measurement | Software fault injection support |
| Fault recovery | Clearing injection and observing recovery |

## Recovery

The node does not recover from FAULT after a single good sample. It requires a sequence of valid samples.

Actual recovery evidence showed:

- qualified recovery complete
- required_valid_samples = 5
- FAULT -> HEALTHY transition after clearing the fault

## Environmental thresholds

| Threshold | Value |
|---|---:|
| High temperature enter | 30.000 C |
| High temperature clear | 28.000 C |
| Pressure low enter | 95.000 kPa |
| Pressure high enter | 105.000 kPa |
| Pressure low clear | 97.000 kPa |
| Pressure high clear | 103.000 kPa |

## Important distinction

A node can be HEALTHY while the environment is in an alert state. A sensor failure, stale data, or queue pressure affects node health. Temperature and pressure thresholds affect environmental status.
