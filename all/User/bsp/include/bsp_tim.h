#ifndef _BSP_TIM_H_
#define _BSP_TIM_H_
#include "stm32f4xx.h"

void init_tim6(void);
void init_tim8_ex1(void);
void init_tim2_ex2(void);
void init_tim8_ex2(void);
void TIM8_CC_IRQHandler(void);
void TIMx_NVIC_Configure(void);

#endif

