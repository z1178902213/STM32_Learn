#include"stm32f4xx_gpio.h"

void gpio_init(GPIO_TYPE* gpiox, GPIO_INIT_CONFIG* gpio_config){
	uint16_t target_pins = gpio_config->GPIO_PIN;
	uint16_t i = 0;
	uint16_t current_pin = 0;
	for(i = 0; i < 16; i++){
		current_pin = ((uint32_t)0x01) << i;
		
		if((current_pin & target_pins) == current_pin){
			gpiox->MODER &= ~(3 << 2 * i);
			gpiox->MODER |= gpio_config->GPIO_MODE << (2 * i);
			
			gpiox->OTYPER |= gpio_config->GPIO_TYPE << i;
			
			gpiox->OSPEEDR &= ~(3 << (2 * i));
			gpiox->OSPEEDR |= gpio_config->GPIO_SPEED << (2 * i);
		}
	}
	
}

//void gpio_init(GPIO_TYPE* GPIOx, GPIO_INIT_CONFIG* GPIO_InitStruct)
//{
//	  uint32_t pinpos = 0x00, pos = 0x00 , currentpin = 0x00;
//	
//	/*-- GPIO Mode Configuration --*/
//  for (pinpos = 0x00; pinpos < 16; pinpos++)
//  {
//		/*以下运算是为了通过 GPIO_InitStruct->GPIO_Pin 算出引脚号0-15*/
//		
//		/*经过运算后pos的pinpos位为1，其余为0，与GPIO_Pin_x宏对应。pinpos变量每次循环加1，*/
//		pos = ((uint32_t)0x01) << pinpos;
//   
//		/* pos与GPIO_InitStruct->GPIO_Pin做 & 运算，若运算结果currentpin == pos，
//		则表示GPIO_InitStruct->GPIO_Pin的pinpos位也为1，
//		从而可知pinpos就是GPIO_InitStruct->GPIO_Pin对应的引脚号：0-15*/
//    currentpin = (GPIO_InitStruct->GPIO_PIN) & pos;

//		/*currentpin == pos时执行初始化*/
//    if (currentpin == pos)
//		{		
//			/*GPIOx端口，MODER寄存器的GPIO_InitStruct->GPIO_Pin对应的引脚，MODER位清空*/
//			GPIOx->MODER  &= ~(3 << (2 *pinpos));
//		
//			/*GPIOx端口，MODER寄存器的GPIO_Pin引脚，MODER位设置"输入/输出/复用输出/模拟"模式*/
//			GPIOx->MODER |= (((uint32_t)GPIO_InitStruct->GPIO_MODE) << (2 *pinpos));

//			/*GPIOx端口，PUPDR寄存器的GPIO_Pin引脚，PUPDR位清空*/
//			GPIOx->PUPDR &= ~(3 << ((2 *pinpos)));
//		
//			/*GPIOx端口，PUPDR寄存器的GPIO_Pin引脚，PUPDR位设置"上/下拉"模式*/
//			GPIOx->PUPDR |= (((uint32_t)GPIO_InitStruct->GPIO_PUPD) << (2 *pinpos));		
//		
//			/*若模式为"输出/复用输出"模式，则设置速度与输出类型*/
//			if ((GPIO_InitStruct->GPIO_MODE == GPIO_MODER_OUTPUT) || (GPIO_InitStruct->GPIO_MODE == GPIO_MODER_MUX))
//			{
//				/*GPIOx端口，OSPEEDR寄存器的GPIO_Pin引脚，OSPEEDR位清空*/
//				GPIOx->OSPEEDR &= ~(3 << (2 *pinpos));
//				/*GPIOx端口，OSPEEDR寄存器的GPIO_Pin引脚，OSPEEDR位设置输出速度*/
//				GPIOx->OSPEEDR |= ((uint32_t)(GPIO_InitStruct->GPIO_SPEED) << (2 *pinpos));

//				/*GPIOx端口，OTYPER寄存器的GPIO_Pin引脚，OTYPER位清空*/
//				GPIOx->OTYPER  &= ~(1 << (pinpos)) ;
//				/*GPIOx端口，OTYPER位寄存器的GPIO_Pin引脚，OTYPER位设置"推挽/开漏"输出类型*/
//				GPIOx->OTYPER |= (uint16_t)(((uint16_t)GPIO_InitStruct->GPIO_TYPE) << (pinpos));
//			}
//		}
//	}
//}

void set_gpio(GPIO_TYPE* gpiox, uint16_t gpio_pin){
	gpiox->BSRRL = gpio_pin;
}

void reset_gpio(GPIO_TYPE* gpiox, uint16_t gpio_pin){
	gpiox->BSRRH = gpio_pin;
}

