#include "stm32f4xx_gpio.h"

void Delay( uint32_t nCount); 

int main(void){
	GPIO_INIT_CONFIG GPIOF_INIT_CONFIG;
	
	RCC->AHB1ENR |= (1<<5);
	
	GPIOF_INIT_CONFIG.GPIO_PIN = GPIO_PIN_6;
	GPIOF_INIT_CONFIG.GPIO_MODE = GPIO_MODER_OUTPUT;
	GPIOF_INIT_CONFIG.GPIO_TYPE = GPIO_OTYUPER_PUSHPULL;
	GPIOF_INIT_CONFIG.GPIO_PUPD = GPIO_PUPDR_UP;
	GPIOF_INIT_CONFIG.GPIO_SPEED = GPIO_OSPEEDR_LOW;
	gpio_init(GPIOF, &GPIOF_INIT_CONFIG);
	
	
	while(1){
		set_gpio(GPIOF, GPIO_PIN_6);
		Delay(0xFFFFF);
		reset_gpio(GPIOF, GPIO_PIN_6);
		Delay(0xFFFFF);
	}
}

void Delay( uint32_t nCount)	 
{
	for(; nCount != 0; nCount--);
}

void SystemInit(){

}

