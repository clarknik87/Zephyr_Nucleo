#include <zephyr.h>
#include <device.h>
#include <drivers/gpio.h>
#include <Utils.hpp>
#include <Button.hpp>


Button::Button(gpio_dt_spec dev) : button{dev}
{
    //GPIO init
    gpio_pin_configure_dt(&button, GPIO_INPUT);

    //Interrupt init
    while(!device_is_ready(button.port))
    {
        k_msleep(1);
    }

    button_cb_data.m_cb = [this](const device *dev, gpio_callback *cb, uint32_t pins){ this->button_callback(dev,cb,pins); };
    
    gpio_pin_interrupt_configure_dt(&button, GPIO_INT_EDGE_BOTH);
    gpio_init_callback(&button_cb_data.cb_data, utils::callback, BIT(button.pin));
    gpio_add_callback(button.port, &button_cb_data.cb_data);
}

bool Button::Pressed()
{
    return pressed;
}

void Button::button_callback(const device *dev, gpio_callback *cb, uint32_t pins)
{
    if( pins == BIT(button.pin) )
    {
        auto key = irq_lock();
        pressed = gpio_pin_get_dt(&button);
        irq_unlock(key);
        
        for(auto e : external_cb_list)
        {
            e(pressed);
        }
    }
}

void Button::AddCallback(std::function<void(bool)> &p_cb)
{
    external_cb_list.push_back(p_cb);
}