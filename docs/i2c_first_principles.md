\# FieldSense-Z I2C First Principles



\## Why I studied I2C before using the sensor driver



Before using a BME280 or BMP280 driver, I wanted to understand what the ESP32 and HW-611 sensor were doing electrically and at the protocol level.



For FieldSense-Z, the ESP32 acts as the I2C controller. The HW-611 sensor acts as an I2C target.



The controller starts the transaction, controls the clock, sends the 7-bit address, and checks whether a target responds.



\## SDA and SCL



I2C uses two shared lines:



\- SDA: serial data

\- SCL: serial clock



SDA carries the data bits.



SCL provides the timing for when those bits are sampled.



For my ESP32 wiring checkpoint, I used:



\- SDA = GPIO21

\- SCL = GPIO22



\## Open-drain signaling



I2C uses open-drain style signaling.



That means a device does not normally force the line high. Instead:



\- A device can pull the line low.

\- A device can release the line.

\- A pull-up resistor brings the line high when nobody is pulling it low.



So the idle state of the bus is high.



This is why SDA and SCL normally sit high when the bus is not active.



\## Pull-up resistors



Pull-up resistors are required because open-drain devices only pull the line low or release it.



If there is no pull-up, the line may not return high correctly. That can cause no ACKs, timeouts, unstable communication, or a bus that appears stuck.



For my ESP32 system, the pullups must go to 3.3 V, not 5 V.



\## Common ground



Common ground is required because both devices need the same voltage reference.



If the ESP32 and sensor do not share GND, then the ESP32's idea of high and low may not match the sensor's idea of high and low.



For FieldSense-Z, ESP32 GND must connect to HW-611 GND.



\## 7-bit I2C addresses



I2C targets respond to addresses.



For this HW-611 sensor module, I did not assume the address. I checked the two expected possibilities:



\- `0x76`

\- `0x77`



The scan showed an ACK at `0x76` and no ACK at `0x77`.



That means an I2C target responded at `0x76`.



It does not yet prove the exact sensor model.



\## START, STOP, ACK, and NACK



A START condition begins an I2C transaction.



A STOP condition ends an I2C transaction.



An ACK means the target pulled SDA low during the acknowledge bit. In this checkpoint, an ACK at `0x76` meant that a device responded at that address.



A NACK means the target did not acknowledge. In this checkpoint, `0x77` did not respond.



\## Why bus validation comes before driver validation



I separated bus validation from driver validation.



The I2C scan only proves that the ESP32 can reach a target at a specific address.



The sensor driver will later prove whether the device behaves like the expected sensor and whether measurements can be read correctly.



This separation keeps debugging clean:



1\. First prove power, ground, pins, pullups, and address response.

2\. Then prove sensor identity.

3\. Then prove measurement reads.

4\. Then build the full RTOS data pipeline.



\## Connection to PulseGuard



This connects to the open-drain and signal-state thinking I used in PulseGuard.



In an open-drain bus, high does not mean a device is actively driving high. High means the devices have released the line and the pull-up resistor brought it high.



Low means at least one device is pulling the line down.



That same mindset helps with fault diagnosis: before blaming software, I need to check who is responsible for driving, releasing, or pulling a signal.

