#include "bsp_usart.h"
#include "bsp_led.h"
#include "bsp_fsmc.h"

__IO uint32_t p = 0x6C000000;
uint8_t testValue __attribute__((at(0x6C000020)));

void test_sram(){
	init_led();
	init_usart1();
	
	*(uint32_t *)p = 0xFC;
	testValue = 0xDD;
	printf("--> 测试FSMC的SRAM，目前还未初始化，目标地址值为：0x%x，测试值：0x%x\n", *(uint32_t *)p, testValue);
	
	init_fsmc_sram();
	*(uint32_t *)p = 0xAB;
	testValue = 0xDD;
	printf("--> 测试FSMC的SRAM，目前已经初始化，目标地址值为：0x%x，测试值：0x%x\n", *(uint32_t *)p, testValue);
	
}
