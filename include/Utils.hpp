#ifndef UTILS_HPP
#define UTILS_HPP

#include <drivers/gpio.h>
#include <functional>

/******************************************************************************
 * 
 * Helper Macros
 * 
******************************************************************************/

/**
 * @brief Return a device tree specification for an aliased member.
 * 
 * @param dev_id aliased name for device tree specification
 */
#define GPIO_GET_SPEC(dev_id) GPIO_DT_SPEC_GET_OR(DT_ALIAS(dev_id), gpios, {0})












/******************************************************************************
 * 
 * Helper Structures and Functions
 * 
******************************************************************************/

namespace utils
{

    /**
     * @brief callback wrapper to enable zephyr gpio callbacks to invoke class
     * member function. Intended to be used with zephyr's CONTAINER_OF() macro.
     * The cb_data member is to be passed to the gpio_init_callback() function
     * in "drivers/gpio.h" 
     * 
     * gpio_init_callback(gpio_callback_wrapper.cb_data, utils::callback, ... )
     * 
     * m_cb can be assigned to the desired callback function. The std::function
     * prototype allows for more flexibility than the original zephyr library.
     */
    struct gpio_callback_wrapper
    {
        gpio_callback cb_data;
        std::function<void(const device*, gpio_callback *cb, uint32_t)> m_cb;
    };

    /**
     * @brief helper function designed to be used with the gpio_callback_-
     * wrapper struct. This function assumes that the associated zephyr 
     * callback has been initialized with a gpio_callback_wrapper struct.
     * This helper function will then use CONTAINER_OF() to access and
     * invoke the m_cb of the original gpio_callback_wrapper struct. This
     * function should never be directly called.
     * 
     * @param dev helper variable passed through to gpio_wrapper_callback.m_cb
     * @param cb helper variable passed through to gpio_wrapper_callback.m_cb
     * @param pins helper variable passed through to gpio_wrapper_callback.m_cb
     */
    void callback(const device *dev, gpio_callback *cb, uint32_t pins); 
}

#endif //UTILS_HPP