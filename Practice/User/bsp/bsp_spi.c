#include "bsp_spi.h"
#include "bsp_usart.h"

void spi_flash_write_enable(){
	GPIO_ResetBits(GPIOG, GPIO_Pin_6);
	spi_flash_sendbyte(0x06);
	GPIO_SetBits(GPIOG, GPIO_Pin_6);
}

void spi_flash_wait_write_end(){
	uint8_t flash_status = 0;
	
	GPIO_ResetBits(GPIOG, GPIO_Pin_6);
	spi_flash_sendbyte(0x05);
	
	do{
		flash_status = spi_flash_sendbyte(0xff);
	}while((flash_status&0x01) == SET);
	
	GPIO_SetBits(GPIOG, GPIO_Pin_6);
	
}

void spi_flash_erise_sector(uint32_t sector_addr){
	// 先发送FLASH写使能指令并等待
	spi_flash_write_enable();
	spi_flash_wait_write_end();
	// 待完成FLASH写使能指令后，再发送起始信号
	GPIO_ResetBits(GPIOG, GPIO_Pin_6);
	
	spi_flash_sendbyte(0x20);
	spi_flash_sendbyte((sector_addr & 0xff0000) >> 16);
	spi_flash_sendbyte((sector_addr & 0xff00) >> 8);
	spi_flash_sendbyte(sector_addr & 0xff);
	
	GPIO_SetBits(GPIOG, GPIO_Pin_6);
	// 等待擦除完毕
	spi_flash_wait_write_end();
}

void spi_flash_buffer_read(uint8_t* pBuffer, uint32_t addr, uint16_t numByte){
	GPIO_ResetBits(GPIOG, GPIO_Pin_6);
	
	spi_flash_sendbyte(0x03);
	spi_flash_sendbyte((addr & 0xff0000) >> 16);
	spi_flash_sendbyte((addr & 0xff00) >> 8);
	spi_flash_sendbyte(addr & 0xff);
	
	while(numByte--){
		*pBuffer = spi_flash_sendbyte(0xff);
		pBuffer++;
	}
	
	GPIO_SetBits(GPIOG, GPIO_Pin_6);
}

uint32_t spi_flash_read_id(){
	uint32_t rec;
	uint32_t tmp1, tmp2, tmp3;
	
	GPIO_ResetBits(GPIOG, GPIO_Pin_6);
	spi_flash_sendbyte(0x9F);
	
	tmp1 = spi_flash_sendbyte(0xFF);
	tmp2 = spi_flash_sendbyte(0xFF);
	tmp3 = spi_flash_sendbyte(0xFF);
	GPIO_SetBits(GPIOG, GPIO_Pin_6);
	rec = (tmp1<<16) | (tmp2<<8) | (tmp3);
	
	return rec;
}

void init_spi_flash(){
	// 开时钟总线（SPI总线时钟、SPI所在GPIOB时钟、GPIOG时钟）
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);
	
	// 配置GPIO复用情况
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource3, GPIO_AF_SPI1);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource4, GPIO_AF_SPI1);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource5, GPIO_AF_SPI1);
	
	// 初始化GPIO的3、4和5
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	// 注意！这里要设置成PP模式，否则没有值
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	
	// 初始化GPIO的PG6
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_Init(GPIOG, &GPIO_InitStruct);
	GPIO_SetBits(GPIOG, GPIO_Pin_6);
		
	// 初始化SPI总线并使能
	SPI_InitTypeDef SPI_InitStruct;
	SPI_InitStruct.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStruct.SPI_Mode = SPI_Mode_Master;
	SPI_InitStruct.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStruct.SPI_CPOL = SPI_CPOL_High;
	SPI_InitStruct.SPI_CPHA = SPI_CPHA_2Edge;
	SPI_InitStruct.SPI_NSS = SPI_NSS_Soft;
	SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
	SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStruct.SPI_CRCPolynomial = 7;
	SPI_Init(SPI1, &SPI_InitStruct);
	SPI_Cmd(SPI1, ENABLE);
}

uint16_t spi_flash_sendbyte(u8 byte){
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
	SPI_I2S_SendData(SPI1, byte);
	
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
	return SPI_I2S_ReceiveData(SPI1);
}

uint16_t spi_flash_readbyte(){
	return spi_flash_sendbyte(0xFF);
}




void spi_flash_page_write(uint8_t* pBuffer, uint32_t addr, uint16_t numByte){
	// ！！！！！！！！要先写使能，并等待，然后才是开始启动信号，这里要特别注意！！！！！！！！
	spi_flash_write_enable();
	spi_flash_wait_write_end();

	GPIO_ResetBits(GPIOG, GPIO_Pin_6);
	
	spi_flash_sendbyte(0x02);
	spi_flash_sendbyte((addr & 0xff0000) >> 16);
	spi_flash_sendbyte((addr & 0xff00) >> 8);
	spi_flash_sendbyte(addr & 0xff);
	
	if(numByte > SPI_FLASH_PAGE_SIZE){
		printf("--> 超过了页可写的范围，仅写入页大小\n");
		numByte = SPI_FLASH_PAGE_SIZE;
	}
	
	while(numByte--){
		spi_flash_sendbyte(*pBuffer);
		pBuffer++;
	}
	
	GPIO_SetBits(GPIOG, GPIO_Pin_6);
	
	spi_flash_wait_write_end();
}

void spi_flash_buffer_write(u8 *pBuffer, u32 writeAddr, u16 numByteToWrite){
	uint8_t addr, pageNum, count, pageLast;
	
	// 第一页要写多少数据进去
	addr = writeAddr % SPI_FLASH_PAGE_SIZE;
	count = SPI_FLASH_PAGE_SIZE - addr;
	
	// 如果不止一页，那后面还要写多少页的数据
	pageNum = numByteToWrite / SPI_FLASH_PAGE_SIZE;
	
	// 如果最后一页不是完整的一页，那看看还有多少数据
	pageLast = numByteToWrite % SPI_FLASH_PAGE_SIZE;
	
	// 一开始页地址对齐的情况
	if(addr == 0){
		// 不满一页的情况，而且还全部对齐了，那就直接全部写入
		if(pageNum == 0){
			spi_flash_page_write(pBuffer, writeAddr, numByteToWrite);
		}
		// 超出一页了，那就分多次写入
		else{
			// 完整的页先写
			while(pageNum--){
				spi_flash_page_write(pBuffer, writeAddr, SPI_FLASH_PAGE_SIZE);
				pBuffer += SPI_FLASH_PAGE_SIZE;
				writeAddr += SPI_FLASH_PAGE_SIZE;
			}
			
			// 剩下残缺的一页直接写入
			if(pageLast != 0){
				spi_flash_page_write(pBuffer, writeAddr, pageLast);
			}
		}
	}
	// 开始页不对齐
	else{
		// 不满一页的情况，先看看剩下的空间够不够写
		if(pageNum == 0){
			// 写得完
			if(count > pageLast){
				spi_flash_page_write(pBuffer, writeAddr, numByteToWrite);
			}
			// 写不完，先把够写的写了，然后剩下的再写进去
			else{
				spi_flash_page_write(pBuffer, writeAddr, count);
				pBuffer += count;
				writeAddr += count;
				spi_flash_page_write(pBuffer, writeAddr, pageLast - count);
			}
		}
		// 超出一页了，那就分多次写入
		else{
			// 此时情况复杂，先把count剩下的写了，完事之后重新计算剩下的数据量，转换成页已经对齐的情况来处理的
			spi_flash_page_write(pBuffer, writeAddr, count);
			pBuffer += count;
			writeAddr += count;
			
			pageNum = (numByteToWrite - count) / SPI_FLASH_PAGE_SIZE;
			pageLast = (numByteToWrite - count) % SPI_FLASH_PAGE_SIZE;
			
			// 完整的页先写
			while(pageNum--){
				spi_flash_page_write(pBuffer, writeAddr, SPI_FLASH_PAGE_SIZE);
				pBuffer += SPI_FLASH_PAGE_SIZE;
				writeAddr += SPI_FLASH_PAGE_SIZE;
			}
			
			// 剩下残缺的一页直接写入
			if(pageLast != 0){
				spi_flash_page_write(pBuffer, writeAddr, pageLast);
			}
		}
	}
}

void spi_flash_wakeup(void){
	GPIO_ResetBits(GPIOG, GPIO_Pin_6);
	spi_flash_sendbyte(0xab);
	GPIO_SetBits(GPIOG, GPIO_Pin_6);
}

uint8_t test_spi_flash(){
	u8 tx_buffer[] = "啊啊啊！我终于把SPI学完了！他妈的真的好累啊，真的好痛苦啊，终于能够学这么多了，我真的太牛了。\n";
	u8 tx_buffer_size;
	tx_buffer_size = sizeof(tx_buffer) / sizeof(*tx_buffer);
	u8 rx_buffer[tx_buffer_size];
	u32 flashId;
	
	
	init_spi_flash();
	
	flashId = spi_flash_read_id();
	printf("--> Flash ID：0x%X\n", flashId);
	
	spi_flash_erise_sector(0x00000);
	printf("--> spi flash wait ok\n");
	
	spi_flash_buffer_write(tx_buffer, 0x00000, tx_buffer_size);
	spi_flash_buffer_read(rx_buffer, 0x00000, tx_buffer_size);
	
	printf("--> 读取到的值为：%s\n", rx_buffer);
	
	return 1;
}


