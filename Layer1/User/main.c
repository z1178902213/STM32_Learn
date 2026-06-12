#include "stm32f4xx.h"
#include "bsp_usart.h"
#include "bsp_tim.h"
#include "bsp_mpu6050.h"
#include "bsp_led.h"
#include "common.h"
#include "bsp_epprom.h"
#include "bsp_spi.h"
#include "bsp_spi_flash.h"

void nvic_init(){
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	
	NVIC_InitTypeDef nvic_init_struct;
	
	// 配置TIM6的中断优先级
	nvic_init_struct.NVIC_IRQChannel = TIM6_DAC_IRQn;
	nvic_init_struct.NVIC_IRQChannelPreemptionPriority = 0;
	nvic_init_struct.NVIC_IRQChannelSubPriority = 1;
	nvic_init_struct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvic_init_struct);
}

int main(void){
	uint32_t test_address = 0x00001000;
	
	init_tim6();
	init_usart1();
	init_led();
	
	turn_off_blue();
	turn_off_green();
	turn_off_red();
	
	init_spi();
	delay(100);
	ReadID();
	delay(1000);
	
	printf("========== 擦除前扇区数据 ==========\n");
	ReadBufferTest(test_address);
	delay(1000);
	printf("================================\n\n\n\n");
	
	printf("========== 测试擦除扇区 ==========\n");
	SectorErase(test_address);
	delay(1000);
	printf("================================\n\n");
	
	printf("========== 擦除后扇区数据 ==========\n");
	ReadBufferTest(test_address);
	delay(1000);
	printf("================================\n\n");
	
	printf("========== 向扇区写入数据 ==========\n");
	ProgramPageTest(test_address);
	delay(1000);
	printf("================================\n\n");
	
	printf("========== 写入数据后扇区数据 ==========\n");
	ReadBufferTest(test_address);
	delay(1000);
	printf("================================\n\n");
	
	
	while(1){
		turn_on_red();
		delay(500);
		turn_off_red();
		delay(500);
	}
}

