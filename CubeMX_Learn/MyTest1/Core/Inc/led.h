#ifndef __LED_H
#define __LED_H
#include "stm32f4xx.h"
#include "main.h"

typedef enum {
	LED_RED = 0x01,
	LED_GREEN = 0x02,
	LED_BLUE = 0x04
} LED_COLOR;

typedef enum {
	LED_OFF = 0U,
	LED_ON = !LED_OFF
} LED_STATUS;

void LED_Turn(LED_COLOR color, LED_STATUS status);
void LED_Turn_Red(LED_STATUS status);

#endif


