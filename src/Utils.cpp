#include <Utils.hpp>

void utils::callback(const device *dev, gpio_callback *cb, uint32_t pins)
{
    struct utils::gpio_callback_wrapper *container = CONTAINER_OF(cb, struct utils::gpio_callback_wrapper, cb_data);
    if(container != nullptr)
    {
        container->m_cb(dev, cb, pins);
    }
}