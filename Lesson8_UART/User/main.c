#include "stm32f4xx.h"
#include "bsp_led.h"
#include "bsp_key.h"
#include "bsp_usart.h"

void delay500ms(){
	uint32_t i = 21454112;
	for(;i >0; i --);
}

int main(void){
	init_led();
	init_usart1();
	
	turn_off_red();
	turn_off_green();
	turn_off_blue();
	
	usart1_send_c('c');
	
	while(1){
		
	}
}

