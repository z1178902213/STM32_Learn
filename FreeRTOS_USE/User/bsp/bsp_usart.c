#include "bsp_usart.h"

void init_usart1(){
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);
	GPIO_InitTypeDef gpio_usart1_init_struct;
	gpio_usart1_init_struct.GPIO_Pin = GPIO_Pin_9;
	gpio_usart1_init_struct.GPIO_Mode = GPIO_Mode_AF;
	gpio_usart1_init_struct.GPIO_OType = GPIO_OType_PP;
	gpio_usart1_init_struct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &gpio_usart1_init_struct);
	gpio_usart1_init_struct.GPIO_Pin = GPIO_Pin_10;
	GPIO_Init(GPIOA, &gpio_usart1_init_struct);
	
	USART_InitTypeDef usart1_init_struct;
	usart1_init_struct.USART_Mode = USART_Mode_Tx|USART_Mode_Rx;
	usart1_init_struct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	usart1_init_struct.USART_BaudRate = 115200;
	usart1_init_struct.USART_Parity = USART_Parity_No;
	usart1_init_struct.USART_StopBits = USART_StopBits_1;
	usart1_init_struct.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART1, &usart1_init_struct);
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

///重定向c库函数printf到串口，重定向后可使用printf函数
int fputc(int ch, FILE *f)
{
		/* 发送一个字节数据到串口 */
		USART_SendData(USART1, (uint8_t) ch);
		
		/* 等待发送完毕 */
		while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);		
	
		return (ch);
}

///重定向c库函数scanf到串口，重写向后可使用scanf、getchar等函数
int fgetc(FILE *f)
{
		/* 等待串口输入数据 */
		while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);

		return (int)USART_ReceiveData(USART1);
}
