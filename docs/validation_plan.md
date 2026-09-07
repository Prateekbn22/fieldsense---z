# Validation Plan

## Purpose

This plan defines how FieldSense-Z is validated using physical hardware, serial logs, photos, and diagnostic shell output.

No test may be marked PASS without evidence.

## Required evidence

Evidence locations:

| Evidence | Path |
|---|---|
| Main validation serial log | results/logs/hardware_validation_serial.txt |
| Stability run log | results/logs/stability_run_30_60_min.txt |
| Build log | results/logs/hardware_validation_build.txt |
| Flash log | results/logs/hardware_validation_flash.txt |
| Hardware photos | results/photos/ |
| Screenshots | results/screenshots/ |

Serial screenshots were not captured. Serial logs are the primary evidence.

## Hardware safety rule

For physical wiring changes:

1. Power the ESP32 off first.
2. Record what was disconnected.
3. Take a photo.
4. Restore wiring safely.
5. Confirm 3.3 V, GND, SDA, and SCL.
6. Power the board again.
7. Confirm normal readings return.

## Validation tests

| Test | Purpose |
|---|---|
| Cold boot | Verify boot output, shell readiness, healthy status |
| Normal measurements | Verify live temperature and pressure samples |
| Environmental threshold | Verify thresholds and controlled normal-environment injection |
| Sensor unavailable | Verify physical disconnect behavior |
| Sensor read failure | Verify software sensor failure behavior |
| Stale data | Verify stale-data detection and recovery |
| Queue pressure | Verify finite queue behavior and recovery |
| Fault recovery | Verify qualified recovery after FAULT |
| Reset-stats | Verify diagnostic reset behavior |
| Power cycle | Verify restart and sensor recovery |
| 30-60 minute stability run | Verify longer runtime stability |

## Requirements-to-test traceability

| Requirement ID | Requirement | Evidence / Test |
|---|---|---|
| R1 | Firmware boots on ESP32 and shell becomes available | Test 1 cold boot |
| R2 | Node reports healthy status after normal boot | Test 1 cold boot, Test 2 normal measurements |
| R3 | BMP280 temperature and pressure samples are read | Test 2 normal measurements |
| R4 | Humidity is not claimed for BMP280 hardware | Test 2 normal measurements, node latest output |
| R5 | Environmental thresholds are visible and documented | Test 3 environmental threshold |
| R6 | Controlled normal-environment injection works | Test 3 environmental threshold |
| R7 | Physical sensor unavailable condition is detected | Test 4 sensor unavailable |
| R8 | Software sensor read failure is detected | Test 5 sensor read failure |
| R9 | Stale data is detected and causes FAULT when threshold is reached | Test 6 stale data |
| R10 | Queue pressure and queue overflow are detected | Test 7 queue pressure |
| R11 | Processing delay can cause missed deadlines under stress | Test 7 queue pressure |
| R12 | Node recovers only after qualified valid samples | Test 5, Test 8 fault recovery |
| R13 | reset-stats resets diagnostic counters without forcing health state | Test 9 reset-stats |
| R14 | Power cycle returns node to healthy sensor operation | Test 10 power cycle |
| R15 | Node remains stable during longer run | Test 11 stability run |
| R16 | Stack usage is measured instead of guessed | Test 11 node threads, docs/resource_analysis.md |
| R17 | Validation results are evidence-backed | results/validation_results.md |

## Pass criteria

A test passes only when the expected behavior is visible in saved evidence.

A test is incomplete when evidence is missing or unclear.

## Final validation result

The final validation results document records all tests as PASS.
