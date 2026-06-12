#ifndef _BSP_ADC_H_
#define _BSP_ADC_H_

#include "stm32f4xx.h"
#define ADC_CDR_ADDR ((uint32_t)0x40012308)

void init_adc_1ch(void);
void Rheostat_adc_nvic_config(void);
void init_adc_3adc(void);

#endif

