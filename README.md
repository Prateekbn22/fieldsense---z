# FieldSense-Z

FieldSense-Z is an ESP32-based embedded monitoring project built with Zephyr RTOS. It reads a verified BMP280 environmental sensor over I2C, processes temperature and pressure samples in a dedicated RTOS pipeline, tracks timing and health, exposes a diagnostic shell, and validates fault behavior using both physical hardware tests and deterministic software fault injection.

This version documents only implemented and measured behavior. It does not claim humidity support, cloud connectivity, Wi-Fi dashboards, Bluetooth, machine learning, relay control, or untested actuator behavior.

## 1. Problem

Embedded sensor nodes often fail in ways that are hard to understand after deployment. A sensor can disappear from the bus, reads can fail, data can become stale, a queue can fill, or timing can drift under load. A simple sensor demo may still print values, but it usually does not prove how the node behaves when the system is stressed or when the hardware is disconnected.

FieldSense-Z addresses that problem by treating the node as a small embedded system instead of only a sensor-reading sketch. It measures samples, tracks timing, records faults, separates node health from environmental status, and validates behavior with logs.

## 2. Objective

The objective was to build and validate a small Zephyr-based environmental monitoring node that demonstrates:

- I2C bring-up on ESP32
- BMP280 sensor identification and measurement
- Temperature and pressure processing
- RTOS thread separation
- Message queue based data transfer
- Node health state tracking
- Environmental status tracking
- Diagnostic shell commands
- Deterministic fault injection
- Timing, resource, and stability measurement
- Evidence-backed hardware validation

## 3. Hardware

Actual validated hardware:

| Item | Actual implementation |
|---|---|
| MCU board | ESP32 DEVKIT V1 / ESP-WROOM-32 |
| Zephyr board target | doit_esp32_devkit_v1/esp32/procpu |
| Sensor module | HW-611 module identified as BMP280 |
| Sensor address | 0x76 |
| Sensor chip ID | 0x58 |
| Supply voltage | 3.3 V |
| I2C SDA | GPIO21 |
| I2C SCL | GPIO22 |
| GND | Common ground |
| Humidity | Not supported by this verified hardware |

The module was originally treated as a possible BME280-style breakout, but chip ID testing identified it as BMP280. This means the implemented system supports temperature and pressure only.

No relay was used. No relay coil, relay contacts, flyback diode, relay supply, or relay switching behavior is part of this version.

## 4. Architecture

FieldSense-Z is split into small modules:

| Area | Implementation |
|---|---|
| Sensor access | sensor_service |
| Data model | app_types |
| Environmental statistics | env_stats |
| Timing metrics | timing_metrics |
| Health and environmental state machine | state_model |
| Fault injection | fault_injection |
| Diagnostic shell | diagnostics |
| Main RTOS pipeline | main |

The architecture separates acquisition, processing, health decisions, diagnostics, and validation logic so that each part can be tested and explained independently.

## 5. Data flow

The data path is:

1. Acquisition thread reads the BMP280 through Zephyr sensor APIs.
2. The sample is wrapped in a sensor_sample structure.
3. The sample is published to a finite Zephyr message queue.
4. Processing thread receives samples from the queue.
5. Processing updates statistics, timing metrics, health state, and environment state.
6. Diagnostic shell commands read a published snapshot of the current system state.
7. Logs and shell output provide validation evidence.

The queue depth is 4. Under queue pressure, the implemented policy is to preserve existing queued samples and drop the newest sample when the queue is full.

## 6. RTOS design

Implemented RTOS behavior:

| RTOS element | Actual behavior |
|---|---|
| Acquisition thread | Reads sensor samples periodically |
| Processing thread | Consumes queued samples and updates system state |
| Message queue | Transfers sensor samples from acquisition to processing |
| Diagnostic shell | Runs on serial shell backend |
| Logging | Zephyr logging enabled for runtime evidence |
| Thread analyzer | Used to measure stack high-water usage |

The sampling period used by the firmware is 2000 ms. During normal operation and the stability run, measured intervals were about 2070 to 2071 ms with zero missed deadlines.

## 7. Node health vs environmental status

FieldSense-Z separates node health from environmental status.

Node health describes whether the embedded system itself is operating correctly:

- INITIALIZING
- HEALTHY
- WARNING
- FAULT

Environmental status describes the sensed environment:

- UNKNOWN
- NORMAL
- HIGH_TEMPERATURE
- PRESSURE_ALERT

This separation matters because a high temperature is not the same as a broken node. A sensor failure, stale data, missed deadlines, or queue pressure can affect node health, while temperature and pressure thresholds affect environmental status.

Implemented thresholds:

| Parameter | Value |
|---|---:|
| Sampling period | 2000 ms |
| Missed deadline threshold | 2250 ms |
| Stale data threshold | 6000 ms |
| Recovery requirement | 5 consecutive valid samples |
| High temperature enter | 30.000 C |
| High temperature clear | 28.000 C |
| Pressure low enter | 95.000 kPa |
| Pressure high enter | 105.000 kPa |
| Pressure low clear | 97.000 kPa |
| Pressure high clear | 103.000 kPa |

## 8. Building

From the Zephyr workspace:

    cd C:\zephyrproject

    & C:\zephyrproject\.venv\Scripts\Activate.ps1

    $env:Path = "C:\Program Files\CMake\bin;C:\Program Files\7-Zip;" + $env:Path
    $env:ZEPHYR_SDK_INSTALL_DIR = "C:\zephyrproject\zephyr-sdk-1.0.1"
    $env:ZEPHYR_TOOLCHAIN_VARIANT = "zephyr"
    $env:PYTHONUTF8 = "1"
    $env:PYTHONIOENCODING = "utf-8"

    $repo = "C:\dev\fieldsense-z"
    $board = "doit_esp32_devkit_v1/esp32/procpu"
    $build = "$repo\build\hardware_validation"

    west build -b $board -d $build $repo

## 9. Flashing

With the ESP32 connected:

    west flash -d $build

Serial monitor:

    python -m serial.tools.miniterm COM9 115200

Use the actual COM port for the board.

## 10. Shell commands

Implemented shell commands:

| Command | Purpose |
|---|---|
| node status | Prints node health, environmental status, counters, queue state, and active injections |
| node latest | Prints latest valid temperature and pressure sample |
| node stats | Prints environmental statistics |
| node timing | Prints sampling period, intervals, missed deadlines, and stale-data status |
| node faults | Prints fault counters and transition counters |
| node reset-stats | Requests statistics/timing reset on the next processed sample |
| node thresholds | Prints configured health and environmental thresholds |
| node threads | Prints thread analyzer stack usage |
| node inject ... | Controls deterministic software fault injection |

## 11. Fault injection

Implemented fault injection commands:

| Command | Behavior |
|---|---|
| node inject sensor-failure | Forces sensor read failure behavior |
| node inject stale-publication | Forces stale-data behavior |
| node inject processing-delay | Adds processing delay |
| node inject queue-pressure | Generates queue pressure and queue overflow |
| node inject invalid-measurement | Generates invalid measurement behavior |
| node inject normal-environment | Forces controlled normal readings |
| node inject clear | Clears all active injections |

Fault injection was used only for validation and demonstration. It does not replace physical testing.

## 12. Validation

Hardware validation covered:

| Test | Result |
|---|---|
| Cold boot | PASS |
| Normal measurements | PASS |
| Environmental threshold | PASS |
| Sensor unavailable | PASS |
| Sensor read failure | PASS |
| Stale data | PASS |
| Queue pressure | PASS |
| Fault recovery | PASS |
| Reset-stats | PASS |
| Power cycle | PASS |
| 30-60 minute stability run | PASS |

The stability run lasted about 40 minutes. Final stability evidence showed healthy node state, normal environmental state, 1176 valid samples in final stats, 0 invalid samples, 0 queue overflows, 0 missed deadlines, and stale_data no.

## 13. Resource results

Measured thread analyzer results from the stability run:

| Thread | Used stack | Allocated stack | Usage |
|---|---:|---:|---:|
| fieldsense_proc | 1152 bytes | 2048 bytes | 56 percent |
| fieldsense_acq | 800 bytes | 2048 bytes | 39 percent |
| shell_uart | 1920 bytes | 2048 bytes | 93 percent |
| logging | 288 bytes | 1024 bytes | 28 percent |
| idle | 208 bytes | 1024 bytes | 20 percent |
| ISR0 | 544 bytes | 2048 bytes | 26 percent |

The shell stack is intentionally left unchanged even though usage was high. Stacks were not reduced just to make the numbers look better.

Measured stability timing:

| Metric | Value |
|---|---:|
| requested_period | 2000 ms |
| latest_interval | 2071 ms |
| mean_interval | 2070 ms |
| missed_deadlines | 0 |
| stale_data | no |

## 14. Limitations

Current limitations:

- BMP280 hardware supports temperature and pressure only.
- Humidity is not available with the verified module.
- No Wi-Fi, Bluetooth, MQTT, cloud dashboard, or mobile app is implemented.
- No relay or external actuator was used.
- Serial screenshots were not captured; serial logs are the primary evidence.
- Stability run was 40 minutes, not a full day or long-term deployment.
- Measurements were not calibrated against a lab reference instrument.
- Queue pressure and sensor read failure are partly validated using deterministic software injection.
- The captured thread analyzer output did not list a system workqueue stack entry.

## 15. What I personally implemented

I implemented the FieldSense-Z firmware and validation flow as an embedded systems project, not only a sensor demo. I brought up the ESP32 Zephyr environment, validated I2C wiring, identified the HW-611 module as a BMP280 by chip ID, built the sensor service, created the acquisition and processing pipeline, added message queue handling, implemented statistics and timing metrics, built the health and environmental state model, added diagnostic shell commands, added deterministic fault injection, measured resource usage, and completed evidence-backed hardware validation.

I also documented the debugging process, validation procedure, resource measurements, limitations, and requirements-to-test traceability so the project can be reviewed as an engineering artifact.
