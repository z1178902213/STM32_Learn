#ifndef __USER_HAL_CALLBACK_H
#define __USER_HAL_CALLBACK_H
#include "stm32f4xx.h"
#include "stm32f4xx_hal_uart.h"
void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size);


#endif

