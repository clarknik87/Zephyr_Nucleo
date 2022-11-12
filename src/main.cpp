#include <zephyr.h>
#include <device.h>
#include <drivers/gpio.h>
#include <sys/printk.h>

#include <LED.hpp>
#include <Button.hpp>

#define SLEEP_TIME_MS 750

static LED l1;
static Button b1;

void main(void)
{

	while (1) {
		l1.Toggle();
		k_msleep(SLEEP_TIME_MS);
	}
}
