# Wiring

## Baseline wiring

| BMP280 / HW-611 pin | ESP32 pin |
|---|---|
| VCC | 3V3 |
| GND | GND |
| SDA | GPIO21 |
| SCL | GPIO22 |
| CSB / CS | Not connected |
| SDO | Not connected |

Use 3.3 V only.

## I2C behavior

The validated I2C address is 0x76.

The earlier I2C validation showed:

- address 0x76 acknowledged
- address 0x77 did not acknowledge
- chip ID register 0xD0 returned 0x58

## Physical fault test rule

For physical wiring changes:

1. Power the ESP32 off first.
2. Disconnect only the intended wire.
3. Record what was disconnected.
4. Take a photo.
5. Restore wiring safely.
6. Re-check 3.3 V, GND, SDA, and SCL.
7. Power the ESP32 again.
8. Confirm readings return.

## Sensor unavailable test

The validation procedure used a physical sensor unavailable test. The validation results document records the disconnected wire as BMP280 SDA from ESP32 GPIO21. If a different wire was disconnected in the actual photo, update that line before final publication.

## Final restored wiring

The expected final wiring is the same as the baseline wiring:

- VCC to 3V3
- GND to GND
- SDA to GPIO21
- SCL to GPIO22
