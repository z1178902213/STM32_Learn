#include "stm32f4xx.h"
#include "bsp_led.h"

void delay(uint32_t count){
	for(;count >0; count --);
}

int main(void){
	init_led();
	// 一开始要先把红绿蓝都配置为关闭，不然亮灯很奇怪。
	turn_off_red();
	turn_off_green();
	turn_off_blue();
	while(1){
		turn_on_red();
		delay(0xffffff);
		turn_off_red();
		delay(0xffffff);
		turn_on_green();
		delay(0xffffff);
		turn_off_green();
		delay(0xffffff);
		turn_on_blue();
		delay(0xffffff);
		turn_off_blue();
		delay(0xffffff);
	}
}

