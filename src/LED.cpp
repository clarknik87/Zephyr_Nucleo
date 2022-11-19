#include <zephyr.h>
#include <device.h>
#include <drivers/gpio.h>
#include <LED.hpp>


LED::LED(gpio_dt_spec dev) : led{dev}
{
    gpio_pin_configure_dt(&led, GPIO_OUTPUT);
}

void LED::On()
{
    led_is_on = true;
    gpio_pin_set_dt(&led, (int)led_is_on);
}

void LED::Off()
{
    led_is_on = false;
    gpio_pin_set_dt(&led, (int)led_is_on);
}

void LED::Toggle()
{
    led_is_on = !led_is_on;
    gpio_pin_toggle_dt(&led);
}