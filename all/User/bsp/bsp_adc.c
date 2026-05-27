#include "bsp_adc.h"

__IO uint32_t ADC_ConvertedValue[3];

void init_adc_1ch(){
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	
	// ADC通用的配置项
	ADC_CommonInitTypeDef ADC_CommonInitStruct;
	ADC_CommonInitStruct.ADC_Mode = ADC_Mode_Independent;
	ADC_CommonInitStruct.ADC_Prescaler = ADC_Prescaler_Div4;
	ADC_CommonInitStruct.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
	ADC_CommonInitStruct.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_10Cycles;
	ADC_CommonInit(&ADC_CommonInitStruct);
	
	// ADC1针对性配置
	ADC_InitTypeDef ADC_InitStruct;
	ADC_InitStruct.ADC_Resolution = ADC_Resolution_12b;
	ADC_InitStruct.ADC_ScanConvMode = DISABLE;
	ADC_InitStruct.ADC_ContinuousConvMode = ENABLE;
	ADC_InitStruct.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
	ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStruct.ADC_NbrOfConversion = 1;
	ADC_Init(ADC1, &ADC_InitStruct);
	
	// ADC通道配置
	ADC_RegularChannelConfig(ADC1, ADC_Channel_8, 1, ADC_SampleTime_480Cycles);
	ADC_ITConfig(ADC1, ADC_IT_EOC, ENABLE);
	ADC_Cmd(ADC1, ENABLE);
	ADC_SoftwareStartConv(ADC1);
}

void Rheostat_adc_nvic_config()
{
	NVIC_InitTypeDef NVIC_InitStruct;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	NVIC_InitStruct.NVIC_IRQChannel = ADC_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	
	NVIC_Init(&NVIC_InitStruct);
}

void init_adc_3adc(){

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);

	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOC, &GPIO_InitStruct);

	DMA_InitTypeDef DMA_InitStruct;
	DMA_InitStruct.DMA_PeripheralBaseAddr = ADC_CDR_ADDR;
	DMA_InitStruct.DMA_Memory0BaseAddr = (uint32_t)ADC_ConvertedValue;
	DMA_InitStruct.DMA_Channel = DMA_Channel_0;
	DMA_InitStruct.DMA_DIR = DMA_DIR_PeripheralToMemory;
	DMA_InitStruct.DMA_BufferSize = 3;
	DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_Word;
	DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word;
	DMA_InitStruct.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStruct.DMA_Priority = DMA_Priority_High;
	DMA_InitStruct.DMA_FIFOMode = DMA_FIFOMode_Disable;
	DMA_Init(DMA2_Stream0, &DMA_InitStruct);
	DMA_Cmd(DMA2_Stream0, ENABLE);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC3, ENABLE);
	
	ADC_CommonInitTypeDef ADC_CommonInitStruct;
	ADC_CommonInitStruct.ADC_Mode = ADC_TripleMode_Interl;
	
	// ??? 这个ADC_DMAAccessMode在教程里面说要禁止，很抽象，我禁止了就不能用，开起来以后就能用了，有点sb。
	ADC_CommonInitStruct.ADC_DMAAccessMode = ADC_DMAAccessMode_2;
	ADC_CommonInitStruct.ADC_Prescaler = ADC_Prescaler_Div4;
	ADC_CommonInitStruct.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_20Cycles;
	ADC_CommonInit(&ADC_CommonInitStruct);
	
	ADC_InitTypeDef ADC_InitStruct;
	ADC_InitStruct.ADC_Resolution = ADC_Resolution_12b;
	ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;
	ADC_InitStruct.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
	ADC_InitStruct.ADC_ScanConvMode = DISABLE;
	ADC_InitStruct.ADC_ContinuousConvMode = ENABLE;
	ADC_InitStruct.ADC_NbrOfConversion = 1;
	ADC_Init(ADC1, &ADC_InitStruct);
	ADC_Init(ADC2, &ADC_InitStruct);
	ADC_Init(ADC3, &ADC_InitStruct);
	
	ADC_RegularChannelConfig(ADC1, ADC_Channel_12, 1, ADC_SampleTime_3Cycles);
	ADC_RegularChannelConfig(ADC2, ADC_Channel_12, 1, ADC_SampleTime_3Cycles);
	ADC_RegularChannelConfig(ADC3, ADC_Channel_12, 1, ADC_SampleTime_3Cycles);
	ADC_MultiModeDMARequestAfterLastTransferCmd(ENABLE);
	ADC_DMACmd(ADC1, ENABLE);
	
	ADC_Cmd(ADC1, ENABLE);
	ADC_Cmd(ADC2, ENABLE);
	ADC_Cmd(ADC3, ENABLE);
	
	ADC_SoftwareStartConv(ADC1);
}
