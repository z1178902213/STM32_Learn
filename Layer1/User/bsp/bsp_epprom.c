#include "bsp_epprom.h"

void init_epprom()
{
	init_i2c(1);
}

void epprom_write_byte_test(){
	i2c_set_reg(I2C1, 0xA0, 0x02, 0xff);
}

void epprom_read_byte_test(){
	uint8_t data = 0x3f;
	
	printf("[INFO] 读取数据前，data值：0x%02X. \n", data);
	
	i2c_read_reg(I2C1, 0xA0, 0x02, &data);
	
	printf("[INFO] 读取EPPROM数据后，data值：0x%02X. \n", data);
}

