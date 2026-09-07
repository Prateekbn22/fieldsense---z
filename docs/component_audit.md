# Component Audit

## Validated components

| Component | Actual result |
|---|---|
| ESP32 DEVKIT V1 / ESP-WROOM-32 | Used as the main controller |
| HW-611 sensor module | Electrically identified as BMP280-compatible hardware |
| BMP280 chip ID | 0x58 |
| I2C address | 0x76 |
| Supply voltage | 3.3 V |
| SDA | ESP32 GPIO21 |
| SCL | ESP32 GPIO22 |
| GND | Common ground |

## Sensor capability

The module was treated carefully because HW-611-style boards can be mislabeled or confused with BME280 modules. The chip ID read returned 0x58, which identifies the hardware as BMP280. Therefore this project supports:

- temperature
- pressure

This project does not support:

- humidity

The firmware and documentation describe humidity as unsupported by verified BMP280 hardware.

## Parts intentionally not used

No relay was used.

No relay design is included:

- no relay coil current calculation
- no relay contacts
- no relay driver transistor
- no flyback diode
- no relay supply design

No external actuator output was validated in this version.

## Hardware validation photos

Hardware photos are stored under:

- results/photos/baseline_wiring_before_validation.jpg
- results/photos/baseline_wiring_closeup.jpg
- results/photos/sensor_unavailable_wiring_change.jpg
- results/photos/restored_wiring_after_fault_test.jpg
- results/photos/final_restored_wiring.jpg

The exact available photos depend on the files saved during validation.
