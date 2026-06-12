#ifndef _BSP_WWDG_H_
#define _BSP_WWDG_H_

#include "stm32f4xx.h"
void WWDG_NVIC_Init(void);
void init_wwdg(uint8_t Counter, uint32_t Prescaler, uint8_t WindowValue);
void wwdg_reload(uint8_t Counter);


#endif

