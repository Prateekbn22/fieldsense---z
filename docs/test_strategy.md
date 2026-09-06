# Test Strategy

## Goal

FieldSense-Z uses deterministic software tests to verify processing and statistics logic without depending on the physical BMP280 sensor.

The purpose of these tests is to prove that the data-processing layer behaves correctly for known inputs before relying on live hardware data.

## What was tested

This milestone added Ztest-based tests for:

```text
first sample
minimum
maximum
moving average startup
full averaging window
negative temperature
large scaled values
invalid sample
sequence gap
```

## Unit test

A unit test checks one small piece of logic in isolation.

In this milestone, the unit tests check environmental statistics behavior such as first sample handling, minimum value tracking, maximum value tracking, and moving average calculations.

## Integration test

An integration test checks multiple pieces working together.

In this milestone, the processing tests combine fake sensor samples, validation logic, statistics updates, and sequence tracking behavior.

These tests do not use the physical BMP280 sensor.

## Assertion

An assertion is a pass/fail rule inside a test.

For example, the tests assert that:

```text
average of 22.000 C and 24.000 C = 23.000 C
minimum updates when a lower value arrives
maximum updates when a higher value arrives
invalid samples do not update statistics
sequence gaps are detected
```

## Deterministic input

A deterministic input is a fixed known input.

The tests use software-created sensor samples instead of live sensor readings.

Examples:

```text
22.000 C
24.000 C
-5.000 C
85.000 C
100.000 kPa
110.000 kPa
```

Because the values are fixed, the expected results are repeatable.

## Boundary test

A boundary test checks edge cases.

The test suite covers:

```text
first valid sample
startup moving average before the window is full
full moving average window
rolling moving average window
negative milli-Celsius temperature
large scaled integer values
invalid sample rejection
sequence gap detection
duplicate or out-of-order sequence handling
```

## No physical sensor required

These tests do not require:

```text
ESP32
BMP280
BME280
I2C wiring
serial monitor
COM port
```

The test code creates fake `struct sensor_sample` values in software.

The tests run using Zephyr Ztest on `qemu_x86`.

## Test location

The test application is located at:

```text
tests/processing_stats
```

Main test source:

```text
tests/processing_stats/src/main.c
```

Test configuration:

```text
tests/processing_stats/prj.conf
```

Twister metadata:

```text
tests/processing_stats/tests.yaml
```

## Test command used

The test was run with:

```text
west twister -T "$repo\tests\processing_stats" -p qemu_x86 --inline-logs -v
```

## Evidence

Actual test evidence is saved in:

```text
results/logs/processing_tests.txt
```

The passing result showed:

```text
fieldsense.processing_stats PASSED
1 of 1 executed test configurations passed
10 of 10 executed test cases passed
```

## Result

The processing and statistics test milestone passed.

The firmware processing logic now has repeatable software test coverage before depending on live sensor behavior.
