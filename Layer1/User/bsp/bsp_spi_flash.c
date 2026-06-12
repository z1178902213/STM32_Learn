#include "bsp_spi_flash.h"

void ReadID(){
	uint8_t manufacturer_id = 0;
	uint8_t flash_id = 0;
	
	spi_generate_start();
	spi_write_data(0x90);
	spi_write_data(0x00);
	spi_write_data(0x00);
	spi_write_data(0x00);
	manufacturer_id = spi_read_data();
	flash_id = spi_read_data();
	spi_generate_stop();
	
	printf("[INFO] 读取到ManufacturerID: 0x%02X, 读取到FlashID: 0x%02X. \n", manufacturer_id, flash_id);
}

void WaitForBusy(){
	uint8_t status_register = 0;
	do{
		spi_generate_start();
		spi_write_data(0x05);
		status_register = spi_read_data();
	}while((status_register & STATUS_REGISTER_MASK_BUSY) == STATUS_REGISTER_MASK_BUSY);
	spi_generate_stop();
}

void WaitForWEL(){
	uint8_t status_register = 0;
	do{
		spi_generate_start();
		spi_write_data(0x05);
		status_register = spi_read_data();
	}while((status_register & STATUS_REGISTER_MASK_WEL) != STATUS_REGISTER_MASK_WEL);
	spi_generate_stop();
}

void WriteEnable(){
	printf("[INFO] 开启写使能...\n");
	spi_generate_start();
	spi_write_data(0x06);
	spi_generate_stop();
	WaitForWEL();
	printf("[INFO] 开启写使能成功！\n");
}

// 对SPI_FLASH进行扇区擦除，擦除4KB扇区，输入地址24位有效
void SectorErase(uint32_t address){
	
	WriteEnable();
	
	uint8_t byte2, byte3, byte4;
	byte2 = (uint8_t)((address & 0x00ff0000) >> 16);
	byte3 = (uint8_t)((address & 0x0000ff00) >> 8);
	byte4 = (uint8_t)(address & 0x000000ff);
	printf("[INFO] 解析后的地址0x%02X 0x%02X 0x%02X：\n", byte2, byte3, byte4);
	
	spi_generate_start();
	spi_write_data(0x20);
	spi_write_data(byte2);
	spi_write_data(byte3);
	spi_write_data(byte4);
	spi_generate_stop();
	printf("[INFO] 正在擦除扇区0x%08X...\n", address);
	WaitForBusy();
	printf("[INFO] 扇区擦除完成\n");
	
}

// 用于测试Fast Read功能，默认读取给定地址的前256个字节，并通过串口输出结果
void ReadBufferTest(uint32_t address){
	uint16_t i = 0;
	uint8_t data[256] = {0};
	uint8_t byte2, byte3, byte4;
	byte2 = (uint8_t)((address & 0x00ff0000) >> 16);
	byte3 = (uint8_t)((address & 0x0000ff00) >> 8);
	byte4 = (uint8_t)(address & 0x000000ff);
	printf("[INFO] 解析后的地址0x%02X 0x%02X 0x%02X：\n", byte2, byte3, byte4);
	
	spi_generate_start();
	spi_write_data(0x0b);
	spi_write_data(byte2);
	spi_write_data(byte3);
	spi_write_data(byte4);
	spi_read_data();		// 这个数据按照定义应该是空数据
	for(i = 0; i < 256; i++){
		data[i] = spi_read_data();
	}
	spi_generate_stop();
	
	printf("[INFO] 数据接收完成，给定地址后256字节数据为：\n");
	for(i = 0; i < 256; i++){
		printf("0x%02X ", data[i]);
		if((i + 1) % 16 == 0){
			printf("\n");
		}
	}
}

void ProgramPageTest(uint32_t address){
	uint16_t i = 0;
	uint8_t data[256] = {0};
	// 给data数组赋初始值
	for(i = 0; i < 256; i++){
		data[i] = i*127/256;
	}
	
	uint8_t byte2, byte3, byte4;
	byte2 = (uint8_t)((address & 0x00ff0000) >> 16);
	byte3 = (uint8_t)((address & 0x0000ff00) >> 8);
	byte4 = (uint8_t)(address & 0x000000ff);
	printf("[INFO] 解析后的地址0x%02X 0x%02X 0x%02X：\n", byte2, byte3, byte4);
	
	WriteEnable();
	
	spi_generate_start();
	spi_write_data(0x02);
	spi_write_data(byte2);
	spi_write_data(byte3);
	spi_write_data(byte4);
	for(i = 0; i < 256; i++){
		spi_write_data(data[i]);
	}
	spi_generate_stop();
	
	printf("[INFO] 数据写入完成，写入的256字节数据为：\n");
	for(i = 0; i < 256; i++){
		printf("0x%02X ", data[i]);
		if((i + 1) % 16 == 0){
			printf("\n");
		}
	}
}


