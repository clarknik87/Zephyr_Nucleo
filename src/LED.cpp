#include <zephyr.h>
#include <device.h>
#include <drivers/gpio.h>
#include <LED.hpp>

// Defines for the LED GPIO
#define LED0_NODE   DT_ALIAS(led0)
#define LED0	    DT_GPIO_LABEL(LED0_NODE, gpios)


LED::LED()
{
    pin = DT_GPIO_PIN(LED0_NODE, gpios);
    dev = device_get_binding(LED0);
	if (dev == nullptr) 
    {
		return;
	}

	gpio_pin_configure(dev, pin, GPIO_OUTPUT_ACTIVE | DT_GPIO_FLAGS(LED0_NODE, gpios));
}

void LED::On()
{
    led_is_on = true;
    gpio_pin_set(dev, pin, (int)led_is_on);
}

void LED::Off()
{
    led_is_on = false;
    gpio_pin_set(dev, pin, (int)led_is_on);
}

void LED::Toggle()
{
    led_is_on = !led_is_on;
    gpio_pin_set(dev, pin, (int)led_is_on);
}