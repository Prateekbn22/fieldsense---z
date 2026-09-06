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

