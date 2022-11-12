#include <zephyr.h>

class LED
{
private:
    struct gpio_dt_spec led; 
	bool led_is_on = true;
public:
    LED();

    void On();
    void Off();
    void Toggle();
};