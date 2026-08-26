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

## Entry — Sensor service refactor

### What I was trying to achieve

I wanted to keep `main.c` simple by moving environmental sensor access into a reusable sensor service module.

### What I changed

I created:

- `include/app_types.h`
- `include/sensor_service.h`
- `src/sensor_service.c`

The sensor service now owns the Zephyr sensor API calls and returns a clean `sensor_sample` structure to the application.

### What I learned

I learned that a good module boundary keeps hardware access separate from application behavior.

`main.c` should not need to know every Zephyr sensor channel or driver detail. It should ask for a sample and decide what to do with it.

I also learned why explicit units matter. Instead of passing around floating-point values or raw driver structures, I store temperature in milli-degrees Celsius and pressure in pascals. This makes logs, comparisons, thresholds, and tests clearer.

### Result

The refactored application produced the same physical measurements as the previous sensor-driver version, but the code is cleaner and easier to extend.

### Evidence

Serial output from the refactored application was saved in:

`results/logs/sensor_service_refactor.txt`

### Blog seed

After proving that the BMP280 worked through Zephyr’s sensor API, I refactored the sensor logic into a small service module. This moved hardware access out of `main.c` and created a cleaner boundary between driver-level operations and application behavior. The service fetches samples, reads supported channels, converts values into explicit integer units, and reports errors through a structured status field. This makes the next stages easier to build because future RTOS threads, queues, statistics, and fault logic can work with a simple `sensor_sample` structure instead of directly depending on sensor-driver calls.

## Entry — Environmental measurement statistics

### What I was trying to achieve

I wanted to add useful statistics to the environmental processing thread without mixing calculation logic into the hardware layer.

### What I changed

I added a separate statistics module:

- `include/env_stats.h`
- `src/env_stats.c`

The processing thread now updates statistics only after receiving and validating a sample.

### What I learned

I learned the difference between latest value, minimum, maximum, arithmetic mean, and moving average.

The latest value is the newest valid reading. The minimum and maximum track the range of valid readings. A moving average smooths short-term variation by averaging only the most recent window of samples.

I also learned why integer scaling matters in embedded systems. Temperature is stored in milli-degrees Celsius and pressure is stored in pascals, so statistics can be calculated without floating point.

I used an `int64_t` moving-window sum to reduce overflow risk when adding multiple `int32_t` values.

### Interview explanation

I kept statistics separate from the hardware layer. The sensor service talks to the Zephyr sensor driver, the acquisition thread publishes samples, and the processing thread validates samples before passing values into the stats module.

This makes the calculation code easier to test. I verified the module first with controlled values, then with real BMP280 measurements.

Since my verified sensor is BMP280, I only calculate statistics for temperature and pressure. Humidity statistics are intentionally skipped because this hardware does not support humidity.

### Evidence

Serial output was saved in:

`results/logs/env_stats.txt`

### Blog seed

After building the producer-consumer pipeline, I added environmental measurement statistics as a separate module. The goal was to keep hardware access, RTOS communication, processing, and calculations separated. The stats module tracks the latest value, minimum, maximum, valid sample count, and a moving average window for temperature and pressure. I verified the math first using controlled values, then ran it on real BMP280 readings. This made the feature easier to test and also kept the design honest because humidity statistics are not calculated on BMP280 hardware.

