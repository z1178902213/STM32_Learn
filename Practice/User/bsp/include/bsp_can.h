#ifndef _BSP_CAN_H_
#define _BSP_CAN_H_
#include "stm32f4xx.h"

void init_can(void);
void Config_Tx(CanTxMsg* can_tx);
void Init_Can2_NVIC(void);
void Config_Rx_Filter(void);

#endif

