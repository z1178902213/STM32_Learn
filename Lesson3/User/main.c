#include "stm32f4xx.h"
#include "bsp_led.h"

void delay(uint32_t count){
	for(;count >0; count --);
}

int main(void){
    while(1){
			turn_on_red();
			delay(0xffffff);
			turn_off_red();
			delay(0xffffff);
		}
}

