## Entry 2 — Hardware component audit

### 1. What I was trying to achieve

I was trying to identify the exact hardware I have before choosing a Zephyr board target or wiring the sensor.

### 2. What concept I learned

I learned that board bring-up starts with physical evidence. The PCB text, module marking, USB connector, sensor markings, and pin labels all affect how the system should be configured and tested.

### 3. What I changed

I updated the component audit with the ESP32 PCB text, ESP32 module text, Micro-USB connector type, sensor marking, sensor pin labels, operating system, and Git workflow.

### 4. How I tested it

I verified the documentation file using PowerShell and checked Git status before committing the documentation update.

### 5. What actually happened

I identified the board as ESP32 DEVKIT V1 with an ESP-WROOM-32 module. The sensor breakout is marked or described as GY-BME280 or unknown, with pins VCC, GND, SCL, SDA, CSB, and SDO.

### 6. Any problem and its root cause

The sensor is not fully verified as BME280 yet. The root cause is that a breakout label or seller name alone is not enough evidence to confirm humidity support or the exact chip.

### 7. What I would explain in an interview

I would explain that I documented the hardware before wiring because I did not want to assume the board target, I2C pins, voltage behavior, or sensor address.

### 8. Blog-style paragraph

For this step, I treated the hardware audit as part of the bring-up process. I recorded the ESP32 board text, module marking, USB connector, and sensor pin labels before writing code. This helped me separate what I know from what still needs to be verified, which is important when working with real hardware instead of only following a tutorial.