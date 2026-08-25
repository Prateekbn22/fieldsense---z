#include <stdint.h>

#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>

#include "sensor_service.h"

static int32_t abs_i32(int32_t value)
{
	return value < 0 ? -value : value;
}

static void print_milli_value(const char *label, int32_t milli_value,
			      const char *unit)
{
	int32_t whole;
	int32_t frac;

	if (milli_value < 0) {
		int32_t abs_value = abs_i32(milli_value);

		whole = abs_value / 1000;
		frac = abs_value % 1000;

		printk("%s: -%d.%03d %s\n", label, whole, frac, unit);
		return;
	}

	whole = milli_value / 1000;
	frac = milli_value % 1000;

	printk("%s: %d.%03d %s\n", label, whole, frac, unit);
}

static void print_pressure_pa(int32_t pressure_pa)
{
	int32_t kpa_whole = pressure_pa / 1000;
	int32_t kpa_frac = pressure_pa % 1000;

	printk("Pressure: %d.%03d kPa (%d Pa)\n",
	       kpa_whole, kpa_frac, pressure_pa);
}

static void print_sample(const struct sensor_sample *sample)
{
	printk("\nSample %u at %u ms\n",
	       sample->sequence,
	       sample->timestamp_ms);

	print_milli_value("Temperature",
			  sample->temperature_milli_celsius,
			  "deg C");

	print_pressure_pa(sample->pressure_pa);

	if (sample->humidity_supported) {
		print_milli_value("Humidity",
				  sample->humidity_milli_percent_rh,
				  "%RH");
	}
}

int main(void)
{
	struct sensor_sample sample;
	bool humidity_note_printed = false;
	int ret;

	printk("FieldSense-Z environmental sensor service start\n");
	printk("Board target: doit_esp32_devkit_v1/esp32/procpu\n");

	ret = sensor_service_init();
	if (ret != 0) {
		printk("ERROR: sensor_service_init() failed, ret=%d\n", ret);
		return 0;
	}

	printk("Sensor device is ready: %s\n", sensor_service_device_name());
	printk("Sampling every two seconds using sensor_service_read()\n");

	while (1) {
		ret = sensor_service_read(&sample);
		if (ret != 0 || !sample.valid) {
			printk("ERROR: sample read failed, status=%s, driver_error=%d, ret=%d\n",
			       sensor_sample_status_to_string(sample.status),
			       sample.driver_error,
			       ret);

			k_sleep(K_SECONDS(2));
			continue;
		}

		print_sample(&sample);

		if (!sample.humidity_supported && !humidity_note_printed) {
			printk("Humidity: not supported by current BMP280 hardware\n");
			humidity_note_printed = true;
		}

		k_sleep(K_SECONDS(2));
	}

	return 0;
}