# Test Strategy

## Purpose

The test strategy combines deterministic software tests with hardware validation. Software tests verify processing and state logic without physical hardware. Hardware validation verifies the ESP32, BMP280 wiring, sensor behavior, shell commands, and fault behavior on the real system.

## Software tests

Implemented software test coverage includes:

- processing and statistics tests
- health state transition tests
- deterministic synthetic sample tests
- threshold boundary tests
- stale-data tests
- queue overflow behavior tests
- transient error behavior tests
- environmental alert behavior while node health remains healthy
- small integration-style pipeline tests without physical hardware

Previously completed test results:

| Test suite | Result |
|---|---|
| processing_stats | 10 of 10 test cases passed |
| health_state | 12 of 12 test cases passed |

## Hardware tests

Hardware validation includes:

- cold boot
- normal measurements
- environmental threshold
- sensor unavailable
- sensor read failure
- stale data
- queue pressure
- fault recovery
- reset-stats
- power cycle
- 30-60 minute stability run

## Evidence rule

A test cannot be marked PASS without evidence. Evidence can include:

- serial logs
- build logs
- flash logs
- hardware photos
- stability logs
- diagnostic shell output

Screenshots were not captured, so serial logs are the primary evidence.

## What software tests prove

Software tests prove deterministic logic behavior, such as:

- statistics updates
- state transitions
- recovery criteria
- stale-data state behavior
- threshold boundary behavior
- queue event handling logic

## What software tests do not prove

Software tests do not prove:

- physical wiring
- I2C electrical behavior
- live BMP280 measurement accuracy
- ESP32 serial behavior
- real power-cycle behavior
- real disconnect/reconnect behavior

Those are covered by hardware validation.
