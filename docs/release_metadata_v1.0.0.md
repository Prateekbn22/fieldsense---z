# FieldSense-Z v1.0.0 Release Metadata

## Git commit

Full commit:

db109e6d74c7f7d8e4981e1b04a551499a727ed5

Short commit:

db109e6d74c7

## Zephyr version

v4.4.0-9769-gd211a737740

## SDK version

zephyr-sdk-1.0.1

SDK path used during validation:

C:\zephyrproject\zephyr-sdk-1.0.1

## Board target

doit_esp32_devkit_v1/esp32/procpu

## Sensor identity

| Item | Value |
|---|---|
| Sensor module | HW-611 BMP280-compatible module |
| Chip ID | 0x58 |
| Measurement support | Temperature and pressure |
| Humidity | Not supported |

## Sensor address

0x76

## Test summary

| Area | Result |
|---|---|
| Clean Git status | PASS |
| Generated-file review | PASS |
| Fresh clone | PASS |
| README-only setup review | PASS |
| Clean-clone build | PASS |
| Clean-clone flash | PASS |
| Sensor verification | PASS |
| Automated tests | PASS |
| Fault-recovery demonstration | PASS |
| Documentation-link check | PASS |
| Hardware validation | PASS |

## Hardware validation summary

All hardware validation tests passed:

| Test | Result |
|---|---|
| Cold boot | PASS |
| Normal measurements | PASS |
| Environmental threshold | PASS |
| Sensor unavailable | PASS |
| Sensor read failure | PASS |
| Stale data | PASS |
| Queue pressure | PASS |
| Fault recovery | PASS |
| Reset-stats | PASS |
| Power cycle | PASS |
| 30-60 minute stability run | PASS |

## Stability result

The stability run lasted approximately 40 minutes.

Final stability evidence showed:

| Metric | Result |
|---|---|
| Valid samples | 1176 in final stats, 1180 in final summary |
| Invalid samples | 0 |
| Queue overflows | 0 |
| Missed deadlines | 0 |
| Stale data | no |
| Final node health | HEALTHY |
| Final environment status | NORMAL |

## Known limitations

- BMP280 hardware supports temperature and pressure only.
- Humidity is not supported.
- No Wi-Fi, Bluetooth, MQTT, cloud dashboard, or mobile app is implemented.
- No relay or actuator behavior is implemented.
- Serial screenshots were not captured; serial logs are the primary evidence.
- Stability run was approximately 40 minutes, not a long-term deployment test.
- Measurements were not calibrated against a lab-grade reference instrument.
- Some fault behavior is validated using deterministic software injection.
- Captured thread analyzer output did not list a system workqueue stack entry.

## Release decision

v1.0.0 can be tagged only after clean-clone reproduction succeeds.

