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

