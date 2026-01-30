#include "bsp_key.h"

/*
	初始化按键输入
*/
void init_key(){
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOC, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	
	GPIO_InitTypeDef GPIOA_Structure;
	GPIOA_Structure.GPIO_Pin = GPIO_Pin_0;
	GPIOA_Structure.GPIO_Mode = GPIO_Mode_IN;
	GPIOA_Structure.GPIO_Speed = GPIO_High_Speed;
	GPIOA_Structure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIOA_Structure);
	
	GPIO_InitTypeDef GPIOC_Structure;
	GPIOC_Structure.GPIO_Pin = GPIO_Pin_13;
	GPIOC_Structure.GPIO_Mode = GPIO_Mode_IN;
	GPIOC_Structure.GPIO_Speed = GPIO_High_Speed;
	GPIOC_Structure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOC, &GPIOC_Structure);
}

