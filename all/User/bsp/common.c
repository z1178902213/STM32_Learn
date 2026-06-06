#include "common.h"

__IO uint8_t tim_stop;

/* 使用之前要确保初始化了tim6 */
void delay10ms(uint32_t tick){
	tim_stop = 0;
	uint32_t i = tick;
	for(; i > 0; i--){
		while(tim_stop == 0);
		tim_stop = 0;
	}
}

