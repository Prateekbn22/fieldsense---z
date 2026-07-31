#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>

int main(void)
{
	printk("FieldSense-Z board bring-up start\n");
	printk("Checkpoint: ESP32 boot and serial console only\n");
	printk("BME280 sensor is not connected for this test\n");

	while (1) {
		printk("FieldSense-Z alive, uptime_ms=%lld\n", k_uptime_get());
		k_sleep(K_SECONDS(5));
	}

	return 0;
}