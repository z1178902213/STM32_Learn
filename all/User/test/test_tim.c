#include "test.h"
#include "bsp_usart.h"
#include "bsp_tim.h"
#include "bsp_led.h"

void test_tim6(){
	init_led();
	turn_off_red();
	turn_off_green();
	turn_off_blue();
	
	init_tim6();
}

void test_tim8_ex1(){
	init_usart1();
	init_tim8_ex1();
}

void test_tim2_tim8_ex2(){
	init_usart1();
	printf("-> 初始化NVIC \n");
	TIMx_NVIC_Configure();
	printf("-> 初始化TIM2 \n");
	init_tim2_ex2();
	printf("-> 初始化TIM8 \n");
	init_tim8_ex2();
}
