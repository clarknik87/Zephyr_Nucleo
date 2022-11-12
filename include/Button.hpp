#include <zephyr.h>
#include <Utils.hpp>

class Button
{
private:
    bool    pressed{false};
    struct  gpio_dt_spec button;
    struct  utils::gpio_callback_wrapper button_cb_data;

    void button_callback(const device *dev, gpio_callback *cb, uint32_t pins);
public:
    Button();

    bool Pressed();
};