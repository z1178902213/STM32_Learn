#include "bsp_usart.h"

void init_usart1(void){
	// 1、开启USART1与GPIOA的相对应的总线的时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	
	// 2、将GPIOA对应IO口配置复用为USART1
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);
	
	// 3、初始化GPIO9和GPIO10
	GPIO_InitTypeDef GPIOA_USART_Struct;
	GPIOA_USART_Struct.GPIO_Pin = GPIO_Pin_9;
	GPIOA_USART_Struct.GPIO_Mode = GPIO_Mode_AF;
	GPIOA_USART_Struct.GPIO_OType = GPIO_OType_PP;
	GPIOA_USART_Struct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIOA_USART_Struct);
	GPIOA_USART_Struct.GPIO_Pin = GPIO_Pin_10;
	GPIO_Init(GPIOA, &GPIOA_USART_Struct);

	// 4、USART1初始化配置
	USART_InitTypeDef USART1_Struct;
	USART1_Struct.USART_BaudRate = 115200;
	USART1_Struct.USART_WordLength = USART_WordLength_8b;
	USART1_Struct.USART_StopBits = USART_StopBits_1;
	USART1_Struct.USART_Parity = USART_Parity_No;
	USART1_Struct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART1_Struct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_Init(USART1, &USART1_Struct);

	// 6、配置USART在发送完数据和接收到数据以后产生中断
//	USART_ITConfig(USART1, USART_FLAG_TC, ENABLE);
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	
	USART_Cmd(USART1, ENABLE);
}

void usart1_send_c(uint16_t c){
	USART_SendData(USART1, c);
}

void usart1_send_s(char *s){
	uint16_t i = 0;
	while(*(s+i) != '\0')
	{
		usart1_send_c(*(s+i));
		while(USART_GetFlagStatus(USART1, USART_FLAG_TC) != SET);
		i++;
	}
}

uint16_t usart1_receive_c(void){
	uint16_t c = USART_ReceiveData(USART1);
	return c;
}
