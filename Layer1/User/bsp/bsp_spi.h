#ifndef _BSP_SPI_H_
#define _BSP_SPI_H_
#include "stm32f4xx.h"
#include "bsp_usart.h"

void init_spi(void);
void init_spi_flash(void);
uint8_t spi_write_data(uint8_t data);
uint8_t spi_read_data(void);
void spi_generate_start(void);
void spi_generate_stop(void);

#endif

