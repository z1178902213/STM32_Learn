#ifndef _BSP_KEY_H
#define _BSP_KEY_H
#include "stm32f4xx.h"

#define IS_KEY_PRESS(_value_) (_value_ == Bit_SET)

void init_key(void);
uint8_t read_key1(void);
uint8_t read_key2(void);


#endif //_BSP_KEY_H

