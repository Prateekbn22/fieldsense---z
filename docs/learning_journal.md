## Entry 3 — Zephyr environment setup and verification

### 1. What I was trying to achieve

I was trying to install and verify the Zephyr development environment before writing FieldSense-Z application code.

### 2. What concept I learned

I learned that Zephyr development depends on the host environment. The `west` tool, Python virtual environment, Zephyr workspace, CMake, Ninja, Git, and Zephyr SDK must all be available before board bring-up can start.

### 3. What I changed

I installed the missing Zephyr setup pieces and moved the Zephyr workspace to `C:\zephyrproject` to avoid problems caused by spaces in my Windows user path.

### 4. How I tested it

I activated the Zephyr virtual environment and ran `west --version`, `west topdir`, `west list zephyr`, `west boards` filtered for ESP32, `cmake --version`, `ninja --version`, `git --version`, `py -3.12 --version`, and `where.exe 7z`.

### 5. What actually happened

TBD after reviewing `results/logs/zephyr_environment_check.txt`.

### 6. Any problem and its root cause

Earlier, PowerShell could not recognize `west`, and the first Zephyr workspace path caused dependency-install issues because my Windows user path contained spaces. I fixed this by creating a clean Zephyr workspace at `C:\zephyrproject`.

### 7. What I would explain in an interview

I would explain that I verified the Zephyr toolchain before writing firmware. When `west` was missing and the first setup path caused issues, I treated it as an environment problem, documented the evidence, and fixed the setup before moving to board bring-up.

### 8. Blog-style paragraph

Before writing sensor code, I set up and verified the Zephyr environment on Windows. I captured the tool versions and ESP32 board listing in a log file so future build or flash issues can be compared against a known setup state. This step helped me separate toolchain problems from firmware or hardware problems.

## Entry 4 — First ESP32 board bring-up

### What I was trying to achieve

I wanted to build, flash, and verify a minimal Zephyr application on my ESP32 before connecting the BME280 sensor.

### What I learned

I learned that hardware bring-up should be done in small steps. First I verified the board target, SDK toolchain, flashing path, and serial console before adding sensor code.

### What I changed

I added a minimal `src/main.c`, updated `CMakeLists.txt`, and kept `prj.conf` limited to serial console and `printk`.

### How I tested it

I built the application using Zephyr west, flashed it to the ESP32, and opened a serial monitor on COM9 at 115200 baud.

### Result

The ESP32 successfully booted Zephyr and printed periodic uptime messages every 5 seconds.

### Evidence

Logs saved:

- `results/logs/first_board_build.txt`
- `results/logs/first_board_flash.txt`
- `results/logs/first_board_boot.txt`

### Interview explanation

I would explain that I started with a minimal board bring-up test instead of jumping directly to the sensor. This helped me isolate the build system, board target, SDK, flashing, and serial-console path first.

### Blog-style paragraph

For this step, I kept the firmware intentionally small. The application only prints a startup message and a periodic uptime message. This proved that the ESP32 could build, flash, boot Zephyr, and communicate over the serial console before I connected the BME280 sensor.

## Entry — Bosch sensor identity verification

### What I was trying to achieve

I wanted to verify whether my HW-611 module actually contained a BME280 or BMP280 before writing sensor-driver measurement code.

### What I learned

I learned that the I2C address and chip ID are different. The address tells me where a device responds on the bus. The chip ID tells me what silicon is inside the package.

### What I tested

I read Bosch register `0xD0`, which is the identification register.

### Result

The sensor responded at address `0x76`, and register `0xD0` returned `0x58`.

This identifies the module as BMP280.

### Project impact

I can continue with temperature and pressure measurements, but humidity cannot be implemented with this hardware. If humidity becomes required for the final FieldSense-Z demo, I need to purchase a verified BME280.

### Blog seed

Instead of trusting the breakout-board name or seller listing, I verified the actual silicon by reading the Bosch chip identification register. The module responded on the I2C bus at `0x76`, but that only proved communication. The stronger identity check was register `0xD0`, which returned `0x58`. That value identifies the device as a BMP280, not a BME280. This changed the project scope honestly: temperature and pressure remain available, but humidity is not possible with the current hardware.