#include "stm32f4xx.h"
#include "bsp_led.h"
#include "bsp_key.h"
#include "bsp_clkconfig.h"

void delay(uint32_t count){
	for(;count >0; count --);
}

uint8_t scan_key1(){
	if(read_key1() == 1){
		while(read_key1() == 1);
		return 1;
	}else{
		return 0;
	}
}

uint8_t scan_key2(){
	if(read_key2() == 1){
		while(read_key2() == 1);
		return 1;
	}else{
		return 0;
	}
}

int main(void){
	User_SetSysClock();
	init_led();
	turn_off_red();
	turn_off_green();
	turn_off_blue();
	init_key();
	while(1){
		turn_on_red();
		delay(16800000);
		turn_off_red();
		delay(16800000);
	}
}

