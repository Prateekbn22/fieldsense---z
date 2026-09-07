# Devicetree Notes

## Board target

The project builds for:

- doit_esp32_devkit_v1/esp32/procpu

## I2C pins

The overlay configures ESP32 I2C0 using:

- SDA GPIO21
- SCL GPIO22
- 100 kHz clock frequency

## Sensor node

The sensor node is defined at address 0x76.

The project uses the Zephyr Bosch environmental sensor driver path that accepts the compatible string used by the BME280/BMP280 driver support. Even though the compatible string references the Bosch driver family, the actual hardware was identified as BMP280 by chip ID 0x58.

## Alias note

A previous devicetree issue came from hyphen versus underscore naming.

Devicetree alias style:

- fieldsense-i2c
- fieldsense-env-sensor

C macro usage style:

- DT_ALIAS(fieldsense_i2c)
- DT_ALIAS(fieldsense_env_sensor)

The hyphen in devicetree becomes an underscore in C macro usage.

## Lessons learned

Devicetree must match both hardware and driver expectations. A build can compile but still fail at link time if the device is not enabled by Kconfig or devicetree. FieldSense-Z solved this by enabling the I2C and sensor driver configuration and by verifying the overlay was actually used during the build.
