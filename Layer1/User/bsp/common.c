#include "common.h"

/* 使用TIM6进行延时，最小单位1ms，输入延时时长 */
void delay(uint32_t delay_time){
	uint32_t i = 0;
	for(; i < delay_time; i++){
		while(!TIM_GetITStatus(TIM6, TIM_IT_Update));
		TIM_ClearITPendingBit(TIM6, TIM_IT_Update);
	}
}

