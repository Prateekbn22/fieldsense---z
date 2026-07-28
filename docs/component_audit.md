\# FieldSense-Z Component Audit



\## Hardware I already have



\- ESP32 development board: TBD

\- ESP32 module marking: TBD

\- USB connector type: TBD

\- BME280 or BMP280-style sensor breakout: TBD

\- Jumper wires: TBD

\- USB cable: TBD



\## Hardware I still need



\- Known-good USB data cable, not charge-only

\- Breadboard or stable wiring setup

\- Short jumper wires for 3.3 V, GND, SDA, and SCL

\- Optional: multimeter for checking 3.3 V and continuity

\- Optional: labels or tape for documenting wiring during photos



\## Items I need to verify



\### ESP32 board



\- Exact PCB text

\- Exact module text

\- USB connector type

\- Zephyr board target support

\- Flashing method

\- Serial console port

\- Whether boot/reset buttons are needed during flashing



\### Sensor breakout



\- Whether the board is truly BME280 or only BMP280

\- Pin labels printed on the breakout

\- Whether the breakout supports 3.3 V directly

\- Whether the board includes voltage regulation or level shifting

\- I2C address option

\- Whether CS/CSB must be tied high for I2C mode, depending on the breakout design



\## Safe 3.3 V rules



\- Treat the ESP32 and sensor interface as a 3.3 V system unless the exact hardware documentation proves otherwise.

\- Do not connect an ESP32 GPIO pin directly to 5 V.

\- Use 3.3 V for I2C pull-ups unless the breakout documentation clearly states that level shifting is present.

\- Connect all modules to a common GND.

\- Do not power the sensor from 5 V unless the breakout specifically supports it.

\- Do not assume that a pin labeled VIN is always safe for every voltage.

\- Before powering the sensor, verify the board markings and pin labels.



\## How to distinguish BME280 from BMP280



A BME280 measures:



\- temperature

\- pressure

\- humidity



A BMP280 measures:



\- temperature

\- pressure



The easiest practical difference is humidity support. If the chip or breakout is actually BMP280, humidity readings will not be available.



Things to check:



\- Product listing or invoice

\- Text printed on the breakout

\- Any marking on the sensor chip, if readable

\- Number and names of pins

\- Whether the seller specifically says BME280, not BMP280

\- Whether humidity is listed as a supported measurement



I will not assume the breakout is BME280 until the markings or product details support that.



\## Photographs to save for documentation



Save these photos in:



results/photos/



Recommended filenames:



\- esp32\_front.jpg

\- esp32\_back.jpg

\- esp32\_module\_marking.jpg

\- esp32\_usb\_connector.jpg

\- sensor\_front.jpg

\- sensor\_back.jpg

\- sensor\_pin\_labels.jpg

\- first\_i2c\_wiring.jpg



\## Current unknowns



\- ESP32 PCB text: TBD

\- ESP32 module text: TBD

\- USB connector type: TBD

\- Sensor breakout markings: TBD

\- Sensor pin labels: TBD

\- Operating system: TBD

\- Git workflow: TBD

