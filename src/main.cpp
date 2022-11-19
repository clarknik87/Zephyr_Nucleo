/**
 * @file main.cpp
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
#include <device.h>
#include <drivers/gpio.h>
#include <sys/printk.h>

// C++ std/stl Includes
#include <functional>

// Project Includes
#include <Utils.hpp>
#include <LED.hpp>
#include <Button.hpp>


/**
 * @brief Instantiate objects and enter main executional loop
 */
void main(void)
{
	LED l1(GPIO_GET_SPEC(led0));
	Button b1(GPIO_GET_SPEC(sw0));

	std::function<void(bool)> b1_callback = [&l1](bool pressed){
		if(pressed)
		{
			l1.On();
			printk("pressed\n");
		}
		else
		{
			l1.Off();
			printk("released\n");
		}
	};

	b1.AddCallback(b1_callback);

	while (1) {
		;
	}
}
