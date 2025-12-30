#include "bsp_key.h"

void init_key(void){
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	
	GPIO_InitTypeDef GPIO_CONFIG;
	
	GPIO_CONFIG.GPIO_Pin = GPIO_Pin_0;
	GPIO_CONFIG.GPIO_Mode = GPIO_Mode_IN;
	GPIO_Init(GPIOA, &GPIO_CONFIG);
	GPIO_CONFIG.GPIO_Pin = GPIO_Pin_13;
	GPIO_CONFIG.GPIO_Mode = GPIO_Mode_IN;
	GPIO_Init(GPIOA, &GPIO_CONFIG);
}

uint8_t read_key1(void){
	return GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0);
}

uint8_t read_key2(void){
	return GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_13);
}

