#include "stm32f4xx.h"
#include "bsp_led.h"
#include "bsp_key.h"
#include "bsp_exti.h"

void delay500ms(){
	uint32_t i = 21454112;
	for(;i >0; i --);
}

int main(void){
	init_led();
	
	init_key();
	init_nvic();
	init_exti0();
	init_exti13();
	
	turn_off_red();
	turn_off_green();
	turn_off_blue();
	
	while(1){

	}
}

