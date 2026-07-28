# FieldSense-Z Component Audit

## 1. Hardware I already have

### ESP32 development board

- ESP32 PCB text: ESP32 DEVKIT V1
- ESP32 metal module text: ESP-WROOM-32
- USB connector type: Micro-USB
- Current status: physically available, exact Zephyr target not selected yet

### Environmental sensor breakout

- Sensor type claimed by seller or marking: GY-BME280 or unknown
- Confirmed as BME280: not confirmed yet
- Confirmed as BMP280: not confirmed yet
- Sensor board markings: GY-BME280 or unknown
- Sensor pin labels in printed order: VCC, GND, SCL, SDA, CSB, SDO
- Current status: physically available, not wired yet

### Supporting items

- USB cable: available, but not yet verified as a data cable
- Jumper wires: TBD
- Breadboard or stable wiring setup: TBD
- Multimeter: TBD
- Oscilloscope or logic analyzer: not required for first checkpoint, but useful for I2C debugging

### Development setup

- Operating system: Windows 11
- Git workflow: GitHub Desktop and terminal Git

## 2. Hardware I still need

- Known-good USB data cable, not charge-only
- Stable jumper wires
- Breadboard or another stable connection method
- Multimeter for checking 3.3 V and GND
- Optional: oscilloscope or logic analyzer for checking SDA and SCL activity
- Optional: labels or tape for documenting wiring during photos

## 3. Items I need to verify

### ESP32 board

- Exact board support or compatible target in Zephyr
- Flashing method
- Serial console port
- Whether BOOT or RESET buttons are needed during flashing
- Which pins are safe to use for I2C
- Which pin is 3.3 V
- Which pins are GND

### Sensor breakout

- Whether the board is truly BME280 or only BMP280
- Whether VCC should be connected to 3.3 V only or can accept a wider input range
- Whether the board includes voltage regulation
- Whether the board includes I2C pull-up resistors
- Whether the board includes level shifting
- Expected I2C address
- Whether SDO changes the I2C address
- Whether CSB must be tied high for I2C mode

## 4. Safe 3.3 V rules

- Treat the ESP32 and sensor interface as a 3.3 V system unless exact hardware documentation proves otherwise.
- Do not connect an ESP32 GPIO pin directly to 5 V.
- Use 3.3 V for I2C pull-ups unless the breakout documentation clearly says level shifting is present.
- Connect ESP32 GND and sensor GND together.
- GND is the common electrical reference shared by the ESP32 and the sensor.
- Do not power the sensor from 5 V unless the breakout specifically supports it.
- Do not assume that a pin labeled VCC or VIN is safe for every voltage.
- Before powering the sensor, verify the board markings and pin labels.
- Take a wiring photo before applying power.

## 5. How to distinguish BME280 from BMP280

A BME280 measures:

- temperature
- pressure
- humidity

A BMP280 measures:

- temperature
- pressure

The easiest practical difference is humidity support. If the breakout is actually BMP280, humidity readings will not be available.

Things to check:

- Product listing or invoice
- Text printed on the breakout
- Marking on the sensor chip, if readable
- Number and names of pins
- Whether the seller specifically says BME280, not BMP280
- Whether humidity is listed as a supported measurement
- Whether the device responds with the expected chip ID later during software bring-up

I will not assume the breakout is BME280 until the markings, product details, or software evidence support that.

## 6. Photographs to save for documentation

Save these photos in:

```text
results/photos/