## Debug entry — Zephyr setup path and west availability

### Date

July 28, 2026

### Symptom

PowerShell initially did not recognize `west`, and the Zephyr dependency installation failed when the workspace was under a Windows user path containing spaces.

### What I expected

I expected `west --version` to work and the Zephyr Python dependencies to install cleanly.

### What actually happened

`west` was not initially available. After installing it, the dependency installation failed because the path was split incorrectly around spaces in the Windows user folder.

### Evidence collected

- `results/logs/zephyr_environment_check.txt`

### Root cause

The Zephyr environment was not available at first, and the first workspace location used a path with spaces. This caused Windows command parsing problems during dependency installation.

### Fix

I created a clean Zephyr workspace at `C:\zephyrproject`, created a new Python virtual environment there, installed `west`, downloaded Zephyr modules, installed dependencies, and completed SDK setup.

### Verification

Pending from the final `zephyr_environment_check.txt` log.

### What I learned

I learned that embedded toolchains can fail before any firmware is written. A clean installation path and an activated virtual environment are important parts of reliable board bring-up.

## I2C Bring-up Debug Checklist

### Scope

This checklist is for the first ESP32 to BME280-style sensor I2C bring-up.

No sensor application code has been added yet.

### Hardware identity

- ESP32 board marking: ESP32 DEVKIT V1
- ESP32 module marking: ESP-WROOM-32
- Sensor marking: GY-BME280 or unknown
- Sensor pin labels: VCC, GND, SCL, SDA, CSB, SDO
- Verified Zephyr board target: `doit_esp32_devkit_v1/esp32/procpu`

### Before powering

- [ ] ESP32 powered from Micro-USB only
- [ ] Sensor VCC connected to verified 3.3 V source
- [ ] ESP32 GND connected to sensor GND
- [ ] SDA connected to chosen SDA GPIO
- [ ] SCL connected to chosen SCL GPIO
- [ ] SDA and SCL are not swapped
- [ ] No connection from ESP32 GPIO to 5 V
- [ ] CSB wiring requirement checked
- [ ] SDO wiring/address behavior checked
- [ ] Wiring photo saved to `results/photos/first_i2c_wiring.jpg`

### If sensor is not detected later

Check in this order:

1. Confirm ESP32 and sensor share common GND.
2. Confirm sensor is powered from 3.3 V.
3. Confirm SDA and SCL are not swapped.
4. Confirm the selected ESP32 GPIO pins match the Zephyr I2C/devicetree configuration.
5. Confirm whether the breakout is BME280 or BMP280.
6. Confirm expected I2C address, usually `0x76` or `0x77` depending on SDO wiring.
7. Confirm CSB is in the correct state for I2C mode if required.
8. Check whether SDA and SCL have pullups.
9. Check whether pullups go to 3.3 V, not 5 V.
10. Use the wiring photo to compare actual wiring against the checklist.

### Likely failure causes

| Symptom | Possible cause |
|---|---|
| No I2C device detected | No common GND, wrong SDA/SCL pins, no sensor power, wrong bus, missing pullups |
| Device detected at unexpected address | SDO wiring changed address, breakout default differs from expectation |
| Temperature/pressure works but humidity missing | Sensor may be BMP280 instead of BME280 |
| ESP32 resets or behaves strangely | Power wiring issue, short, unstable USB cable, accidental wrong voltage |
| Build works but sensor fails | Hardware wiring or devicetree mismatch, not a compiler problem |

### Debug rule

I will not guess the fix from memory. I will record the actual symptom, wiring photo, expected address, chosen pins, and test output before changing hardware or code.

## I2C Scan Bring-up Debug Notes

### Goal

Validate that the ESP32 can communicate with the HW-611 sensor over I2C before using the BME280/BMP280 driver.

### Hardware and configuration

- Board: ESP32 DEVKIT V1 / ESP-WROOM-32
- Zephyr board target: `doit_esp32_devkit_v1/esp32/procpu`
- SDA: GPIO21
- SCL: GPIO22
- Expected addresses checked: `0x76` and `0x77`

### Issues encountered

1. Devicetree alias used an underscore

   The first overlay used `fieldsense_i2c`, but Zephyr devicetree alias names allow lowercase letters, digits, and hyphens. I changed the alias to `fieldsense-i2c` in `app.overlay` and kept `DT_ALIAS(fieldsense_i2c)` in C.

2. Duplicate `main()` function

   The I2C scan code was pasted below the old board bring-up code, causing two `main()` functions. I replaced the entire `src/main.c` file with only the I2C scan program.

3. I2C driver was not linked

   The build failed with an undefined device reference because the I2C controller node existed in devicetree, but the ESP32 I2C driver was not being built. I added `CONFIG_I2C_ESP32=y` to `prj.conf`.

### Final result

The ESP32 booted, initialized the I2C device, and scanned the two expected addresses.

Actual result:

- `0x76`: ACK received
- `0x77`: no ACK, `ret=-5`

Final serial output:

```text
I2C device is ready
ACK received at address 0x76
No ACK at address 0x77, ret=-5
I2C scan result: PASS, one expected address responded
I2C bus validation checkpoint complete

## Entry — I2C bus validation before sensor driver

### What I was trying to achieve

I wanted to prove that the ESP32 could communicate with the HW-611 sensor at the I2C bus level before using a BME280 or BMP280 driver.

### What I changed

I configured I2C on the ESP32 using GPIO21 for SDA and GPIO22 for SCL. I added a devicetree overlay, enabled I2C support in Kconfig, and wrote a small scan program that checked only the expected addresses, `0x76` and `0x77`.

### What I learned

I learned that an I2C ACK means a target responded at that address, but it does not prove the exact sensor model. The bus scan validates the electrical and protocol layer, while the sensor driver validates the device identity and measurement behavior.

### Result

The ESP32 initialized the I2C bus and received an ACK at address `0x76`. Address `0x77` did not respond.

### Evidence

The actual serial output was saved to:

`results/logs/i2c_scan.txt`

### Blog seed

Before using the Zephyr sensor driver, I validated the lower electrical and protocol layer first. I configured the ESP32 I2C controller on GPIO21 and GPIO22, then scanned only the expected HW-611 sensor addresses, `0x76` and `0x77`. This separated bus bring-up from sensor-driver bring-up. An ACK at one address proves that the ESP32 can reach a target on the I2C bus, but it does not yet prove the exact sensor model or measurement correctness. That separation made the debug path cleaner: first prove power, ground, pins, pullups, and address response, then move on to driver-level identification and measurements.

## Bosch Sensor Identification Debug Note

### Goal

Determine whether the HW-611 module contains a BME280 or BMP280 before writing measurement code.

### Method

I read Bosch identification register `0xD0` over I2C.

### Result

- Address `0x76`: register `0xD0` returned `0x58`
- Address `0x77`: chip ID read failed with `ret=-5`

### Interpretation

The sensor is BMP280.

The board can provide temperature and pressure measurements, but humidity is not available with this hardware.

### Scope impact

FieldSense-Z will continue with BMP280-compatible scope unless a verified BME280 is purchased later.