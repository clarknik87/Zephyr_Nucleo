#include <zephyr.h>
#include <device.h>
#include <drivers/gpio.h>
#include <sys/printk.h>

#include <Utils.hpp>

#include <LED.hpp>
#include <Button.hpp>

#define SLEEP_TIME_MS 500

void main(void)
{
	LED l1(GPIO_GET_SPEC(led0));
	Button b1(GPIO_GET_SPEC(sw0));

	while (1) {
		l1.Toggle();
		k_msleep(SLEEP_TIME_MS);
	}
}
