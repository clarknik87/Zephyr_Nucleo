#include <zephyr.h>
#include <device.h>
#include <drivers/gpio.h>
#include <sys/printk.h>

#define SLEEP_TIME_MS 750

// Defines for the LED GPIO
#define LED0_NODE DT_ALIAS(led0)

#if DT_NODE_HAS_STATUS(LED0_NODE, okay)
#define LED0	DT_GPIO_LABEL(LED0_NODE, gpios)
#define PIN	DT_GPIO_PIN(LED0_NODE, gpios)
#define FLAGS	DT_GPIO_FLAGS(LED0_NODE, gpios)
#else
#error "Unsupported board: led0 devicetree alias is not defined"
#define LED0	""
#define PIN	    0
#define FLAGS	0
#endif

// Defines for the user button
#define BUTTON0_NODE DT_ALIAS(sw0)

#if DT_NODE_HAS_STATUS(BUTTON0_NODE, okay)
#define BUTTON0	        DT_GPIO_LABEL(BUTTON0_NODE, gpios)
#define BUTTON0_PIN	    DT_GPIO_PIN(BUTTON0_NODE, gpios)
#define BUTTON0_FLAGS	DT_GPIO_FLAGS(BUTTON0_NODE, gpios)
#else
#error "Unsupported board: sw0 devicetree alias is not defined"
#define BUTTON0	        ""
#define BUTTON0_PIN     0
#define BUTTON_FLAGS    0
#endif


void main(void)
{
    int ret;

    //Set up LED
    const struct device *dev;
	bool led_is_on = true;

	dev = device_get_binding(LED0);
	if (dev == NULL) 
    {
		return;
	}

	ret = gpio_pin_configure(dev, PIN, GPIO_OUTPUT_ACTIVE | FLAGS);
	if (ret < 0) {
		return;
	}

    //Set up Button
    const struct device *button;
    bool button_is_pressed;

    button = device_get_binding(BUTTON0);
    if (button ==  NULL)
    {
        return;
    }

    ret = gpio_pin_configure(button, BUTTON0_PIN, GPIO_INPUT | BUTTON0_FLAGS);
    if (ret < 0)
    {
        return;
    }

	while (1) {
		gpio_pin_set(dev, PIN, (int)led_is_on);
		led_is_on = !led_is_on;
        button_is_pressed = gpio_pin_get(button, BUTTON0_PIN);
        if(button_is_pressed)
        {
            printk("pressed\n");
        }
        else
        {
            printk("released\n");
        }
		k_msleep(SLEEP_TIME_MS);
	}
}
