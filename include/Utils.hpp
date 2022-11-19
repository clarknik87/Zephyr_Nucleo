#ifndef UTILS_HPP
#define UTILS_HPP

#include <drivers/gpio.h>
#include <functional>

/******************************************************************************
 * 
 * Helper Macros
 * 
******************************************************************************/

#define GPIO_GET_SPEC(dev_id) GPIO_DT_SPEC_GET_OR(DT_ALIAS(dev_id), gpios, {0})

/******************************************************************************
 * 
 * Helper Functions
 * 
******************************************************************************/

namespace utils
{

    struct gpio_callback_wrapper
    {
        gpio_callback cb_data;
        std::function<void(const device*,gpio_callback *cb, uint32_t)> m_cb;
    };

    void callback(const device *dev, gpio_callback *cb, uint32_t pins); 
}

#endif //UTILS_HPP