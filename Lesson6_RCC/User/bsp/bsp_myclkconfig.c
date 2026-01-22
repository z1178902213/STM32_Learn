#include "bsp_myclkconfig.h"

void MyClkconfig(){
	__IO uint32_t HSE_READY = 0;
	RCC->CR |= ((uint32_t)RCC_CR_HSEON);
	
	while(1){
		HSE_READY = RCC->CR & RCC_CR_HSERDY;
		if(HSE_READY == (0xFFFF & RCC_CR_HSERDY)){
			break;
		}
	}
	RCC->APB1ENR |= (uint32_t)(RCC_APB1ENR_PWREN);
	PWR->CR |= PWR_CR_VOS_1;
	RCC->CFGR |= RCC_CFGR_HPRE_DIV1;
	RCC->CFGR |= RCC_CFGR_PPRE2_DIV2;
	RCC->CFGR |= RCC_CFGR_PPRE1_DIV4;
	// 由于PLLCFGR中PLLP的值2、4、6、8对应00、01、10、11，所以需要搞(((2 >> 1) - 1) << 16)这么个操作才能把值弄对。
	RCC->PLLCFGR |= 25 | 336<<6 | (((2 >> 1) - 1) << 16) | 7 << 24;
	RCC->CR |= RCC_CR_PLLON;
	
	while(1){
		if((RCC->CR & RCC_CR_PLLRDY) == 0){
			break;
		}
	}

	/* Configure Flash prefetch, Instruction cache, Data cache and wait state */
	FLASH->ACR = FLASH_ACR_PRFTEN | FLASH_ACR_ICEN | FLASH_ACR_DCEN | FLASH_ACR_LATENCY_5WS;

	/* Select the main PLL as system clock source */
	RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
	RCC->CFGR |= RCC_CFGR_SW_PLL;

	/* Wait till the main PLL is used as system clock source */
	while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL)
			;
	{
	}
	
	
}

