#include "stm32f4xx.h"
#include "bsp_led.h"
#include "bsp_key.h"
#include "bsp_myclkconfig.h"
#include "bsp_clkconfig.h"

void delay500ms(){
	uint32_t i = 21454112;
	for(;i >0; i --);
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
	MyClkconfig();
	// User_SetSysClock();
	init_led();
	turn_off_red();
	turn_off_green();
	turn_off_blue();
	init_key();
	while(1){
		turn_on_red();
		delay500ms();
		turn_off_red();
		delay500ms();
	}
}

