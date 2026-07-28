# FieldSense-Z

FieldSense-Z is a Zephyr RTOS portfolio project using an ESP32 and a BME280-style environmental sensor breakout.

The goal is to build a small environmental sensing node that does more than print sensor values. The project will acquire timestamped environmental samples, move them through an RTOS-safe data path, detect stale data and node faults, separate node health from environmental alerts, and document evidence from physical hardware testing.

## Current status

Repository initialized.

No sensor application code has been added yet.

## Planned capabilities

- Periodic environmental sampling
- Timestamped sample records
- Producer-consumer data flow
- RTOS-safe message queue
- Sample freshness checks
- Node-health tracking
- Environmental-alert classification
- Controlled recovery experiments
- Hardware photos, logs, and debug notes

## Hardware status

Exact hardware identification is pending.

The Zephyr board target, I2C pins, and sensor address will not be selected until the ESP32 board and sensor breakout markings are verified.

## Non-goals for version 1

- Wi-Fi
- Cloud services
- Dashboards
- MQTT
- Bluetooth
- Machine learning
- Extra sensors
- Production calibration
- Safety certification
