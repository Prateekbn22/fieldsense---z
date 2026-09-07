# Project Overview

FieldSense-Z is a Zephyr RTOS environmental monitoring node built on an ESP32 DEVKIT V1 and a verified BMP280 sensor module.

The project demonstrates practical embedded engineering work:

- hardware bring-up
- I2C first-principles validation
- Zephyr devicetree configuration
- sensor driver integration
- RTOS thread separation
- message queue based sample transfer
- diagnostic shell commands
- health and fault state modeling
- deterministic fault injection
- timing and resource measurement
- hardware validation with evidence

The validated sensor hardware supports temperature and pressure only. Humidity is intentionally documented as unsupported.

## Actual validated behavior

The completed project can:

- boot on ESP32
- read BMP280 temperature and pressure over I2C address 0x76
- publish samples from an acquisition thread to a processing thread
- compute latest, minimum, maximum, and moving-average statistics
- track sampling intervals, missed deadlines, stale data, and last valid sample age
- classify node health separately from environmental status
- expose a diagnostic shell
- inject controlled software faults
- recover from sensor, stale-data, and queue-pressure faults
- complete a 40-minute stability run without invalid samples, missed deadlines, stale data, or queue overflows

## Out of scope

This project does not include:

- humidity measurement
- relay switching
- Wi-Fi
- Bluetooth
- MQTT
- cloud storage
- dashboard UI
- machine learning
- battery-power characterization
- external calibration
