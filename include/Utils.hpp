#ifndef UTILS_HPP
#define UTILS_HPP

#include <drivers/gpio.h>
#include <functional>

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