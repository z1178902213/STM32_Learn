#include "test.h"
#include "bsp_usart.h"
#include "bsp_adc.h"

extern __IO uint16_t ADC_ConvertedValue[3];
float ADC_ConvertedValueLocal[3]; 

float ADC_Vol;
uint32_t total_value = 0;
uint8_t count = 0;
uint16_t avg_value = 0;


void delay50ms(){
	uint32_t i = 2290822;
	for(;i >0; i --);
}

void delay500ms(){
	uint32_t i = 10;
	for(;i >0; i --){
		delay50ms();
	}
}

void delay2s(){
	uint32_t a = 40;
	for(; a>0; a--){
		delay50ms();
	}
}

void test_adc(){
	init_usart1();
	init_adc_3adc();
	
	printf("--> Æô¶¯ADC²âÊÔ¡£\r\n");
	while(1){
		delay2s();
		
    ADC_ConvertedValueLocal[0] =(float)((uint16_t)ADC_ConvertedValue[0]*3.3/4096); 
    ADC_ConvertedValueLocal[1] =(float)((uint16_t)ADC_ConvertedValue[1]*3.3/4096);
    ADC_ConvertedValueLocal[2] =(float)((uint16_t)ADC_ConvertedValue[2]*3.3/4096);
    
    printf("--> The current AD value = 0x%08X \r\n", ADC_ConvertedValue[0]); 
    printf("--> The current AD value = 0x%08X \r\n", ADC_ConvertedValue[1]); 
    printf("--> The current AD value = 0x%08X \r\n", ADC_ConvertedValue[2]); 
    
    printf("--> The current ADC1 value = %f V \r\n",ADC_ConvertedValueLocal[0]); 
    printf("--> The current ADC2 value = %f V \r\n",ADC_ConvertedValueLocal[1]);
    printf("--> The current ADC3 value = %f V \r\n",ADC_ConvertedValueLocal[2]);
	}
}

