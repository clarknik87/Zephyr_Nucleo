/**
 * @file Gyro.hpp
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

// C++ std/stl Includes
#include <cstdint>

// Project Includes


class Gyro
{
private:
    const device*   gyro;
    uint32_t        i2c_cfg;
    uint8_t         address;

    uint8_t         ReadRegister(uint8_t reg_addr);
    void            ReadRegisters(uint8_t reg_addr, uint8_t *read_data, int num_reg);
    void            WriteRegister(uint8_t reg_addr, uint8_t reg_val);
    void            InitRegisters();

public:
    Gyro() = delete;
    Gyro(const char* dev_name, uint8_t addr);

    void ReadAccelerometer(int16_t &x, int16_t &y, int16_t &z);
};