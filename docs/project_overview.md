# FieldSense-Z Project Overview

## Project objective

FieldSense-Z is a Zephyr RTOS environmental sensing and fault-monitoring node using an ESP32 and a BME280-style sensor breakout.

The project will periodically acquire temperature, humidity, and pressure samples, attach timing and validity information, pass samples through an RTOS-safe data path, detect stale data and node faults, and expose diagnostic evidence from physical hardware testing.

## Problem statement

A simple program that reads a sensor and prints a value does not prove that the embedded node is trustworthy over time.

A printed value may be old, repeated, delayed, or produced after an ignored error. FieldSense-Z is intended to show how an embedded system can track not only the environmental measurement, but also the health of the measurement process.

## Scope

Version 1 will focus on:

- ESP32 running Zephyr RTOS
- BME280-style environmental sensor over I2C, if verified
- Periodic acquisition
- Timestamped samples
- RTOS-safe message queue data transfer
- Sample freshness checking
- Node-health classification
- Environmental-alert classification
- Diagnostic logs and documentation
- Physical hardware validation

## Non-goals

Version 1 will not include:

- Wi-Fi
- Cloud services
- Dashboards
- MQTT
- Bluetooth
- Machine learning
- Extra sensors
- Production calibration
- Safety certification

## Expected final demonstration

The final demonstration should show the node acquiring environmental samples on physical hardware, reporting current measurements with timing context, detecting stale or failed acquisition states, separating node-health problems from environmental alerts, and recording test evidence through logs, photos, and notes.

The project will make bounded claims based on measured results from the tested hardware only.
