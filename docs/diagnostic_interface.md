# Diagnostic Interface

FieldSense-Z exposes a serial shell under the command group:

- node

## Commands

| Command | Purpose |
|---|---|
| node status | Prints node state, environment state, sample counters, queue state, and active injections |
| node latest | Prints the latest valid temperature and pressure sample |
| node stats | Prints environmental statistics |
| node timing | Prints interval, deadline, and stale-data metrics |
| node faults | Prints fault counters and transition counters |
| node reset-stats | Requests reset of statistics and timing counters |
| node thresholds | Prints configured thresholds |
| node threads | Prints thread analyzer stack usage |
| node inject sensor-failure | Forces sensor read failure behavior |
| node inject stale-publication | Forces stale-data behavior |
| node inject processing-delay | Adds processing delay |
| node inject queue-pressure | Generates queue pressure |
| node inject invalid-measurement | Generates invalid measurement behavior |
| node inject normal-environment | Forces controlled normal readings |
| node inject clear | Clears all fault injections |

## Evidence

The diagnostic interface was used for validation. The logs include evidence for:

- normal measurements
- sensor unavailable
- sensor read failure
- stale data
- queue pressure
- fault recovery
- reset-stats
- power cycle
- stability run
- thread stack usage

## Screenshot note

Serial screenshots were not captured. Saved serial logs are the primary evidence.
