\# FieldSense-Z Wiring Notes



\## I2C bus validation wiring



For the first I2C bus validation checkpoint, I connected the ESP32 DEVKIT V1 to the HW-611 sensor module using I2C.



The verified Zephyr board target was:



`doit\_esp32\_devkit\_v1/esp32/procpu`



The proposed I2C pins were:



\- SDA: GPIO21

\- SCL: GPIO22



The wiring plan was:



| ESP32 | HW-611 sensor |

|---|---|

| 3.3 V | VCC |

| GND | GND |

| GPIO21 | SDA |

| GPIO22 | SCL |



I treated the system as a 3.3 V system. I did not use 5 V for the I2C pullups or sensor interface.



\## Why I took a bus-first approach



Before using a BME280 or BMP280 sensor driver, I first verified that the ESP32 could communicate electrically and at the I2C protocol level with the sensor module.



This matters because driver-level debugging is much harder if the lower-level bus is not already trusted. If the sensor driver failed before this test, I would not know whether the problem was wiring, power, ground, SDA/SCL pins, pullups, address selection, or driver configuration.



\## I2C scan result



The I2C scan showed:



\- `0x76`: ACK received

\- `0x77`: no ACK



This means one expected sensor address responded on the bus.



The result confirms that an I2C target responded at `0x76`, but it does not yet prove the exact sensor model. The module may still need to be verified as BMP280 or BME280 by reading its chip ID or using the correct Zephyr driver later.



\## Evidence



Actual serial output was saved to:



`results/logs/i2c\_scan.txt`

## Sensor identity result

After validating the I2C bus, I read Bosch register `0xD0` to identify the actual sensor silicon.

The sensor responded at I2C address `0x76`.

Register `0xD0` returned `0x58`, which identifies the device as BMP280.

This means the current HW-611 module supports temperature and pressure, but not humidity.

The I2C address and chip ID are different pieces of evidence:

- `0x76` is the I2C address where the device responds.
- `0x58` is the chip ID stored inside the Bosch sensor.

