/**
 * @file Gyro.cpp
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
#include <drivers/i2c.h>
#include <devicetree.h>

// C++ std/stl Includes

// Project Includes
#include <Gyro.hpp>

#if DT_NODE_HAS_STATUS(DT_NODELABEL(i2c1), okay)
#define I2C_DEV_NAME DT_LABEL(DT_NODELABEL(i2c1))
#else
#error "Please set the correct I2C device"
#endif

Gyro::Gyro(const char* dev_name, uint8_t addr) : address{addr}
{
    gyro = device_get_binding(I2C_DEV_NAME);
    if (!gyro)
    {
        printk("failed to get I2C_1 device\n");
        return;
    }

    i2c_cfg = (I2C_SPEED_SET(I2C_SPEED_STANDARD) | I2C_MODE_MASTER);
    if (i2c_configure(gyro, i2c_cfg)) {
		printk("I2C config failed\n");
        return;
	}

    if(i2c_cfg != (I2C_SPEED_SET(I2C_SPEED_STANDARD) | I2C_MODE_MASTER))
    {
        printk("I2C config setting invalid %u", i2c_cfg);
        return;
    }
}

uint8_t Gyro::ReadRegister(uint8_t reg_addr)
{
    uint8_t reg_val;
    i2c_write(gyro, &reg_addr, 1, address );
    i2c_read(gyro, &reg_val, 1, address);
    return reg_val;
}

void Gyro::ReadAccelerometer(int16_t &x, int16_t &y, int16_t &z)
{
    uint8_t write_address;
    uint8_t hi_byte{0};
    uint8_t lo_byte{0};

    //Reads the "WHO_AM_I byte that returns 0x68"
    lo_byte = ReadRegister(0x75);

    x = (hi_byte<<8) | lo_byte;

    return;
}