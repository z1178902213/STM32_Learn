#include "bsp_led.h"

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
	uint8_t tmp = Bit_RESET;
	tmp = GPIO_ReadOutputDataBit(GPIOF, GPIO_Pin_6);
	if(tmp == Bit_SET){
		turn_on_red();
	}else{
		turn_off_red();
	}
}

void turn_on_green(void){
	GPIO_ResetBits(GPIOF, GPIO_Pin_7);
}

void turn_off_green(void){
	GPIO_SetBits(GPIOF, GPIO_Pin_7);
}

void toggle_green(void){
	uint8_t tmp = Bit_RESET;
	tmp = GPIO_ReadOutputDataBit(GPIOF, GPIO_Pin_7);
	if(tmp == Bit_SET){
		turn_on_green();
	}else{
		turn_off_green();
	}
}

void turn_on_blue(void){
	GPIO_ResetBits(GPIOF, GPIO_Pin_8);
}

void turn_off_blue(void){
	GPIO_SetBits(GPIOF, GPIO_Pin_8);
}

void toggle_blue(void){
	uint8_t tmp = Bit_RESET;
	tmp = GPIO_ReadOutputDataBit(GPIOF, GPIO_Pin_8);
	if(tmp == Bit_SET){
		turn_on_blue();
	}else{
		turn_off_blue();
	}
}

