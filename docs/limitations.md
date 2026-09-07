# Limitations

## Sensor limitations

The verified HW-611 module behaves as a BMP280 sensor.

Supported:

- temperature
- pressure

Not supported:

- humidity

Humidity is intentionally reported as unsupported.

## Connectivity limitations

This version does not implement:

- Wi-Fi
- Bluetooth
- MQTT
- cloud upload
- web dashboard
- mobile app

## Hardware output limitations

This version does not implement or validate:

- relay switching
- buzzer output
- LED alert output
- actuator control

## Measurement limitations

The temperature and pressure readings were not calibrated against an external lab-grade reference.

The stability run lasted about 40 minutes. It is useful evidence, but it is not the same as multi-day or field deployment testing.

## Resource measurement limitations

Thread analyzer output captured:

- fieldsense_proc
- fieldsense_acq
- shell_uart
- logging
- idle
- ISR0

The captured output did not list a system workqueue stack entry.

Boot memory section lines were captured, but a full rom_report and ram_report should be used for deeper flash and RAM analysis.

## Evidence limitations

Serial monitor screenshots were not captured. Saved serial logs were used as the primary evidence.

## Fault injection limitations

Fault injection is deterministic and useful for validation, but it is not the same as every possible real hardware failure. The project includes both physical sensor unavailable testing and software fault injection to cover both cases.
