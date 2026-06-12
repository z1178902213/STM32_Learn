#include "bsp_iic.h"
#include "bsp_usart.h"

void init_iic(void){
	// 开启IIC1总线时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
	
	// 开启连接到IIC1的相应GPIO口的总线时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	
	// 配置GPIO复用为IIC
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource8, GPIO_AF_I2C1);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource9, GPIO_AF_I2C1);
	
	// 初始化GPIO，设置为复用模式
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_OD;
	GPIO_InitStruct.GPIO_Speed = GPIO_Fast_Speed;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	
	// 初始化I2C配置
	I2C_InitTypeDef I2C_InitStruct;
	
	I2C_InitStruct.I2C_Mode = I2C_Mode_I2C;
	I2C_InitStruct.I2C_DutyCycle = I2C_DutyCycle_2;
	I2C_InitStruct.I2C_OwnAddress1 = 0x0A;
	I2C_InitStruct.I2C_Ack = I2C_Ack_Enable;
	I2C_InitStruct.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	I2C_InitStruct.I2C_ClockSpeed = 400000;
	
	I2C_Init(I2C1, &I2C_InitStruct);
	
	I2C_Cmd(I2C1, ENABLE);
	
	I2C_AcknowledgeConfig(I2C1, ENABLE);
	
}

void write_data_eeprom(){
	I2C_GenerateSTART(I2C1, ENABLE);
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));
	printf("--> I2C1 WRITE start.\n");
	
	I2C_Send7bitAddress(I2C1, 0xA0, I2C_Direction_Transmitter);
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
	printf("--> I2C1 send slave addr.\n");
	
	I2C_SendData(I2C1, 0x00);
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	printf("--> I2C1 send eeprom addr.\n");
	
	I2C_SendData(I2C1, 8);
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	printf("--> I2C1 send data.\n");
	
	I2C_GenerateSTOP(I2C1, ENABLE);
	printf("--> I2C1 stop.\n");
}

void check_data_eeprom(){
	uint8_t a = 0;
	
	while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY));
	
	I2C_GenerateSTART(I2C1, ENABLE);
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));
	printf("--> I2C1 READ start.\n");
	
	I2C_Send7bitAddress(I2C1, 0xA0, I2C_Direction_Transmitter);
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
	printf("--> I2C1 READ send slave addr.\n");
	I2C_Cmd(I2C1, ENABLE);
	
	I2C_SendData(I2C1, 0x00);
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	printf("--> I2C1 READ send eeprom data.\n");
	
	I2C_GenerateSTART(I2C1, ENABLE);
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));
	printf("--> I2C1 READ start2.\n");
	
	I2C_Send7bitAddress(I2C1, 0xA0, I2C_Direction_Receiver);
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
	printf("--> I2C1 READ send slave addr2.\n");
	
	a = I2C_ReceiveData(I2C1);
	
	I2C_AcknowledgeConfig(I2C1, DISABLE);
	printf("--> I2C1读取到EEPROM写入的值：%d\n", a);
	printf("--> I2C1 接收数据完成.\n");
	
	I2C_GenerateSTOP(I2C1, ENABLE);
	
	I2C_AcknowledgeConfig(I2C1, ENABLE);
}
