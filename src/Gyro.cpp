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

    InitRegisters();
}

uint8_t Gyro::ReadRegister(uint8_t reg_addr)
{
    uint8_t reg_val;
    i2c_write_read(gyro, address, &reg_addr, 1, &reg_val, 1);
    return reg_val;
}

void Gyro::ReadRegisters(uint8_t reg_addr, uint8_t *read_data, int num_reg)
{
    i2c_write_read(gyro, address, &reg_addr, 1, read_data, num_reg);
}

void Gyro::WriteRegister(uint8_t reg_addr, uint8_t reg_val)
{
    uint8_t write_buf[2] = {reg_addr, reg_val};
    i2c_write(gyro, write_buf, 2, address);
}

void Gyro::InitRegisters()
{
    WriteRegister(0x6b, 0x00); //Power On
    WriteRegister(0x1c, 0x08); //Accel 4G
    WriteRegister(0x1a, 0x06); //Low pass filter bandwidth 5Hz
    return;
}

void Gyro::ReadAccelerometer(int16_t &x, int16_t &y, int16_t &z)
{
    uint8_t raw_data[6];

    ReadRegisters(0x3b, raw_data, 6);

    x = ((raw_data[0]<<8) | raw_data[1]);
    y = ((raw_data[2]<<8) | raw_data[3]);
    z = ((raw_data[4]<<8) | raw_data[5]);

    return;
}