#include "test.h"
#include "bsp_usart.h"
#include "bsp_led.h"
#include "bsp_key.h"
#include "bsp_iwdg.h"


void test_iwdg(){
		init_key();
		init_led();
		init_usart1();
		init_iwdg();
		
		turn_off_blue();
		turn_off_red();
		turn_off_green();
		turn_on_red();
		printf("--> Éè±¸¸´Î».\n");
		
		while(1){
			if(get_key_status() == SET){
				reload_iwdg();
				turn_off_red();
				turn_on_green();
				printf("--> Î¹¹·.\n");
			}
		}
}

