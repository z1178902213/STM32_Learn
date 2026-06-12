#ifndef _BSP_MPU6050_H_
#define _BSP_MPU6050_H_

#include "stm32f4xx.h"
#include "bsp_iic.h"
#include "bsp_usart.h"
#include "common.h"

#define MPU6050_I2C I2C1
#define MPU6050_ADDRESS 0xD0

int16_t mpu6050_get_temp(void);
void init_mpu6050(void);

#endif

