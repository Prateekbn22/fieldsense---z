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

## BME280 I2C Wiring Plan

### Hardware used for this wiring checkpoint

- ESP32 board marking: ESP32 DEVKIT V1
- ESP32 module marking: ESP-WROOM-32
- USB connector type: Micro-USB
- Sensor breakout marking: GY-BME280 or unknown
- Sensor pin labels visible: VCC, GND, SCL, SDA, CSB, SDO
- Operating system: Windows 11
- Verified Zephyr board target: `doit_esp32_devkit_v1/esp32/procpu`

### Wiring goal

Connect the ESP32 to the BME280-style breakout over I2C safely.

This checkpoint is only for wiring planning and documentation. Sensor application code is not added yet.

### Safe voltage rule

The ESP32 GPIO pins are treated as 3.3 V logic. The sensor will be powered from 3.3 V unless the exact breakout documentation proves that the VCC/VIN pin supports 5 V safely.

I will not connect any ESP32 GPIO pin to a 5 V signal.

### Common ground rule

ESP32 GND and sensor GND must be connected together. Without common ground, SDA and SCL signals do not have a shared voltage reference and I2C communication may fail or behave unpredictably.

### I2C signal plan

| Sensor pin | Connection plan | Status |
|---|---|---|
| VCC | Connect to ESP32 3.3 V only after verifying the sensor VCC/VIN meaning | TBD |
| GND | Connect to ESP32 GND | TBD |
| SDA | Connect to the ESP32 SDA GPIO chosen from board documentation or Zephyr devicetree plan | TBD |
| SCL | Connect to the ESP32 SCL GPIO chosen from board documentation or Zephyr devicetree plan | TBD |
| CSB | Do not assume. Research whether it must be tied high for I2C mode on this breakout | TBD |
| SDO | Do not assume. Research whether it controls the I2C address, usually 0x76 or 0x77 depending on wiring | TBD |

### Pullup check

I2C needs pullup resistors on SDA and SCL. Many BME280 breakout boards already include pullups, but I will verify this from the breakout documentation or board inspection before adding external pullups.

If pullups are used, they must pull up to 3.3 V, not 5 V.

### BME280 vs BMP280 check

The breakout marking is currently `GY-BME280 or unknown`, so I will not assume it is definitely a BME280.

A BME280 measures temperature, pressure, and humidity.

A BMP280 measures temperature and pressure only.

The practical check later will be whether the sensor reports humidity support and whether the detected chip ID matches the expected sensor.

### Sensor address plan

The sensor I2C address is not assumed yet.

Expected address will be documented after checking the breakout documentation and SDO wiring.

Possible addresses to investigate later:

- `0x76`
- `0x77`

### Pre-power checklist

- [ ] ESP32 3.3 V pin identified
- [ ] ESP32 GND pin identified
- [ ] Sensor VCC/VIN meaning verified
- [ ] SDA GPIO chosen from board documentation or Zephyr devicetree plan
- [ ] SCL GPIO chosen from board documentation or Zephyr devicetree plan
- [ ] CSB behavior checked for I2C mode
- [ ] SDO behavior checked for address selection
- [ ] Pullups checked or documented
- [ ] Expected sensor address documented
- [ ] Wiring photo saved as `results/photos/first_i2c_wiring.jpg`
- [ ] No power applied until the wiring photo is reviewed

### Wiring photo rule

Before powering the circuit, I will take a clear photo showing ESP32 3.3 V, GND, SDA, SCL, and the sensor pins.

The photo is required because it gives visual evidence of the wiring and helps catch reversed power, missing ground, swapped SDA/SCL, or accidental connection to the wrong voltage pin before powering the board.

## Bosch Sensor Identity Check

The HW-611 breakout was originally treated as a BME280-style module, but I did not trust the breakout-board label or seller description alone.

I verified the actual silicon by reading Bosch identification register `0xD0` over I2C.

Result:

- I2C address responding: `0x76`
- Register read: `0xD0`
- Chip ID returned: `0x58`
- Identified device: BMP280

Interpretation:

The module contains a BMP280, not a BME280.

Available measurements with this hardware:

- Temperature
- Pressure

Not available with this hardware:

- Humidity

Project scope adjustment:

FieldSense-Z will continue temporarily as an ESP32 + BMP280 temperature/pressure monitoring node. Humidity features will not be implemented unless I replace the module with a verified BME280.
