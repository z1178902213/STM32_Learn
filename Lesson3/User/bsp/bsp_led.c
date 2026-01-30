#include "bsp_led.h"


static __IO uint32_t delayTime = 100000;

void init_led(void){
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
	
	GPIO_InitTypeDef GPIOF_CONFIG;
	
	GPIOF_CONFIG.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8;
	GPIOF_CONFIG.GPIO_Mode = GPIO_Mode_OUT;
	GPIOF_CONFIG.GPIO_OType = GPIO_OType_PP;
	GPIOF_CONFIG.GPIO_Speed = GPIO_Low_Speed;
	
	GPIO_Init(GPIOF, &GPIOF_CONFIG);
}

void turn_on_red(void){
	GPIO_ResetBits(GPIOF, GPIO_Pin_6);
}

void turn_off_red(void){
	GPIO_SetBits(GPIOF, GPIO_Pin_6);
}

void toggle_red(void){
	uint8_t tmp = GPIO_ReadOutputDataBit(GPIOF, GPIO_Pin_6);
	if(tmp == 0x00){
		turn_off_red();
	}else{
		turn_on_red();
	}
}

void turn_on_green(void){
	GPIO_ResetBits(GPIOF, GPIO_Pin_7);
}

void turn_off_green(void){
	GPIO_SetBits(GPIOF, GPIO_Pin_7);
}

void turn_on_blue(void){
	GPIO_ResetBits(GPIOF, GPIO_Pin_8);
}

void turn_off_blue(void){
	GPIO_SetBits(GPIOF, GPIO_Pin_8);
}

void cut_red(void){
	if(delayTime != 0x00){
		delayTime--;
	}
}

void delay1s(){
	while(delayTime != 0);
	delayTime = 100000;
}

void tickTing(){
	toggle_red();
}

