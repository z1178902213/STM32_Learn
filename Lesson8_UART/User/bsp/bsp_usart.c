#include "bsp_usart.h"

void init_usart1(void){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	
	// 这里有可能出问题，貌似要配置两次？
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);
	
	GPIO_InitTypeDef GPIOA_USART_Struct;
	GPIOA_USART_Struct.GPIO_Pin = GPIO_Pin_9;
	GPIOA_USART_Struct.GPIO_Mode = GPIO_Mode_AF;
	GPIOA_USART_Struct.GPIO_OType = GPIO_OType_PP;
	GPIOA_USART_Struct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIOA_USART_Struct);
	GPIOA_USART_Struct.GPIO_Pin = GPIO_Pin_10;
	GPIO_Init(GPIOA, &GPIOA_USART_Struct);

	USART_InitTypeDef USART1_Struct;
	USART1_Struct.USART_BaudRate = 115200;
	USART1_Struct.USART_WordLength = USART_WordLength_8b;
	USART1_Struct.USART_StopBits = USART_StopBits_1;
	USART1_Struct.USART_Parity = USART_Parity_No;
	USART1_Struct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART1_Struct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_Init(USART1, &USART1_Struct);
	
	USART_ClockInitTypeDef USART1_Clock_Struct;
	USART_ClockStructInit(&USART1_Clock_Struct);
	USART_ClockInit(USART1, &USART1_Clock_Struct);
	
	USART_Cmd(USART1, ENABLE);
}

void usart1_send_c(uint16_t c){
	USART_SendData(USART1, c);
}
