#include "stm32f4xx.h"
#include "bsp_led.h"
#include "bsp_key.h"
#include "bsp_usart.h"
#include "bsp_dma.h"
#include "bsp_iic.h"
#include "bsp_spi.h"
#include "bsp_fsmc.h"
#include "test.h"

int main(void){
	test_tim2_tim8_ex2();
	
	while(1){
		
	}
}
