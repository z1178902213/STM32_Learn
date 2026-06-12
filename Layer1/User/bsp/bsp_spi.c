#include "bsp_spi.h"

void init_spi(){
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
	
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource3, GPIO_AF_SPI1);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource4, GPIO_AF_SPI1);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource5, GPIO_AF_SPI1);
	GPIO_InitTypeDef gpio_init_struct;
	gpio_init_struct.GPIO_Pin = GPIO_Pin_3;
	gpio_init_struct.GPIO_OType = GPIO_OType_PP;
	gpio_init_struct.GPIO_Mode = GPIO_Mode_AF;
	gpio_init_struct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	gpio_init_struct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOB, &gpio_init_struct);
	gpio_init_struct.GPIO_Pin = GPIO_Pin_4;
	GPIO_Init(GPIOB, &gpio_init_struct);
	gpio_init_struct.GPIO_Pin = GPIO_Pin_5;
	GPIO_Init(GPIOB, &gpio_init_struct);
	gpio_init_struct.GPIO_Mode = GPIO_Mode_OUT;
	gpio_init_struct.GPIO_Pin = GPIO_Pin_6;
	GPIO_Init(GPIOG, &gpio_init_struct);
	GPIO_SetBits(GPIOG, GPIO_Pin_6);
	
	SPI_InitTypeDef spi_init_struct;
	spi_init_struct.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	spi_init_struct.SPI_Mode = SPI_Mode_Master;
	spi_init_struct.SPI_DataSize = SPI_DataSize_8b;
	spi_init_struct.SPI_CPOL = SPI_CPOL_Low;
	spi_init_struct.SPI_CPHA = SPI_CPHA_1Edge;
	spi_init_struct.SPI_NSS = SPI_NSS_Soft;
	spi_init_struct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_128;
	spi_init_struct.SPI_FirstBit = SPI_FirstBit_MSB;
	spi_init_struct.SPI_CRCPolynomial = 7;
	SPI_Init(SPI1, &spi_init_struct);
	SPI_Cmd(SPI1, ENABLE);
}

void spi_generate_start(){
	GPIO_ResetBits(GPIOG, GPIO_Pin_6);
}

void spi_generate_stop(){
	GPIO_SetBits(GPIOG, GPIO_Pin_6);
}

uint8_t spi_write_data(uint8_t data){
	// 这里细节还比较模糊，CPU主频是168MHz，SPI总线CLK不知道什么频率，执行spi_generate_start后等待
	// 以及SPI_SendData这中间经历了多少的时钟周期？紧跟着的SPI_ReceiveData既然能够接收到正确数据，那说明
	// 从上升沿到下降沿的时间里，已经走过了很多个CPU时钟周期了，但是有多少个周期呢？以后再研究吧。
	
	// 对于CPOL=0、CPHA=0的情况，当CLK上升沿MOSI发出信号，从机DI收到数据；下降沿MISO接收到从机DO发出的数据。
	while(SPI_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
	SPI_SendData(SPI1, data);
	while(SPI_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
	return SPI_ReceiveData(SPI1);
}

uint8_t spi_read_data(){
	return spi_write_data(0xFF);
}
