# Debug Journal

## Environment setup

The project required a working Zephyr environment on Windows, including CMake, west, Python virtual environment, SDK path variables, and ESP32 flashing support.

## Hardware identification

The sensor module was not assumed to be a BME280. I2C validation showed address 0x76 and chip ID 0x58. That identified the module as BMP280-compatible hardware.

Impact:

- temperature supported
- pressure supported
- humidity not supported

## Devicetree alias issue

A devicetree alias naming issue was fixed by remembering that hyphens in devicetree aliases become underscores in C macro usage.

Example:

- fieldsense-env-sensor in devicetree
- DT_ALIAS(fieldsense_env_sensor) in C

## Driver and Kconfig issue

Driver-related link and configuration issues were addressed by enabling the required I2C and sensor configuration. The BMP280/BME280 driver path had to be enabled and the overlay had to be picked up by the build.

## RTOS thread issue

A thread definition issue was fixed by using a valid thread start delay value in K_THREAD_DEFINE.

## Function name conflict

A helper function name conflicted with an existing Zephyr helper. The project helper was renamed to avoid the conflict.

## Test configuration issue

Ztest configuration required simple valid Kconfig content. Incorrect or malformed Kconfig settings caused failures until the test prj.conf was cleaned up.

## Pressure boundary test issue

A pressure threshold test initially assumed equality at the high-enter boundary should trigger alert. The implemented behavior used strict enter behavior, so the test expectation was corrected to match actual state-model behavior.

## Validation evidence issue

The first cold boot record originally missed the full boot banner. The cold boot was rerun to capture ESP32 boot output and diagnostic shell responses.
