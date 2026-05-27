#ifndef _BSP_SPI_H_
#define _BSP_SPI_H_

#include "stm32f4xx.h"

#define sFLASH_ID 0xEF4018
#define SPI_FLASH_PAGE_SIZE 256


// SPI_FLASH 写使能
void spi_flash_write_enable(void);
// 等待 SPI_FLASH 完成写入
void spi_flash_wait_write_end(void);
// SPI_FLASH 擦除扇区
void spi_flash_erise_sector(uint32_t sector_addr);
// SPI_FLASH 读数据
void spi_flash_buffer_read(uint8_t* pBuffer, uint32_t addr, uint16_t numByte);
// 获取 FLASH ID
uint32_t spi_flash_read_id(void);
// 初始化 SPI_FLASH
void init_spi_flash(void);
// SPI_FLASH 发送字节（元操作）
uint16_t spi_flash_sendbyte(u8 byte);
// SPI_FLASH 读取字节（元操作）
uint16_t spi_flash_readbyte(void);
// SPI_FLASH 单页写入
void spi_flash_page_write(uint8_t* pBuffer, uint32_t addr, uint16_t numByte);
// SPI_FLASH 多页写入
void spi_flash_buffer_write(u8 *pBuffer, u32 writeAddr, u16 numByteToWrite);
// SPI_FLASH 唤醒
void spi_flash_wakeup(void);
// 测试 SPI_FLASH
uint8_t test_spi_flash(void);


#endif

