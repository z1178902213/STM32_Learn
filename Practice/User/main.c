#include "stm32f4xx.h"
#include "bsp_led.h"
#include "bsp_key.h"
#include "bsp_usart.h"
#include "bsp_dma.h"
#include "bsp_iic.h"
#include "bsp_spi.h"
#include "bsp_fsmc.h"
#include "bsp_tim.h"
#include "common.h"
#include "test.h"

int main(void){
	init_led();
	init_usart1();
	init_tim6();
	
	turn_off_blue();
	turn_off_red();
	turn_off_green();
	
	init_tim2_ex3();
	detect_tpad_ex3();
	
	while(1){
		if(detect_tpad_ex3() == 1){
			turn_off_red();
			turn_on_green();
		}else{
			turn_off_green();
			turn_on_red();
		}
	}
}
