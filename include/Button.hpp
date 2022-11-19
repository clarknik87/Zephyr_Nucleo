/**
 * @file Button.hpp
 * @author Nik Clark (clarknik87@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-11-19
 * 
 * @copyright Copyright (c) 2022
 * 
 */

// Zephyr Includes
#include <zephyr.h>

// C++ std/stl Includes
#include <list>

// Project Includes
#include <Utils.hpp>

/**
 * @brief The Button class models a simple push button or switch attached to a
 * single GPIO pin. The class automatically configures an internal interrupt on
 * both rising and falling edges. The button class implemenets public member
 * function to enable reading the status of the button or adding additional
 * callbacks.
 * 
 */
class Button
{
private:
    bool    pressed{false};
    struct  gpio_dt_spec button;
    struct  utils::gpio_callback_wrapper button_cb_data;

    std::list<std::function<void(bool)>> external_cb_list;

    void button_callback(const device *dev, gpio_callback *cb, uint32_t pins);
public:
    /**
     * @brief Button objects must be associated with a device tree spec upon
     * construction. The default constructor is therefore explicitly removed.     * 
     */
    Button()= delete;

    /**
     * @brief Construct a new Button object.
     * 
     * @param dev a device tree specification as returned from 
     * GPIO_GET_SPEC(dev_id) contained in Utils.hpp
     */
    Button(gpio_dt_spec dev);

    /**
     * @brief Returns the current state of the associated button or switch.
     * 
     * @return true, the button is pressed
     * @return false, the button is released 
     */
    bool Pressed();

    /**
     * @brief Add an additional callback funtion to be called in the interrupt
     * context upon a rising or falling edge of the associated button/switch.
     * Callback functions are called in the order they are added.
     * 
     * @param p_cb a function pointer to the callback to be added. Callbacks
     * must match the signature:
     * 
     * void external_callback(bool is_pressed)
     * 
     * the parameter of the function callback is the current button state.
     * true = pressed, false = released.
     */
    void AddCallback(std::function<void(bool)> &p_cb);
};