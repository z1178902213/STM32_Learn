#ifndef _BSP_IIC_H_
#define _BSP_IIC_H_
#include "stm32f4xx.h"
#include "bsp_usart.h"

void init_i2c(uint8_t i2c_num);
void i2c_read_reg(I2C_TypeDef* I2Cx, uint8_t slave_address, uint8_t target_reg, uint8_t* receive_data);
void i2c_set_reg(I2C_TypeDef* I2Cx, uint8_t slave_address, uint8_t target_reg, uint8_t target_data);
void write_data_eeprom(void);
void check_data_eeprom(void);

#endif

