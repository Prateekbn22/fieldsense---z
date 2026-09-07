# I2C First Principles

I2C is a two-wire shared bus. The two signal lines are:

- SDA for data
- SCL for clock

Both lines require pull-up behavior because devices pull the lines low rather than actively driving them high.

## Why address scanning matters

Before using a sensor driver, the bus must prove that a device responds at the expected address. FieldSense-Z validated this by checking common sensor addresses.

Actual result:

| Address | Result |
|---|---|
| 0x76 | ACK received |
| 0x77 | No ACK |

That proved the sensor responded at 0x76.

## Why chip ID matters

An I2C ACK only proves that something responded. It does not prove which sensor is installed.

The Bosch chip ID register is 0xD0. The actual read returned:

| Register | Value |
|---|---|
| 0xD0 | 0x58 |

The value 0x58 identifies BMP280 behavior. Because of that, FieldSense-Z treats humidity as unsupported.

## What this proved

The I2C validation proved:

- the ESP32 I2C pins were usable
- the sensor was powered
- SDA and SCL were connected correctly
- the module responded at 0x76
- the sensor was BMP280-compatible
- temperature and pressure were the valid measurement channels
