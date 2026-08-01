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