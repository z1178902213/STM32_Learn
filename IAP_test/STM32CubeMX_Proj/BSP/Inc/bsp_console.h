#ifndef __BSP_CONSOLE_H
#define __BSP_CONSOLE_H
#include "stm32f4xx.h"
#include "main.h"
#include "stm32f4xx_hal_uart.h"

#define CONSOLE_MAX_BUFFER_SIZE 0xff

typedef enum{
	Console_Command_None = 0,		// 没有收到指令
	Console_Command_WiFi,				// WiFi指令
	Console_Command_Unknown			// 未知指令
}Console_Command_Type;

typedef enum{
	CONSOLE_OK 			= 0x00U,
	CONSOLE_ERROR 	= 0x01U,
	CONSOLE_BUSY 		= 0x02U,
	CONSOLE_TIMEOUT = 0x03U
}Console_Status_Type;

Console_Command_Type Console_Get_Command(void);
Console_Command_Type Console_Parse_Command(void);
Console_Status_Type Console_Send_Data(uint8_t *pdata, uint16_t size);
Console_Status_Type Console_Readlines(void);

#endif

