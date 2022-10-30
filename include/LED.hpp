#include <zephyr.h>

class LED
{
private:
    const struct device *dev;
    gpio_pin_t pin;
	bool led_is_on = true;
public:
    LED();

    void On();
    void Off();
    void Toggle();
};