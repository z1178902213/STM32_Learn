#include "bsp_iic.h"

uint8_t I2C1_INIT_FLAG = 0;
const uint32_t TIMEOUT = 0x00ffffff;

void init_i2c(uint8_t i2c_num){
	if(i2c_num == 1 && !I2C1_INIT_FLAG){
		// 开启GPIOB时钟和I2C1的时钟
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
		
		// 配置PB8和PB9的复用
		GPIO_PinAFConfig(GPIOB, GPIO_PinSource8, GPIO_AF_I2C1);
		GPIO_PinAFConfig(GPIOB, GPIO_PinSource9, GPIO_AF_I2C1);
		// 配置PB8和PB9初始化
		GPIO_InitTypeDef gpio_init_struct;
		gpio_init_struct.GPIO_Pin = GPIO_Pin_8;
		gpio_init_struct.GPIO_Mode = GPIO_Mode_AF;
		gpio_init_struct.GPIO_OType = GPIO_OType_OD;
		gpio_init_struct.GPIO_PuPd = GPIO_PuPd_NOPULL;
		gpio_init_struct.GPIO_Speed = GPIO_Speed_100MHz;
		GPIO_Init(GPIOB, &gpio_init_struct);
		gpio_init_struct.GPIO_Pin = GPIO_Pin_9;
		GPIO_Init(GPIOB, &gpio_init_struct);
		
		// 配置I2C1，本机地址默认0x00，速度配置成400k
		I2C_InitTypeDef i2c_init_struct;
		i2c_init_struct.I2C_OwnAddress1 = 0x0A;
		i2c_init_struct.I2C_Mode = I2C_Mode_I2C;
		i2c_init_struct.I2C_ClockSpeed = 400000;
		i2c_init_struct.I2C_DutyCycle = I2C_DutyCycle_2;
		i2c_init_struct.I2C_Ack = I2C_Ack_Enable;
		i2c_init_struct.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
		I2C_Init(I2C1, &i2c_init_struct);
		I2C_Cmd(I2C1, ENABLE);
		I2C_AcknowledgeConfig(I2C1, ENABLE);

		// 标记一下I2C1已经被初始化了，防止后面一直初始化
		I2C1_INIT_FLAG = 1;
	}
}

void i2c_read_reg(I2C_TypeDef* I2Cx, uint8_t slave_address, uint8_t target_reg, uint8_t* receive_data){
	uint32_t timer = TIMEOUT;
	
	while(I2C_GetFlagStatus(I2Cx, I2C_FLAG_BUSY)){
		if(timer-- == 0){
			printf("[ERROR] 等待I2C设备超时。\n");
			return;
		}
	}
	timer = TIMEOUT;
	
	// 生成起始信号
	I2C_GenerateSTART(I2Cx, ENABLE);
	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT)){
		if(timer-- == 0){
			printf("[ERROR] 生成起始信号超时。\n");
			return;
		}
	}
	timer = TIMEOUT;
	
	// 发送从机地址信号
	I2C_Send7bitAddress(I2Cx, slave_address, I2C_Direction_Transmitter);
	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)){
		if(timer-- == 0){
			printf("[ERROR] 与从机建立发送连接超时。\n");
			return;
		}
	}
	timer = TIMEOUT;
	
	// 发送发送访问的i2c设备的寄存器地址
	I2C_SendData(I2Cx, target_reg);
	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED)){
		if(timer-- == 0){
			printf("[ERROR] 发送寄存器超时。\n");
			return;
		}
	}
	timer = TIMEOUT;
	
	// 生成起始信号
	I2C_GenerateSTART(I2Cx, ENABLE);
	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT)){
		if(timer-- == 0){
			printf("[ERROR] 生成起始信号超时。\n");
			return;
		}
	}
	timer = TIMEOUT;
	
	// 发送从机地址信号
	I2C_Send7bitAddress(I2Cx, slave_address, I2C_Direction_Receiver);
	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED)){
		if(timer-- == 0){
			printf("[ERROR] 与从机建立接收连接超时。\n");
			return;
		}
	}
	timer = TIMEOUT;
	
	// 接收数据
	// ！！！重点！！！要等到RXNE还有RTF（这里没检测）标志位被标记以后才表示DR寄存器的值已经修改了！！！不然就会一直读到上一次的值！！
	while(!I2C_GetFlagStatus(I2C1, I2C_FLAG_RXNE));
	// NACK信号要在读取之前发出，这样会在发出ACK信号之前先发出NACK信号，从机才知道可以不用发数据了
	I2C_AcknowledgeConfig(I2Cx, DISABLE);
	*receive_data = I2C_ReceiveData(I2Cx);
	
	I2C_GenerateSTOP(I2Cx, ENABLE);
	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_RECEIVED)){
		if(timer-- == 0){
			printf("[ERROR] 。\n");
			return;
		}
	}
	I2C_AcknowledgeConfig(I2Cx, ENABLE);
}

/* I2C向指定地址写入数据 */
void i2c_set_reg(I2C_TypeDef* I2Cx, uint8_t slave_address, uint8_t target_reg, uint8_t target_data){
	uint32_t timer = TIMEOUT;
	
	while(I2C_GetFlagStatus(I2Cx, I2C_FLAG_BUSY)){
		if(timer-- == 0){
			printf("[ERROR] 等待I2C设备超时。\n");
			return;
		}
	}
	timer = TIMEOUT;
	
	// 生成起始信号
	I2C_GenerateSTART(I2Cx, ENABLE);
	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT)){
		if(timer-- == 0){
			printf("[ERROR] 生成起始信号超时。\n");
			return;
		}
	}
	timer = TIMEOUT;
	
	// 发送从机地址信号
	I2C_Send7bitAddress(I2Cx, slave_address, I2C_Direction_Transmitter);
	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)){
		if(timer-- == 0){
			printf("[ERROR] 与从机建立连接超时。\n");
			return;
		}
	}
	timer = TIMEOUT;
	
	// 发送发送访问的寄存器
	I2C_SendData(I2Cx, target_reg);
	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED)){
		if(timer-- == 0){
			printf("[ERROR] 发送寄存器超时。\n");
			return;
		}
	}
	timer = TIMEOUT;
	
	// 发送需要配置的数据
	I2C_SendData(I2Cx, target_data);
	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED)){
		if(timer-- == 0){
			printf("[ERROR] 发送数据超时。\n");
			return;
		}
	}
	timer = TIMEOUT;
	
	// 发送停止信号
	I2C_GenerateSTOP(I2Cx, ENABLE);
}

