#ifndef _BSP_EPPROM_H_
#define _BSP_EPPROM_H_
#include "stm32f4xx.h"
#include "bsp_iic.h"

void init_epprom(void);
void epprom_write_byte_test(void);
void epprom_read_byte_test(void);


#endif

