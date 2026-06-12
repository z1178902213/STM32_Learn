#include "bsp_tim.h"

uint8_t TIM6_FLAG = 0;		// TIM6中断标志位

/* 初始化TIM6，默认配置为1ms */
void init_tim6(){
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);
	
	TIM_ITConfig(TIM6, TIM_IT_Update, ENABLE);
	
	TIM_TimeBaseInitTypeDef tim_timebase_init_struct;
	tim_timebase_init_struct.TIM_CounterMode = TIM_CounterMode_Up;
	tim_timebase_init_struct.TIM_ClockDivision = TIM_CKD_DIV1;
	tim_timebase_init_struct.TIM_Period = 1000;
	tim_timebase_init_struct.TIM_Prescaler = 84;
	tim_timebase_init_struct.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM6, &tim_timebase_init_struct);
	TIM_Cmd(TIM6, ENABLE);
}

