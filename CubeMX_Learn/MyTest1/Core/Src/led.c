#include "led.h"


// 使用此函数前需要先初始化GPIOF
void LED_Turn(LED_COLOR color, LED_STATUS status){
	uint8_t i = 0;
	for(i = 0; i < 3; i++){
		if((color & (0x01 << i)) == color){
			HAL_GPIO_WritePin(GPIOF, GPIO_PIN_5 << i, (GPIO_PinState)status);
		}
	}
}

void LED_Turn_Red(LED_STATUS status){
	if(status == LED_ON){
		HAL_GPIO_WritePin(GPIOF, LED_R_Pin, GPIO_PIN_RESET);
	}else{
		HAL_GPIO_WritePin(GPIOF, LED_R_Pin, GPIO_PIN_SET);
	}
}
