#include "stm32f4xx.h"
#include "bsp_led.h"
#include "bsp_key.h"
#include "bsp_usart.h"

void delay500ms(){
	uint32_t i = 21454112;
	for(;i >0; i --);
}

void delay2s(){
	uint32_t a = 4;
	for(; a>0; a--){
		delay500ms();
	}
}

void init_nvic(){
	// 配置中断优先级分组
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	
	// 把USART1配置中断优先级，然后给NVIC进行管理
	NVIC_InitTypeDef NVIC_USART1_InitStruct;
	NVIC_USART1_InitStruct.NVIC_IRQChannel = USART1_IRQn;
	NVIC_USART1_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_USART1_InitStruct.NVIC_IRQChannelSubPriority = 1;
	NVIC_USART1_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_USART1_InitStruct);
}

int main(void){
	char *s = "I am ready.\n";
	init_nvic();
	
	init_led();
	init_usart1();
	
	turn_off_red();
	turn_off_green();
	turn_off_blue();
	
	while(1){
		usart1_send_s(s);
		delay2s();
	}
}

