#include "stm32f4xx.h"
#include "user_rcc.h"
#include "bsp_led.h"
#include "bsp_uart.h"
#include "bsp_spi.h"

void delay(){
	uint32_t i = 0xfffff;
	for(; i > 0; i--){}
}

void init_rcc(){
	user_rcc_osc_init();
	user_rcc_clock_init();
}

int main(){
	// uint8_t msg = 0xAA;
	uint8_t msg2[] = "==> now let me test the uart1.\n";
	uint32_t flash_id = 0x00000000;
	init_rcc();
	init_led();
	init_uart();
	init_spi1();
	
	uart1_send_msg(msg2);
	spi1_wait_busy();
	spi1_flash_cs_off();
	flash_id = spi1_flash_read_id();
	printf("==> 读取到的flash是：0x%X", flash_id);
	
	while(1){
		toggle_led(LED_RED_GPIO_PIN);
		delay();
		toggle_led(LED_RED_GPIO_PIN);
		toggle_led(LED_BLUE_GPIO_PIN);
		delay();
		toggle_led(LED_BLUE_GPIO_PIN);
		toggle_led(LED_GREEN_GPIO_PIN);
		delay();
		toggle_led(LED_GREEN_GPIO_PIN);
	}
}

void SystemInit(){
	REG32_VALUE(RCC_CR) |= (uint32_t)0x00000001;
	REG32_VALUE(RCC_CFGR) = 0x00000000;
	REG32_VALUE(RCC_CR) &= (uint32_t)0xFEF6FFFF;
	REG32_VALUE(RCC_PLLCFGR) = 0x24003010;
	REG32_VALUE(RCC_CR) &= (uint32_t)0xFFFBFFFF;
	REG32_VALUE(RCC_CIR) = 0x00000000;
}

