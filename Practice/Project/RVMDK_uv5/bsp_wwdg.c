#include "bsp_wwdg.h"

void WWDG_NVIC_Init(){
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	
	NVIC_InitTypeDef WWDG_NVIC_InitStruct;
	WWDG_NVIC_InitStruct.NVIC_IRQChannel = WWDG_IRQn;
	WWDG_NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
	WWDG_NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
	WWDG_NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	
	NVIC_Init(&WWDG_NVIC_InitStruct);
}

void init_wwdg(uint8_t Counter, uint32_t Prescaler, uint8_t WindowValue){
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG, ENABLE);

	WWDG_SetCounter(Counter);
	
	WWDG_SetPrescaler(Prescaler);
	
	WWDG_SetWindowValue(WindowValue);
	
	WWDG_Enable(Counter);
	
	WWDG_ClearFlag();
	
	WWDG_NVIC_Init();
	
	WWDG_EnableIT();
}

void wwdg_reload(uint8_t Counter){
	WWDG_SetCounter(Counter);
}
