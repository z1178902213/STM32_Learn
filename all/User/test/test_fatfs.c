#include "test.h"
#include <stdio.h>
#include "ff.h"

#define MKFS_WORK_SIZE 4096
BYTE work_buf[MKFS_WORK_SIZE];

FATFS fs;
FIL fnew;
FRESULT res_flash;
UINT fnum;
BYTE ReadBuffer[1024] = {0};
BYTE WriteBuffer[] = "哈哈哈，现在学习效率好高啊，3小时完成fatfs的学习。\r\n";

void test_fatfs_file(){
	res_flash = f_mount(&fs, "1:", 1);
	
	if(res_flash == FR_NO_FILESYSTEM){
		printf("--> [info] FLASH 还没有文件系统，即将进行格式化... \r\n");
		
		res_flash = f_mkfs("1:", NULL, work_buf, MKFS_WORK_SIZE);
		
		if(res_flash == FR_OK){
			printf("--> [success] FLASH 成功初始化。\r\n");
			res_flash = f_mount(NULL, "1:", 1);			// 取消挂载
			res_flash = f_mount(&fs, "1:", 1);			// 重新挂载
		}else{
			printf("--> [error] FLASH 格式化失败。系统停止运行。\r\n");
			while(1);
		}
	}else if(res_flash != FR_OK){
		printf("--> [error] 外部FLASH挂载文件失败。{%d}\r\n", res_flash);
		printf("--> [info] 可能原因：SPI FLASH 初始化不成功。\r\n");
		while(1);
	}else{
		printf("--> [success] 文件系统挂载成功，可以进行读写测试。\r\n");
	}
	
	// =======================写测试========================
	printf("--> [info] 即将进行文件写入测试。\r\n");
	
	res_flash = f_open(&fnew, "1:FatFs 读写测试文件.txt", FA_CREATE_ALWAYS|FA_WRITE);
	if(res_flash == FR_OK){
		printf("--> [success] 打开/创建 FatFs 读写测试文件.txt 文件成功，即将向文件写入数据。\r\n");
		res_flash = f_write(&fnew, WriteBuffer, sizeof(WriteBuffer), &fnum);
		if(res_flash == FR_OK){
			printf("--> [success] 文件写入成功，写入字节数据：%d\n", fnum);
			printf("--> [success] 向文件写入的数据为：\r\n%s\r\n", WriteBuffer);
		}else{
			printf("--> [error] 文件写入失败：{%d}\n", res_flash);
		}
		
		f_close(&fnew);
	}else{
		printf("--> [error] 打开/创建文件失败。\r\n");
	}
	
	// ========================读测试==========================
	printf("--> [info] 即将进行文件读取测试。\r\n");
	
	res_flash = f_open(&fnew, "1:FatFs 读写测试文件.txt", FA_OPEN_EXISTING|FA_READ);
	if(res_flash == FR_OK){
		printf("--> [success] 打开 FatFs 读写测试文件.txt 文件成功。\r\n");
		res_flash = f_read(&fnew, ReadBuffer, sizeof(ReadBuffer), &fnum);
		if(res_flash == FR_OK){
			printf("--> [success] 文件读取成功，读取到的字节数据：%d\n", fnum);
			printf("--> [success] 读得的文件数据为：\r\n%s\r\n", ReadBuffer);
		}else{
			printf("--> [error] 文件读取失败：{%d}\n", res_flash);
		}
	}else{
		printf("--> [error] 打开文件失败。\r\n");
	}
	
	f_close(&fnew);
	f_mount(NULL, "1:", 1);
}


