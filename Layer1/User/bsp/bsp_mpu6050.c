#include "bsp_mpu6050.h"

int16_t mpu6050_get_temp(void){
	uint8_t temp_h = 0;
	uint8_t temp_l = 0;
	i2c_read_reg(MPU6050_I2C, MPU6050_ADDRESS, 0x41, &temp_h);
	i2c_read_reg(MPU6050_I2C, MPU6050_ADDRESS, 0x42, &temp_l);
	int16_t temp = (int16_t)((temp_h << 8) | temp_l);
	return temp;
}

void init_mpu6050(void){
	init_i2c(1);
	delay(100);
	i2c_set_reg(MPU6050_I2C, MPU6050_ADDRESS, 0x6B, 0x00);
	printf("[INFO] 初始化完成. \n");
}

