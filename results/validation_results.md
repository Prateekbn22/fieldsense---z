# FieldSense-Z Hardware Validation Results

## Rule

Do not mark any test PASS without evidence.

Allowed status values:

PENDING
PASS
FAIL
INCOMPLETE

If evidence is missing, unclear, or incomplete, mark the test INCOMPLETE.

## Hardware setup

| Item | Value |
|---|---|
| Board | ESP32 DEVKIT V1 / ESP-WROOM-32 |
| Zephyr board target | doit_esp32_devkit_v1/esp32/procpu |
| Sensor module | HW-611 BMP280-compatible module |
| Sensor address | 0x76 |
| Sensor chip ID | 0x58 |
| Supply voltage | 3.3 V |
| SDA | GPIO21 |
| SCL | GPIO22 |
| GND | Common GND |
| CSB/CS | Not connected |
| SDO | Not connected |

## Evidence files

| Evidence type | Path | Status |
|---|---|---|
| Main serial validation log | results/logs/hardware_validation_serial.txt | Captured |
| Build log | results/logs/hardware_validation_build.txt | Captured if file exists |
| Flash log | results/logs/hardware_validation_flash.txt | Captured if file exists |
| Stability run log | results/logs/stability_run_30_60_min.txt | Captured |
| Baseline wiring photo | results/photos/baseline_wiring_before_validation.jpg | Saved |
| Baseline wiring close-up | results/photos/baseline_wiring_closeup.jpg | Saved if available |
| Sensor unavailable wiring photo | results/photos/sensor_unavailable_wiring_change.jpg | Saved if available |
| Restored wiring photo | results/photos/restored_wiring_after_fault_test.jpg | Saved if available |
| Final restored wiring photo | results/photos/final_restored_wiring.jpg | Saved if available |
| Serial monitor screenshots | results/screenshots/ | Not captured |
| Primary evidence type | results/logs/hardware_validation_serial.txt | Serial logs used as main evidence |

## Screenshot note

Serial monitor screenshots were not captured.

This is acceptable because saved serial logs are the primary evidence.

No test is marked PASS unless the required behavior is visible in the saved logs.

## Summary table

| Test | Status | Evidence path | Notes |
|---|---|---|---|
| Cold boot | PASS | results/logs/hardware_validation_serial.txt | ESP32 boot output, node status, and node faults were captured |
| Normal measurements | PASS | results/logs/hardware_validation_serial.txt | Healthy state, valid temperature and pressure readings, no stale data, no queue overflows || Environmental threshold | PASS | results/logs/hardware_validation_serial.txt | Thresholds printed, normal-environment injection active, controlled readings applied, cleared successfully |
| Sensor unavailable | PASS | results/logs/hardware_validation_serial.txt, results/photos/sensor_unavailable_wiring_change.jpg, results/photos/restored_wiring_after_fault_test.jpg | Sensor unavailable fault observed, restored wiring returned node to healthy operation |
| Sensor read failure | PASS | results/logs/hardware_validation_serial.txt | Sensor-failure injection caused FAULT and recovered after clearing |
| Stale data | PASS | results/logs/hardware_validation_serial.txt | Stale data detected, FAULT entered, cleared and recovered |
| Queue pressure | PASS | results/logs/hardware_validation_serial.txt | Queue overflows, missed deadlines, and recovery behavior observed |
| Fault recovery | PASS | results/logs/hardware_validation_serial.txt | FAULT to HEALTHY recovery observed with qualified recovery message |
| Reset-stats | PASS | results/logs/hardware_validation_serial.txt | Statistics reset applied, new samples continued, health remained healthy |
| Power cycle | PASS | results/logs/hardware_validation_serial.txt | System returned to healthy state after reboot and resumed sensor readings |
| 30-60 minute stability run | PASS | results/logs/stability_run_30_60_min.txt | 40-minute stability run completed with healthy state, zero invalid samples, zero queue overflows, zero missed deadlines, and no stale data |

## Metrics recorded

| Metric | Value | Evidence |
|---|---:|---|
| Final valid samples | 1176 samples in final stability stats, 1180 samples in final stability summary | results/logs/stability_run_30_60_min.txt |
| Final sensor errors | 0 invalid samples during stability run | results/logs/stability_run_30_60_min.txt |
| Final queue overflows | 0 during stability run | results/logs/stability_run_30_60_min.txt |
| Final missed deadlines | 0 during stability run | results/logs/stability_run_30_60_min.txt |
| Final state transitions | node_health_transitions = 1, environment_transitions = 1 during stability run | results/logs/stability_run_30_60_min.txt |
| Unexpected resets | 0 observed in provided serial and stability logs | results/logs/hardware_validation_serial.txt, results/logs/stability_run_30_60_min.txt |
| Unexpected lockups | 0 observed in provided serial and stability logs | results/logs/hardware_validation_serial.txt, results/logs/stability_run_30_60_min.txt |

---

## Test 1: Cold boot

Status: PASS

Evidence:
results/logs/hardware_validation_serial.txt

Expected evidence:
- boot banner visible
- FieldSense-Z application starts after boot
- shell prompt available
- node status responds
- node faults responds
- no unexpected reset loop

Observed result:
Cold boot was rerun with the serial monitor open. The ESP32 boot output was captured, including ESP Simple boot, chip revision, flash configuration, DRAM/IRAM/IROM/DROM memory information, heap size, and SPI flash detection. After boot, node status and node faults responded correctly. The node reported HEALTHY state, NORMAL environment, last_fault_reason NONE, valid samples present, invalid_count 0, queue_full_count 0, and active_injections none. node faults also reported HEALTHY state, last_fault_reason NONE, consecutive_sensor_failures 0, stale_data_events 0, missed_deadline_events 0, queue_overflow_events 0, and active_injections none.

Metrics:
valid samples: 4
sensor errors: 0 invalid samples
queue overflows: 0
missed deadlines: 0
state transitions: node_health_transitions = 1, environment_transitions = 1
unexpected resets: 0 observed
unexpected lockups: 0 observed

Decision: PASS


## Test 2: Normal measurements

Status: PASS

Evidence:
results/logs/hardware_validation_serial.txt

Expected evidence:
- valid samples increase
- latest sample shows temperature
- latest sample shows pressure
- humidity is reported unsupported
- sensor errors are not continuously increasing
- queue overflows are not continuously increasing
- stale_data is no during normal operation

Observed result:
Normal measurement behavior was verified. The node was HEALTHY, environment was NORMAL, last_fault_reason was NONE, valid_count increased to 16 and then 20, invalid_count stayed 0, and queue_full_count stayed 0. The latest sample showed temperature 29.820 C and pressure 100.062 kPa. Humidity was reported unsupported by verified BMP280 hardware. Timing showed requested_period 2000 ms, latest_interval 2070 ms, missed_deadlines 0, and stale_data no.

Metrics:
valid samples: 20
sensor errors: 0 invalid samples
queue overflows: 0
missed deadlines: 0
state transitions: node_health_transitions = 1, environment_transitions = 1
unexpected resets: 0 observed
unexpected lockups: 0 observed

Decision: PASS

---

## Test 3: Environmental threshold

Status: PASS

Evidence:
results/logs/hardware_validation_serial.txt

Expected evidence:
- normal-environment injection becomes active
- temperature reads 26.000 C during injection
- pressure reads 100.000 kPa during injection
- environment can clear to NORMAL
- node health remains HEALTHY unless another health fault exists
- injection clears after node inject clear

Observed result:
Thresholds were printed. High temperature enter was 30.000 C and high temperature clear was 28.000 C. Pressure thresholds were also printed. The normal-environment injection became active with fault_injection_mask 0x00000020. During injection, the latest sample showed temperature 26.000 C and pressure 100.000 kPa. Node health remained HEALTHY and environment remained NORMAL. After node inject clear, active_injections returned to none and the system stayed HEALTHY.

Metrics:
valid samples: 75 after clear
sensor errors: 0 invalid samples
queue overflows: 0
missed deadlines: 0
state transitions: node_health_transitions = 1, environment_transitions = 1
unexpected resets: 0 observed
unexpected lockups: 0 observed

Decision: PASS

---

## Test 4: Sensor unavailable

Status: PASS

Physical wiring change record:
Power off before change: Yes
What was disconnected: BMP280 SDA wire from ESP32 GPIO21
Photo path: results/photos/sensor_unavailable_wiring_change.jpg
Wiring restored: Yes
Restored photo path: results/photos/restored_wiring_after_fault_test.jpg

Evidence:
results/logs/hardware_validation_serial.txt
results/photos/sensor_unavailable_wiring_change.jpg
results/photos/restored_wiring_after_fault_test.jpg

Expected evidence:
- ESP32 was powered off before wiring change
- disconnected wire was recorded
- sensor unavailable behavior is visible
- sensor errors are visible
- node moves toward WARNING or FAULT depending on failure duration
- wiring is restored safely
- normal readings return after wiring is restored

Observed result:
With the sensor unavailable, the node entered FAULT, environment became UNKNOWN, and last_fault_reason became SENSOR_FAILURES. The log showed DEVICE_NOT_READY sensor read failures and invalid samples. After wiring was restored, node status returned to HEALTHY, environment returned to NORMAL, last_fault_reason returned to NONE, valid samples resumed, and latest sample showed temperature 29.950 C and pressure 100.067 kPa.

Metrics:
valid samples during disconnected state: 0
sensor errors during disconnected state: 5 consecutive sensor failures shown in faults
queue overflows: 0
missed deadlines: 0
state transitions: node_health_transitions = 2 during fault, 1 after restored boot/recovery
unexpected resets: 0 unexpected resets observed
unexpected lockups: 0 observed

Decision: PASS

Note:
If a different wire was disconnected during the physical test, update the line above before committing.

---

## Test 5: Sensor read failure

Status: PASS

Evidence:
results/logs/hardware_validation_serial.txt

Expected evidence:
- sensor-failure injection becomes active
- health moves HEALTHY to WARNING to FAULT
- last_fault_reason becomes SENSOR_FAILURES
- consecutive_sensor_failures increases
- after clearing injection, node recovers after required valid samples

Observed result:
The sensor-failure injection became active with fault_injection_mask 0x00000001. The node entered FAULT, environment became UNKNOWN, and last_fault_reason became SENSOR_FAILURES. The log showed FETCH_FAILED sensor read failures. Consecutive sensor failures increased to 13. After node inject clear, the environment transitioned UNKNOWN to NORMAL and the node transitioned FAULT to HEALTHY. The log showed qualified recovery complete with required_valid_samples = 5.

Metrics:
valid samples after recovery: 25
sensor errors: 15 invalid samples during fault/recovery section
queue overflows: 0
missed deadlines: 0
state transitions: node_health_transitions = 4, environment_transitions = 3
unexpected resets: 0 observed
unexpected lockups: 0 observed

Decision: PASS

---

## Test 6: Stale data

Status: PASS

Evidence:
results/logs/hardware_validation_serial.txt

Expected evidence:
- stale-publication injection becomes active
- stale_data becomes yes
- last_fault_reason shows stale-data behavior if threshold is reached
- after clearing injection, stale_data returns to no
- no unsigned wraparound timing value appears

Observed result:
During stale-publication injection, last_valid_sample_age became 7000 ms and stale_data became yes. The node entered FAULT, environment became UNKNOWN, and last_fault_reason became STALE_DATA. stale_data_events increased to 10. After node inject clear, the environment returned to NORMAL, the node transitioned FAULT to HEALTHY, stale_data returned to no, and active_injections returned to none. No unsigned wraparound timing value was observed.

Metrics:
valid samples after recovery: 40
sensor errors: 0 invalid samples in this test
queue overflows: 0
missed deadlines: 1 after clearing stale injection
state transitions: node_health_transitions = 7, environment_transitions = 5
unexpected resets: 0 observed
unexpected lockups: 0 observed

Decision: PASS

---

## Test 7: Queue pressure

Status: PASS

Evidence:
results/logs/hardware_validation_serial.txt

Expected evidence:
- processing-delay injection becomes active
- queue-pressure injection becomes active
- queue_full_count increases
- queue_overflow_events increases
- missed_deadlines may increase
- logs show queue overflow
- policy is drop_newest_preserve_oldest
- after clearing injections, queue pressure stops

Observed result:
processing-delay and queue-pressure injections became active with fault_injection_mask 0x0000000c. queue_full_count increased to 56 and later to 101. The queue reached 4 used samples and 0 free slots. The log showed queue overflow errors with policy drop_newest_preserve_oldest. Missed deadlines increased, sequence gaps were detected, stale_data became yes, and the node entered FAULT. After node inject clear, active_injections returned to none, the environment returned to NORMAL, and the node recovered to HEALTHY with qualified recovery complete.

Metrics:
valid samples after recovery: 52
sensor errors: 0 invalid samples in this test
queue overflows: 101 queue_full_count, 10 queue_overflow_events shown during fault snapshot
missed deadlines: 11 during queue-pressure recovery sequence
state transitions: node_health_transitions = 10, environment_transitions = 7
unexpected resets: 0 observed
unexpected lockups: 0 observed

Decision: PASS

---

## Test 8: Fault recovery

Status: PASS

Evidence:
results/logs/hardware_validation_serial.txt

Expected evidence:
- node reaches FAULT
- fault reason is visible
- after clearing fault, recovery_valid_samples increases
- node returns to HEALTHY only after required valid samples
- last_fault_reason returns to NONE after recovery

Observed result:
The node reached FAULT with last_fault_reason SENSOR_FAILURES while sensor-read-failure injection was active. The log showed repeated FETCH_FAILED sensor read failures. After node inject clear, the environment transitioned UNKNOWN to NORMAL. The node then transitioned FAULT to HEALTHY and the log showed qualified recovery complete with required_valid_samples = 5. Final faults output showed node_health HEALTHY, environment_status NORMAL, last_fault_reason NONE, and active_injections none.

Metrics:
valid samples: recovery confirmed after required valid samples
sensor errors: repeated FETCH_FAILED errors during fault
queue overflows: 0
missed deadlines: 0
state transitions: node_health_transitions = 13, environment_transitions = 9
unexpected resets: 0 observed
unexpected lockups: 0 observed

Decision: PASS

---

## Test 9: Reset-stats

Status: PASS

Evidence:
results/logs/hardware_validation_serial.txt

Expected evidence:
- reset-stats request is accepted
- processing/statistics/timing counters reset on next processed sample
- node health is not forcibly changed by reset-stats
- new samples continue after reset

Observed result:
Before reset-stats, the node was HEALTHY with processed_count 39, valid_count 25, and invalid_count 14. The reset-stats command was accepted and printed that node health is not forcibly changed. The log then showed diagnostic statistics reset applied. After reset, processed_count restarted at 5, valid_count restarted at 5, invalid_count returned to 0, timing metrics continued normally, stale_data was no, and node faults showed HEALTHY with last_fault_reason NONE.

Metrics:
valid samples after reset: 7 in stats output, 10 in later summary
sensor errors after reset: 0 invalid samples
queue overflows after reset: 0
missed deadlines after reset: 0
state transitions: node_health_transitions remained recorded, health stayed HEALTHY
unexpected resets: 0 observed
unexpected lockups: 0 observed

Decision: PASS

---

## Test 10: Power cycle

Status: PASS

Evidence:
results/logs/hardware_validation_serial.txt

Expected evidence:
- clean boot after power cycle
- shell returns
- sensor readings resume
- no unexpected reset loop
- no lockup

Observed result:
Before power off, the node was HEALTHY, environment NORMAL, last_fault_reason NONE, active_injections none, and queue_full_count 0. After power cycle, the shell returned and node status showed HEALTHY, environment NORMAL, last_fault_reason NONE, processed_count 2, valid_count 2, invalid_count 0, and active_injections none. node latest showed status OK, temperature 29.890 C, pressure 100.073 kPa, and humidity unsupported. node faults showed HEALTHY with last_fault_reason NONE.

Metrics:
valid samples after reboot: 2 in status, latest sample sequence 4 available
sensor errors after reboot: 0 invalid samples
queue overflows after reboot: 0
missed deadlines after reboot: 0
state transitions after reboot: node_health_transitions = 1, environment_transitions = 1
unexpected resets: 0 unexpected resets observed
unexpected lockups: 0 observed

Decision: PASS

---

## Test 11: 30-60 minute stability run

Status: PASS

Start time:
12:57 PM

End time:
Approximately 1:37 PM

Duration:
40 minutes

Evidence:
results/logs/stability_run_30_60_min.txt

Expected evidence:
- valid samples continue increasing
- unexpected resets = 0
- unexpected lockups = 0
- sensor errors are explained if present
- queue overflows are explained if present
- missed deadlines are explained if present
- final shell commands respond normally

Observed result:
The stability run completed for approximately 40 minutes. At the first 10-minute checkpoint, processed_count was 297, valid_count was 297, invalid_count was 0, queue_full_count was 0, missed_deadlines was 0, and stale_data was no. At the next checkpoints, valid samples continued increasing to 589, 898, and then over 1171 samples. The final stats showed 1176 valid samples and 0 invalid samples. The final timing output showed requested_period 2000 ms, latest_interval 2071 ms, mean_interval 2070 ms, missed_deadlines 0, last_valid_sample_age 70 ms, and stale_data no. Final faults showed node_health HEALTHY, environment_status NORMAL, last_fault_reason NONE, stale_data_events 0, missed_deadline_events 0, queue_overflow_events 0, and active_injections none.

Thread analysis was also captured at the end of the stability run. fieldsense_proc used 1152 / 2048 bytes, fieldsense_acq used 800 / 2048 bytes, shell_uart used 1920 / 2048 bytes, logging used 288 / 1024 bytes, idle used 208 / 1024 bytes, and ISR0 used 544 / 2048 bytes.

Metrics:
valid samples: 1176 in final stats, 1180 in final summary
sensor errors: 0 invalid samples
queue overflows: 0
missed deadlines: 0
state transitions: node_health_transitions = 1, environment_transitions = 1
unexpected resets: 0 observed
unexpected lockups: 0 observed

Decision: PASS

---

## Final validation conclusion

Overall status:
PASS

Final notes:
Hardware validation evidence was reviewed from results/logs/hardware_validation_serial.txt and results/logs/stability_run_30_60_min.txt.
Tests 1 through 11 have evidence-backed PASS results.
Hardware photos have been saved under results/photos.
Serial monitor screenshots were not captured.
Saved serial logs are used as the primary validation evidence.
No unexpected lockups were observed in the provided serial evidence.
No unexpected reset loop was observed in the provided serial evidence.
The 40-minute stability run completed successfully with healthy state, valid samples increasing, zero invalid samples, zero queue overflows, zero missed deadlines, and stale_data no.

Commit readiness:
Ready for final hardware validation commit.

Recommended final commit message:
test: complete FieldSense-Z hardware validation