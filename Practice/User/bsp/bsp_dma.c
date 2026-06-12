#include "bsp_dma.h"

// 使用了const定义的数据就是在FLASH里面
const uint32_t FLASH_DATA[31] = {
                                    0x01020304,0x05060708,0x090A0B0C,0x0D0E0F10,
                                    0x11121314,0x15161718,0x191A1B1C,0x1D1E1F20,
                                    0x21222324,0x25262728,0x292A2B2C,0x2D2E2F30,
                                    0x31323334,0x35363738,0x393A3B3C,0x3D3E3F40,
                                    0x41424344,0x45464748,0x494A4B4C,0x4D4E4F50,
                                    0x51525354,0x55565758,0x595A5B5C,0x5D5E5F60,
                                    0x61626364,0x65666768,0x696A6B6C,0x6D6E6F70,
                                    0x71727374,0x75767778,0x797A7B7C};
// 没用const，数据空间直接在SRAM里面
uint32_t SRAM_DATA[31];
uint8_t SRAM_SRING[15] = "DMA USART TEST!";



void init_dma2_m2m(){
	// 开启DMA的AHB1总线时钟（这里就是要用RCC_AHB1PeriphClockCmd开启时钟，不能根据stm32f4xx_dma.c写的RCC_AHB1PeriphResetCmd来初始化）
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);
	// 先复位DMA
	DMA_DeInit(DMA2_Stream0);
	
	while (DMA_GetCmdStatus(DMA2_Stream0) != DISABLE)
  {
  }
	
	DMA_InitTypeDef DMA_InitTypeStruct;
	// 配置DMA使用的通道号
	DMA_InitTypeStruct.DMA_Channel = DMA_Channel_0;
	// 配置源存储器的基地址，但是这里为什么需要强转类型？
	DMA_InitTypeStruct.DMA_PeripheralBaseAddr = (uint32_t)FLASH_DATA;
	DMA_InitTypeStruct.DMA_Memory0BaseAddr = (uint32_t)SRAM_DATA;
	DMA_InitTypeStruct.DMA_DIR = DMA_DIR_MemoryToMemory;
	// 数据的长度
	DMA_InitTypeStruct.DMA_BufferSize = 31;
	DMA_InitTypeStruct.DMA_PeripheralInc = DMA_PeripheralInc_Enable;
	DMA_InitTypeStruct.DMA_MemoryInc = DMA_MemoryInc_Enable;
	// 一个单元块的数据大小，是字节、半字还是字。
	DMA_InitTypeStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word;
	DMA_InitTypeStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_Word;
	DMA_InitTypeStruct.DMA_Mode = DMA_Mode_Normal;
	// DMA的优先级？
	DMA_InitTypeStruct.DMA_Priority = DMA_Priority_High;
  /* 禁用FIFO模式 */
  DMA_InitTypeStruct.DMA_FIFOMode = DMA_FIFOMode_Disable;     
  DMA_InitTypeStruct.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
	// 单次传输
	DMA_InitTypeStruct.DMA_MemoryBurst = DMA_MemoryBurst_Single;
	DMA_InitTypeStruct.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
	// 初始化DMA
	DMA_Init(DMA2_Stream0, &DMA_InitTypeStruct);
	
	// 清除DMA传输完成的标志位
	DMA_ClearFlag(DMA2_Stream0, DMA_FLAG_TCIF0);
	
	DMA_Cmd(DMA2_Stream0, ENABLE);
	
}


uint8_t Buffercmp(const uint32_t* pBuffer, 
                  uint32_t* pBuffer1, uint16_t BufferLength)
{
  /* 数据长度递减 */
  while(BufferLength--)
  {
    /* 判断两个数据源是否对应相等 */
    if(*pBuffer != *pBuffer1)
    {
      /* 对应数据源不相等马上退出函数，并返回0 */
      return 0;
    }
    /* 递增两个数据源的地址指针 */
    pBuffer++;
    pBuffer1++;
  }
  /* 完成判断并且对应数据相对 */
  return 1;  
}

uint8_t Is_right(){
	return Buffercmp(FLASH_DATA, SRAM_DATA, 31);
}

void init_dma2_usart(){
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);
	
	DMA_DeInit(DMA2_Stream7);
	
	while (DMA_GetCmdStatus(DMA2_Stream7) != DISABLE)  {
  }
	
	DMA_InitTypeDef DMA_InitStruct;
	DMA_InitStruct.DMA_Channel = DMA_Channel_4;
	DMA_InitStruct.DMA_PeripheralBaseAddr = (USART1_BASE + 0x04);
	DMA_InitStruct.DMA_Memory0BaseAddr = (uint32_t)SRAM_SRING;
	DMA_InitStruct.DMA_DIR = DMA_DIR_MemoryToPeripheral;
	DMA_InitStruct.DMA_BufferSize = 15;
	DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	DMA_InitStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	DMA_InitStruct.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStruct.DMA_Priority = DMA_Priority_Medium;
	DMA_InitStruct.DMA_FIFOMode = DMA_FIFOMode_Disable;
	DMA_InitStruct.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
	DMA_InitStruct.DMA_MemoryBurst = DMA_MemoryBurst_Single;
	DMA_InitStruct.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
	DMA_Init(DMA2_Stream7, &DMA_InitStruct);
	
	DMA_Cmd(DMA2_Stream7, ENABLE);
	
}
