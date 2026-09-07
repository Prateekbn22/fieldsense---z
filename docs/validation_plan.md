\## Deterministic fault injection validation



Software fault injection is used to verify predictable fault handling before and alongside physical fault testing.



Physical tests are still useful, but they are harder to repeat exactly.



Software injection allows the same fault to be triggered repeatedly with known expected behavior.



\## Fault injection test matrix



| Test | Command | Expected behavior |

|---|---|---|

| Baseline | `node status` | No active injections, node healthy |

| Sensor read failure | `node inject sensor-failure` | Sensor failure counter increases, node enters `WARNING`, then `FAULT` |

| Stale publication | `node inject stale-publication` | Stale-data status becomes active, stale counter increases |

| Processing delay | `node inject processing-delay` | Processing slows, missed deadlines or queue pressure can build |

| Queue pressure | `node inject queue-pressure` | Queue-full count increases, queue-overflow counter increases |

| Invalid measurement | `node inject invalid-measurement` | Measurement validation fails, invalid sample count increases |

| Clear faults | `node inject clear` | Active injection mask clears and recovery requires valid samples |

| Final clean check | `node status`, `node timing`, `node faults` | Node returns to healthy state with no active injections |



\## Pass criteria



A test passes when:



\- the injected fault is visible in `node status`,

\- the expected counter increases,

\- the expected health transition occurs,

\- the fault is reversible with `node inject clear`,

\- the node recovers only after the configured recovery condition,

\- no hardware wiring or power changes are required.



\## Final clean-check result



The final clean check passed.



The node returned to:



```text

health: HEALTHY

last\_fault\_reason: NONE

fault\_injection\_mask: 0x00000000

active\_injections: none

stale\_data: no


## Queue backpressure and recovery validation

### Goal

This validation confirms that FieldSense-Z can handle producer/consumer imbalance, finite queue capacity, queue-full behavior, recovery hysteresis, repeated sensor errors, stale data, and environmental alert clearing.

### Controlled sequence

```text
normal operation
→ slow processing
→ queue occupancy rises
→ queue-full policy activates
→ normal processing resumes
→ queue drains
→ recovery criteria are met
```

### Test commands

The following diagnostic shell commands were used:

```text
node inject clear
node reset-stats
node status
node faults
node inject processing-delay
node inject queue-pressure
node inject clear
node inject sensor-failure
node inject stale-publication
node inject normal-environment
node latest
node timing
node faults
```

### Producer/consumer imbalance test

The processing-delay injection intentionally slowed the consumer thread.

Expected result:

```text
active_injections:
- processing-delay
```

The queue occupancy and timing counters were checked using:

```text
node status
node faults
```

### Queue-full policy test

The queue-pressure injection intentionally created extra sample publications.

Expected result:

```text
queue_full_count increases
queue_overflow_events increases
queue overflow logs appear
policy=drop_newest_preserve_oldest
```

This confirms that the finite queue filled and the nonblocking drop-newest policy activated.

### Recovery test

After clearing active injections with:

```text
node inject clear
```

the node was expected to recover only after the configured number of valid samples.

Expected final result:

```text
health: HEALTHY
last_fault_reason: NONE
active_injections: none
```

### Repeated sensor error test

The repeated sensor error test used:

```text
node inject sensor-failure
```

Expected result during injection:

```text
health: FAULT
last_fault_reason: SENSOR_FAILURES
consecutive_sensor_failures: 3 or more
```

Expected result after clearing:

```text
health: HEALTHY
last_fault_reason: NONE
```

### Stale data test

The stale data test used:

```text
node inject stale-publication
```

Expected result during injection:

```text
stale_data: yes
last_fault_reason: STALE_DATA
```

Expected result after clearing:

```text
stale_data: no
active_injections: none
```

The test also confirmed that stale-publication injection no longer creates unsigned wraparound timing values.

### Environmental alert clearing test

The environmental alert clearing test used:

```text
node inject normal-environment
```

Expected result:

```text
environment: NORMAL
temperature: 26.000 C
pressure: 100.000 kPa
```

This verifies environmental alert clearing without changing hardware wiring.

### Shared-state review result

The shared-state review confirmed:

- statistics, timing metrics, and state model are owned by the processing thread,
- diagnostic shell reads a mutex-protected snapshot,
- queue-full count is atomic,
- fault-injection state is accessed through the fault-injection service,
- no unnecessary synchronization was added.

### Evidence

Serial evidence is saved in:

```text
results/logs/queue_backpressure.txt
```

Build and flash evidence are saved in:

```text
results/logs/queue_backpressure_build.txt
results/logs/queue_backpressure_flash.txt
```

### Pass criteria

This milestone passes when:

- normal operation starts with no active injections,
- processing-delay injection is visible,
- queue occupancy rises,
- queue-full policy activates,
- queue-full and queue-overflow counters increase,
- clearing injections resumes normal processing,
- queue occupancy drains,
- repeated sensor error enters fault,
- stale data is detected and then cleared,
- environmental alert clearing is verified,
- final clean check returns to healthy state.


# FieldSense-Z Hardware Validation Procedure

## Purpose

This procedure validates FieldSense-Z on real ESP32 + BMP280 hardware.

The goal is to prove the firmware behavior with evidence, not assumptions.

No test may be marked `PASS` unless the result is supported by saved evidence such as:

```text
serial log
photo
screenshot
build log
flash log
diagnostic-shell output
```

## Safety rules

### General hardware safety

Before touching wiring:

```text
1. Stop the serial monitor if needed.
2. Disconnect USB power from the ESP32.
3. Confirm the circuit is powered off.
4. Make the wiring change.
5. Record exactly what was disconnected or changed.
6. Restore wiring safely.
7. Re-check 3.3 V, GND, SDA, and SCL.
8. Power the ESP32 again.
```

### BMP280 wiring baseline

Normal wiring must be restored to:

```text
BMP280/HW-611 VCC -> ESP32 3V3
BMP280/HW-611 GND -> ESP32 GND
BMP280/HW-611 SDA -> ESP32 GPIO21
BMP280/HW-611 SCL -> ESP32 GPIO22
CSB/CS -> not connected
SDO -> not connected
```

Do not connect the BMP280 module VCC to 5 V.

## Required evidence locations

Save evidence in:

```text
results/logs/
results/photos/
results/screenshots/
```

Recommended filenames:

```text
results/logs/hardware_validation_serial.txt
results/logs/hardware_validation_build.txt
results/logs/hardware_validation_flash.txt
results/logs/stability_run_30_60_min.txt

results/photos/baseline_wiring_before_validation.jpg
results/photos/sensor_unavailable_wiring_change.jpg
results/photos/restored_wiring_after_fault_test.jpg

results/screenshots/final_github_commit.png
results/screenshots/serial_terminal_validation.png
```

## Metrics to record for every test

For each validation test, record:

```text
valid samples
sensor errors
queue overflows
missed deadlines
state transitions
unexpected resets
unexpected lockups
health state
environment state
active fault injections
```

Use these diagnostic commands:

```text
node status
node latest
node stats
node timing
node faults
node thresholds
node threads
```

Fault-injection commands may be used only when the test calls for controlled software faults:

```text
node inject sensor-failure
node inject stale-publication
node inject processing-delay
node inject queue-pressure
node inject invalid-measurement
node inject normal-environment
node inject clear
```

## Pass/fail rule

A test can be marked `PASS` only when:

```text
the expected behavior is visible in saved evidence
no unexpected reset occurred
no unexpected lockup occurred
the final health state is explained
the final fault-injection state is clear unless the test intentionally leaves it active
```

A test must be marked `FAIL` if:

```text
the ESP32 resets unexpectedly
the shell locks up
the node stops publishing samples unexpectedly
a fault state does not match the expected behavior
wiring cannot be safely restored
evidence is missing
```

If evidence is incomplete, mark the test:

```text
INCOMPLETE
```

Do not mark it `PASS`.

---

## Validation test matrix

### Test 1: Cold boot

Purpose:

Verify that the ESP32 boots cleanly and FieldSense-Z starts without manual intervention.

Procedure:

```text
1. Power off the ESP32.
2. Confirm normal BMP280 wiring.
3. Connect USB power.
4. Open serial monitor at 115200 baud.
5. Capture the full boot log.
6. Wait until the shell prompt appears.
7. Run node status.
8. Run node faults.
```

Expected evidence:

```text
boot banner visible
FieldSense-Z application logs visible
shell prompt visible
node status responds
node faults responds
no unexpected reset loop
```

Status before execution:

```text
PENDING
```

---

### Test 2: Normal measurements

Purpose:

Verify normal temperature and pressure measurement processing.

Procedure:

```text
1. Run node inject clear.
2. Run node reset-stats.
3. Wait 20 seconds.
4. Run node status.
5. Run node latest.
6. Run node stats.
7. Run node timing.
8. Run node faults.
```

Expected evidence:

```text
valid samples increase
latest sample shows temperature
latest sample shows pressure
humidity is reported unsupported
sensor errors are not continuously increasing
queue overflows are not continuously increasing
stale_data is no during normal operation
```

Status before execution:

```text
PENDING
```

---

### Test 3: Environmental threshold

Purpose:

Verify environmental alert behavior using deterministic software stimulus.

Procedure:

```text
1. Run node inject normal-environment.
2. Wait 10 seconds.
3. Run node status.
4. Run node latest.
5. Run node faults.
6. Run node inject clear.
7. Wait 10 seconds.
8. Run node status.
```

Expected evidence:

```text
normal-environment injection becomes active
temperature reads 26.000 C during injection
pressure reads 100.000 kPa during injection
environment can clear to NORMAL
node health remains HEALTHY unless another health fault exists
injection clears after node inject clear
```

Status before execution:

```text
PENDING
```

---

### Test 4: Sensor unavailable

Purpose:

Verify behavior when the physical sensor is unavailable.

Physical wiring safety:

```text
Power off before disconnecting anything.
Record what was disconnected.
Restore wiring safely after the test.
```

Procedure:

```text
1. Power off ESP32.
2. Disconnect BMP280 SDA or VCC.
3. Take a photo of the disconnected wiring.
4. Power on ESP32.
5. Capture boot and runtime serial log.
6. Run node status.
7. Run node faults.
8. Power off ESP32.
9. Restore wiring.
10. Take a photo of restored wiring.
11. Power on ESP32.
12. Confirm normal measurement recovery.
```

Expected evidence:

```text
wiring change photo saved
sensor unavailable behavior visible
sensor errors visible
node moves toward WARNING or FAULT depending on failure duration
restored wiring photo saved
normal readings return after wiring is restored
```

Status before execution:

```text
PENDING
```

---

### Test 5: Sensor read failure

Purpose:

Verify controlled repeated sensor read failure without changing wiring.

Procedure:

```text
1. Run node inject clear.
2. Run node reset-stats.
3. Wait 10 seconds.
4. Run node inject sensor-failure.
5. Wait 10 seconds.
6. Run node status.
7. Run node faults.
8. Run node inject clear.
9. Wait 20 seconds.
10. Run node status.
11. Run node faults.
```

Expected evidence:

```text
sensor-failure injection becomes active
health moves HEALTHY -> WARNING -> FAULT
last_fault_reason becomes SENSOR_FAILURES
consecutive_sensor_failures increases
after clearing injection, node recovers after required valid samples
```

Status before execution:

```text
PENDING
```

---

### Test 6: Stale data

Purpose:

Verify stale-data detection.

Procedure:

```text
1. Run node inject clear.
2. Run node reset-stats.
3. Wait 10 seconds.
4. Run node inject stale-publication.
5. Wait 10 seconds.
6. Run node timing.
7. Run node faults.
8. Run node inject clear.
9. Wait 20 seconds.
10. Run node timing.
11. Run node faults.
```

Expected evidence:

```text
stale-publication injection becomes active
stale_data becomes yes
last_fault_reason shows stale-data behavior if threshold is reached
after clearing injection, stale_data returns to no
no unsigned wraparound timing value appears
```

Status before execution:

```text
PENDING
```

---

### Test 7: Queue pressure

Purpose:

Verify finite queue behavior and queue overflow counting.

Procedure:

```text
1. Run node inject clear.
2. Run node reset-stats.
3. Wait 10 seconds.
4. Run node inject processing-delay.
5. Wait 20 seconds.
6. Run node inject queue-pressure.
7. Wait 10 seconds.
8. Run node status.
9. Run node faults.
10. Run node timing.
11. Run node inject clear.
12. Wait 20 seconds.
13. Run node status.
14. Run node faults.
```

Expected evidence:

```text
processing-delay injection becomes active
queue-pressure injection becomes active
queue_full_count increases
queue_overflow_events increases
missed_deadlines may increase
logs show queue overflow
policy is drop_newest_preserve_oldest
after clearing injections, queue pressure stops
```

Status before execution:

```text
PENDING
```

---

### Test 8: Fault recovery

Purpose:

Verify that the node does not recover immediately after one good sample, but waits for recovery criteria.

Procedure:

```text
1. Create a fault using node inject sensor-failure.
2. Wait until node faults shows FAULT.
3. Run node inject clear.
4. Run node faults every 5 seconds until HEALTHY.
5. Record recovery_valid_samples.
```

Expected evidence:

```text
node reaches FAULT
fault reason is visible
after clearing fault, recovery_valid_samples increases
node returns to HEALTHY only after required valid samples
last_fault_reason returns to NONE after recovery
```

Status before execution:

```text
PENDING
```

---

### Test 9: Reset-stats

Purpose:

Verify diagnostic statistics reset behavior.

Procedure:

```text
1. Run node status.
2. Run node stats.
3. Run node timing.
4. Run node reset-stats.
5. Wait for the next processed sample.
6. Run node status.
7. Run node stats.
8. Run node timing.
9. Run node faults.
```

Expected evidence:

```text
reset-stats request is accepted
processing/statistics/timing counters reset on next processed sample
node health is not forcibly changed by reset-stats
new samples continue after reset
```

Status before execution:

```text
PENDING
```

---

### Test 10: Power cycle

Purpose:

Verify clean restart after power removal and restoration.

Procedure:

```text
1. Save current serial output.
2. Power off ESP32 by unplugging USB.
3. Wait 10 seconds.
4. Reconnect USB.
5. Reopen serial monitor.
6. Capture boot log.
7. Run node status.
8. Run node latest.
9. Run node faults.
```

Expected evidence:

```text
clean boot after power cycle
shell returns
sensor readings resume
no unexpected reset loop
no lockup
```

Status before execution:

```text
PENDING
```

---

### Test 11: 30-60 minute stability run

Purpose:

Verify longer runtime stability.

Procedure:

```text
1. Run node inject clear.
2. Run node reset-stats.
3. Start serial logging.
4. Let the system run for 30 to 60 minutes.
5. Every 10 minutes, run:
   node status
   node timing
   node faults
6. At the end, run:
   node status
   node latest
   node stats
   node timing
   node faults
   node threads
```

Expected evidence:

```text
valid samples continue increasing
unexpected resets = 0
unexpected lockups = 0
sensor errors are explained if present
queue overflows are explained if present
missed deadlines are explained if present
final shell commands respond normally
```

Status before execution:

```text
PENDING
```

---

## Final validation decision

The hardware validation can be marked complete only when:

```text
all required tests are PASS or explicitly documented as FAIL/INCOMPLETE
all PASS results have evidence
physical wiring changes were photographed or clearly logged
final wiring is restored safely
final node state is documented
unexpected resets and lockups are recorded
results/validation_results.md is filled
```

