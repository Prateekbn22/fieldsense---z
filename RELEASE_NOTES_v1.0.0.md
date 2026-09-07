# FieldSense-Z v1.0.0

FieldSense-Z v1.0.0 is the first validated release of the ESP32 + BMP280 Zephyr RTOS environmental monitoring node.

## Highlights

- ESP32 DEVKIT V1 / ESP-WROOM-32 support
- Zephyr board target: doit_esp32_devkit_v1/esp32/procpu
- Verified BMP280-compatible HW-611 sensor
- I2C address 0x76
- Temperature and pressure measurement
- Dedicated acquisition and processing threads
- Finite message queue with overflow policy
- Node health state model
- Environmental status model
- Diagnostic serial shell
- Deterministic fault injection
- Hardware validation with serial logs and photos
- 40-minute stability run
- Resource and stack usage measurement

## Validation summary

All validation tests passed:

- Cold boot
- Normal measurements
- Environmental threshold
- Sensor unavailable
- Sensor read failure
- Stale data
- Queue pressure
- Fault recovery
- Reset-stats
- Power cycle
- 30-60 minute stability run

## Stability result

The stability run completed for approximately 40 minutes with:

- 1176 valid samples in final stats
- 0 invalid samples
- 0 queue overflows
- 0 missed deadlines
- stale_data: no
- final node health: HEALTHY
- final environment status: NORMAL

## Known limitations

- BMP280 supports temperature and pressure only.
- Humidity is not supported.
- No Wi-Fi, Bluetooth, MQTT, cloud dashboard, or mobile app is implemented.
- No relay or actuator behavior is implemented.
- Serial logs are the primary evidence; serial screenshots were not captured.
- Stability run was 40 minutes, not long-term field deployment.
- Measurements were not calibrated against a lab-grade instrument.

## Reproduction

Build and flash instructions are in README.md.

Release metadata is in:

docs/release_metadata_v1.0.0.md
