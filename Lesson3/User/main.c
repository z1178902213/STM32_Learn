#include "stm32f4xx.h"
#include "bsp_led.h"


int main(void){
	SysTick_Config(SystemCoreClock / 100000);
	
	init_led();
	// 一开始要先把红绿蓝都配置为关闭，不然亮灯很奇怪。
	turn_off_red();
	turn_off_green();
	turn_off_blue();
	while(1){
		toggle_red();
		delay1s();
	}
}

