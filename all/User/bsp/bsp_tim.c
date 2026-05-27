#include "bsp_tim.h"
#include "bsp_usart.h"



void init_tim6(){

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	NVIC_InitTypeDef NVIC_TIM6_InitStruct;
	NVIC_TIM6_InitStruct.NVIC_IRQChannel = TIM6_DAC_IRQn;
	NVIC_TIM6_InitStruct.NVIC_IRQChannelPreemptionPriority =1;
	NVIC_TIM6_InitStruct.NVIC_IRQChannelSubPriority = 1;
	NVIC_TIM6_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_TIM6_InitStruct);
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);

	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_TimeBaseInitStruct.TIM_Prescaler = 84-1;		// 定时器配置成1MHz，也就是1ms 定时器计数一次
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period = 10 - 1;		// 定时器计数到10的时候发生上溢的事件，产生定时器中断，此时过了10ms。
	TIM_TimeBaseInit(TIM6, &TIM_TimeBaseInitStruct);
	
	TIM_ClearFlag(TIM6, TIM_FLAG_Update);
	TIM_ITConfig(TIM6, TIM_IT_Update, ENABLE);
	TIM_Cmd(TIM6, ENABLE);
}

// 配置TIM8，开启PWM和互补输出
void init_tim8_ex1(){
	// 开时钟
	printf("--> 开启时钟\n");
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);
	
	// 配置GPIO复用
	printf("--> 开启配置GPIO复用\n");
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource5, GPIO_AF_TIM8);
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource6, GPIO_AF_TIM8);
	
	/* 错误记录：在配置输出的过程中需要同时打开GPIOA_Pin_6，该引脚
			作为断路引脚，启动后对TIM_BDTRInitStruct的TIM_Break配置启动，刹车才能使用
			方波才能正确被显示。
	*/
	//GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_TIM8);
	// GPIO初始化
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6;
	GPIO_Init(GPIOC, &GPIO_InitStruct);
	//GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6;
	//GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	// 配置定时器
	TIM_TimeBaseInitTypeDef TIM_InitStruct;
	TIM_InitStruct.TIM_Prescaler = 1680 - 1;		// 定时器频率设置为100KHz，10us计数一次
	TIM_InitStruct.TIM_Period = 1000-1;						// 设置周期为1000，那么就是10ms计数到指定值
	TIM_InitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_InitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_InitStruct.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM8, &TIM_InitStruct);
	// 将定时器配置输出模式
	TIM_OCInitTypeDef TIM_OCInitStruct;
	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStruct.TIM_OutputNState = TIM_OutputNState_Enable;
	TIM_OCInitStruct.TIM_Pulse = 127;
	TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStruct.TIM_OCNPolarity = TIM_OCNPolarity_High;
	TIM_OCInitStruct.TIM_OCIdleState = TIM_OCIdleState_Set;
	TIM_OCInitStruct.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
	TIM_OC1Init(TIM8, &TIM_OCInitStruct);
	TIM_OC1PreloadConfig(TIM8, TIM_OCPreload_Enable);
	// 配置定时器的死区
	TIM_BDTRInitTypeDef TIM_BDTRInitStruct;
	TIM_BDTRInitStruct.TIM_OSSRState = TIM_OSSRState_Enable;
	TIM_BDTRInitStruct.TIM_OSSIState = TIM_OSSIState_Enable;
	TIM_BDTRInitStruct.TIM_LOCKLevel = TIM_LOCKLevel_1;
	TIM_BDTRInitStruct.TIM_DeadTime = 11;
	/* 如果没有配置断路输入引脚，则需要将刹车配置为关闭 */
	TIM_BDTRInitStruct.TIM_Break = TIM_Break_Disable;
	//TIM_BDTRInitStruct.TIM_Break = TIM_Break_Enable;
	
	TIM_BDTRInitStruct.TIM_BreakPolarity = TIM_BreakPolarity_Low;
	TIM_BDTRInitStruct.TIM_AutomaticOutput = TIM_AutomaticOutput_Enable;
	TIM_BDTRConfig(TIM8, &TIM_BDTRInitStruct);
	// 启动高级定时器
	TIM_Cmd(TIM8, ENABLE);
	TIM_CtrlPWMOutputs(TIM8, ENABLE);
	printf("--> 配置完成，启动高级定时器。\n");
}

void TIMx_NVIC_Configure(void){
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	NVIC_InitStruct.NVIC_IRQChannel = TIM8_CC_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 3;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);
}

void init_tim2_ex2(){
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource5, GPIO_AF_TIM2);
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	TIM_TimeBaseInitTypeDef TIM_InitStruct;
	TIM_InitStruct.TIM_Period = 10000-1;
	TIM_InitStruct.TIM_Prescaler = 840 - 1;			// TIM2是挂在APB1上的，默认时钟42MHz，倍频后给TIM2就是84MHz，TIM8是挂在APB2所以是168MHz
	// TIM_InitStruct.TIM_RepetitionCounter = 0;
	TIM_InitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_InitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM2, &TIM_InitStruct);
	
	TIM_OCInitTypeDef TIM_OCInitStruct;
	TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStruct.TIM_Pulse = 3000-1;
	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OC1Init(TIM2, &TIM_OCInitStruct);
	TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);
	TIM_Cmd(TIM2, ENABLE);
}

void init_tim8_ex2(){
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);
	
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource6, GPIO_AF_TIM8);
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOC, &GPIO_InitStruct);
	
	TIM_TimeBaseInitTypeDef TIM_InitStruct;
	TIM_InitStruct.TIM_Period = 0xFFFF-1;
	TIM_InitStruct.TIM_Prescaler = 1680-1;
	TIM_InitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM8, &TIM_InitStruct);
	
	TIM_ICInitTypeDef TIM_ICInitStruct;
	TIM_ICInitStruct.TIM_Channel = TIM_Channel_1;
	TIM_ICInitStruct.TIM_ICPolarity = TIM_ICPolarity_Rising;
	TIM_ICInitStruct.TIM_ICPrescaler = TIM_ICPSC_DIV1;
	TIM_ICInitStruct.TIM_ICSelection = TIM_ICSelection_DirectTI;
	TIM_ICInitStruct.TIM_ICFilter = 0x0;
	TIM_PWMIConfig(TIM8, &TIM_ICInitStruct);
	
	TIM_ICInitStruct.TIM_Channel = TIM_Channel_2;
	TIM_ICInitStruct.TIM_ICPolarity = TIM_ICPolarity_Falling;
	TIM_ICInitStruct.TIM_ICPrescaler = TIM_ICPSC_DIV1;
	// 使用另一个通道捕获下降沿，需要Indirect，这样配置CH2可以查看CH1引脚的情况。
	TIM_ICInitStruct.TIM_ICSelection = TIM_ICSelection_IndirectTI;
	TIM_ICInitStruct.TIM_ICFilter = 0x0;
	TIM_PWMIConfig(TIM8, &TIM_ICInitStruct);
	
	TIM_SelectInputTrigger(TIM8, TIM_TS_TI1FP1);
	
	TIM_SelectSlaveMode(TIM8, TIM_SlaveMode_Reset);
	TIM_SelectMasterSlaveMode(TIM8,TIM_MasterSlaveMode_Enable);
	
	TIM_Cmd(TIM8, ENABLE);
	TIM_ITConfig(TIM8, TIM_IT_CC1, ENABLE);
}

void init_tim2_ex3(){
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
		
		GPIO_PinAFConfig(GPIOA, GPIO_PinSource5, GPIO_AF_TIM2);
		
		GPIO_InitTypeDef GPIO_InitStruct;
		GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5;
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
		GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
		GPIO_Init(GPIOA, &GPIO_InitStruct);
		
		TIM_TimeBaseInitTypeDef TIM_InitStruct;
		TIM_InitStruct.TIM_Period = 10000-1;
		TIM_InitStruct.TIM_Prescaler = 840 - 1;
		TIM_InitStruct.TIM_RepetitionCounter = 0;
		TIM_InitStruct.TIM_CounterMode = TIM_CounterMode_Up;
		TIM_InitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
		TIM_TimeBaseInit(TIM8, &TIM_InitStruct);
		
		TIM_ICInitTypeDef TIM_ICInitStruct;
		TIM_ICInitStruct.TIM_Channel = TIM_Channel_1;
		TIM_ICInitStruct.TIM_ICFilter = 0x0;
		TIM_ICInitStruct.TIM_ICPolarity = TIM_ICPolarity_Falling;
		TIM_ICInitStruct.TIM_ICPrescaler = TIM_ICPSC_DIV1;
		TIM_ICInitStruct.TIM_ICSelection = TIM_ICSelection_DirectTI;
		TIM_ICInit(TIM8, &TIM_ICInitStruct);
		
		TIM_Cmd(TIM8, ENABLE);
}

void reset_pa5_ex3(){
		GPIO_InitTypeDef GPIO_InitStruct;
		GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5;
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
		GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
		GPIO_Init(GPIOA, &GPIO_InitStruct);

		GPIO_ResetBits(GPIOA, GPIO_Pin_5);
		
		
		GPIO_PinAFConfig(GPIOA, GPIO_PinSource5, GPIO_AF_TIM2);
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
		GPIO_Init(GPIOA, &GPIO_InitStruct);
}


