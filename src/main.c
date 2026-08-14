#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/i2c.h>
#include <zephyr/sys/printk.h>

#define FIELDSENSE_I2C_NODE DT_ALIAS(fieldsense_i2c)

#define SENSOR_ADDR_76 0x76
#define SENSOR_ADDR_77 0x77

static int probe_i2c_address(const struct device *i2c_dev, uint8_t addr)
{
	struct i2c_msg msg = {
		.buf = NULL,
		.len = 0,
		.flags = I2C_MSG_WRITE | I2C_MSG_STOP,
	};

	return i2c_transfer(i2c_dev, &msg, 1, addr);
}

int main(void)
{
	const struct device *i2c_dev = DEVICE_DT_GET(FIELDSENSE_I2C_NODE);
	int ret_76;
	int ret_77;
	int found_count = 0;

	printk("FieldSense-Z I2C bus validation start\n");
	printk("Board target: doit_esp32_devkit_v1/esp32/procpu\n");
	printk("Configured I2C pins: SDA=GPIO21, SCL=GPIO22\n");
	printk("Checking expected sensor addresses: 0x76 and 0x77\n");

	if (!device_is_ready(i2c_dev)) {
		printk("ERROR: I2C device is not ready\n");
		return 0;
	}

	printk("I2C device is ready\n");

	ret_76 = probe_i2c_address(i2c_dev, SENSOR_ADDR_76);
	if (ret_76 == 0) {
		printk("ACK received at address 0x76\n");
		found_count++;
	} else {
		printk("No ACK at address 0x76, ret=%d\n", ret_76);
	}

	ret_77 = probe_i2c_address(i2c_dev, SENSOR_ADDR_77);
	if (ret_77 == 0) {
		printk("ACK received at address 0x77\n");
		found_count++;
	} else {
		printk("No ACK at address 0x77, ret=%d\n", ret_77);
	}

	if (found_count == 1) {
		printk("I2C scan result: PASS, one expected address responded\n");
	} else if (found_count == 0) {
		printk("I2C scan result: FAIL, no expected sensor address responded\n");
	} else {
		printk("I2C scan result: WARNING, both expected addresses responded\n");
	}

	printk("I2C bus validation checkpoint complete\n");

	while (1) {
		k_sleep(K_SECONDS(10));
	}

	return 0;
}