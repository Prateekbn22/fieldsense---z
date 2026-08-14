#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/i2c.h>
#include <zephyr/sys/printk.h>

#define FIELDSENSE_I2C_NODE DT_ALIAS(fieldsense_i2c)

#define SENSOR_ADDR_76 0x76
#define SENSOR_ADDR_77 0x77

#define BOSCH_CHIP_ID_REG 0xD0
#define BME280_CHIP_ID    0x60
#define BMP280_CHIP_ID    0x58

static void identify_sensor_at_address(const struct device *i2c_dev, uint8_t addr)
{
	uint8_t chip_id = 0;
	int ret;

	ret = i2c_reg_read_byte(i2c_dev, addr, BOSCH_CHIP_ID_REG, &chip_id);

	if (ret != 0) {
		printk("Address 0x%02x: chip ID read failed, ret=%d\n", addr, ret);
		return;
	}

	printk("Address 0x%02x: register 0x%02x returned chip_id=0x%02x\n",
	       addr, BOSCH_CHIP_ID_REG, chip_id);

	if (chip_id == BME280_CHIP_ID) {
		printk("Sensor identity: BME280 detected at address 0x%02x\n", addr);
		printk("Available measurements: temperature, pressure, humidity\n");
	} else if (chip_id == BMP280_CHIP_ID) {
		printk("Sensor identity: BMP280 detected at address 0x%02x\n", addr);
		printk("Available measurements: temperature and pressure only\n");
		printk("Humidity is not available with this hardware\n");
	} else {
		printk("Sensor identity: unknown Bosch-compatible ID 0x%02x at address 0x%02x\n",
		       chip_id, addr);
	}
}

int main(void)
{
	const struct device *i2c_dev = DEVICE_DT_GET(FIELDSENSE_I2C_NODE);

	printk("FieldSense-Z Bosch sensor identification start\n");
	printk("Board target: doit_esp32_devkit_v1/esp32/procpu\n");
	printk("Configured I2C pins: SDA=GPIO21, SCL=GPIO22\n");
	printk("Reading Bosch chip ID register 0x%02x\n", BOSCH_CHIP_ID_REG);
	printk("Expected IDs: BME280=0x%02x, BMP280=0x%02x\n",
	       BME280_CHIP_ID, BMP280_CHIP_ID);

	if (!device_is_ready(i2c_dev)) {
		printk("ERROR: I2C device is not ready\n");
		return 0;
	}

	printk("I2C device is ready\n");

	identify_sensor_at_address(i2c_dev, SENSOR_ADDR_76);
	identify_sensor_at_address(i2c_dev, SENSOR_ADDR_77);

	printk("Sensor identification checkpoint complete\n");

	while (1) {
		k_sleep(K_SECONDS(10));
	}

	return 0;
}