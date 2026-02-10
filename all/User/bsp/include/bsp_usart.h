#ifndef _BSP_USART_H_
#define _BSP_USART_H_
#include "stm32f4xx.h"

void init_usart1(void);
void usart1_send_c(uint16_t c);
void usart1_send_s(char *s);
uint16_t usart1_receive_c(void);

#endif

