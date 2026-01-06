#include "stm32f4xx.h"
#include "bsp_led.h"

#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x02000000+((addr &0x000FFFFF)<<5)+(bitnum<<2))
#define BIT_ADDR(addr, bitnum) (*(volatile unsigned long*)(BITBAND(addr, bitnum)))
#define LED_RED BIT_ADDR(GPIOF_BASE+0X14, 6)
#define LED_GREEN BIT_ADDR(GPIOF_BASE+0X14, 7)
#define LED_BLUE BIT_ADDR(GPIOF_BASE+0X14, 8)
#define LED_ON 0
#define LED_OFF 1

void delay(__IO uint32_t count){
    for(; count>0; count--);
}

int main(void){
    init_led();
    LED_RED = LED_OFF;
    LED_GREEN = LED_OFF;
    LED_BLUE = LED_OFF;
    while(1){
        LED_RED = LED_ON;
        delay(0xFFFFFF);
        LED_RED = LED_OFF;
        delay(0xFFFFFF);
        LED_GREEN = LED_ON;
        delay(0xFFFFFF);
        LED_GREEN = LED_OFF;
        delay(0xFFFFFF);
        LED_BLUE = LED_ON;
        delay(0xFFFFFF);
        LED_BLUE = LED_OFF;
        delay(0xFFFFFF);
    }
}

