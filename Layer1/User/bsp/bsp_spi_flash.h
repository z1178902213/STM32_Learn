#ifndef _BSP_SPI_FLASH_H_
#define _BSP_SPI_FLASH_H_
#include "stm32f4xx.h"
#include "common.h"
#include "bsp_spi.h"
#include "bsp_usart.h"

// STATUS_REGISTER_MASK 
#define STATUS_REGISTER_MASK_BUSY 0x00000001
#define STATUS_REGISTER_MASK_WEL 0x00000002
#define STATUS_REGISTER_MASK_BP0 0x00000004
// ......
// ...后续还有很多，懒得补充了，又用不上

void ReadID(void);
void WaitForWEL(void);
void WaitForBusy(void);
void SectorErase(uint32_t address);
void ReadBufferTest(uint32_t address);
void ProgramPageTest(uint32_t address);
void CompareData(uint32_t address);


#endif

