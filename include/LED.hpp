/**
 * @file LED.hpp
 * @author Nik Clark (clarknik87@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-11-19
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <zephyr.h>

/**
 * @brief The LED class models a very simple LED attached to a single GPIO pin.
 * The associated GPIO pin is supplied to the class upon construction. This
 * configures the pin and provides public member functions for controlling the
 * LED behavior.
 * 
 */
class LED
{
private:
    struct gpio_dt_spec led; 
	bool led_is_on = true;
public:
    /**
     * @brief LED objects must be associated with a device tree spec upon
     * construction. The default constructor is therefore explicitly removed.     * 
     */
    LED() = delete;

    /**
     * @brief Construct a new LED object.
     * 
     * @param dev a device tree specification as returned from 
     * GPIO_GET_SPEC(dev_id) contained in Utils.hpp
     */
    LED(gpio_dt_spec dev);

    /**
     * @brief Turn on the LED.
     * 
     */
    void On();

    /**
     * @brief Turn off the LED.
     * 
     */
    void Off();

    /**
     * @brief toggle the LED.
     * 
     */
    void Toggle();
};