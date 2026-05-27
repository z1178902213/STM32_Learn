#include "test.h"
#include "bsp_wwdg.h"
#include "bsp_key.h"
#include "bsp_usart.h"
#include "bsp_led.h"

#define COUNTER 127
#define PRESCALER WWDG_Prescaler_8
#define WINDOWVALUE 80

void test_wwdg(){
	init_led();
	init_usart1();
	turn_off_blue();
	turn_off_green();
	turn_off_red();
	turn_on_red();
	
	init_wwdg(COUNTER, PRESCALER, WINDOWVALUE);
	printf("--> ¾¯È®ÉèÖÃÍê³É...\n");
	
	while(1){
	}
	
}
