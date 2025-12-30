#include "stm32f4xx.h"
#include "bsp_led.h"
#include "bsp_key.h"

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
	uint8_t led_red_status = 0;
	uint8_t led_green_status = 0;
	init_led();
	turn_off_red();
	turn_off_green();
	turn_off_blue();
	init_key();
	while(1){
		if(scan_key1()){
			if(led_red_status == 0){
				turn_on_red();
				led_red_status = 1;
			}else{
				turn_off_red();
				led_red_status = 0;
			}
		}
		if(scan_key2()){
			if(led_green_status == 0){
				turn_on_green();
				led_green_status = 1;
			}else{
				turn_off_green();
				led_green_status = 0;
			}
		}
	}
}

