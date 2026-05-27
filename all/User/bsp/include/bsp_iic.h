#ifndef _BSP_IIC_H_
#define _BSP_IIC_H_

#include "stm32f4xx.h"

void init_iic(void);
void write_data_eeprom(void);
void check_data_eeprom(void);

#endif

