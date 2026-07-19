#include "bsp_led.h"
#include "bsp_console.h"
#include "bsp_wifi.h"
#include "user_task.h"
#include "FreeRTOS.h"
#include "task.h"

#define CONSOLE_LEVEL_INFO (0x01 << 0)
#define CONSOLE_LEVEL_WARNING (0x01 << 1)
#define CONSOLE_LEVEL_ERROR (0x01 << 2)

TaskHandle_t APP_Create_Task_Handler = NULL;
TaskHandle_t LED_Red_Blink_Task_Handler = NULL;
TaskHandle_t UART1_Test_Tx_Task_Handler = NULL;
TaskHandle_t Console_Wait_Command_Task_Handler = NULL;
TaskHandle_t Console_Log_Task_Handler = NULL;
Console_Log_Task_Params_Type Console_Log_Task_Param;

static void APP_Create_Task(void);
static void LED_Red_Blink_Task(void);
static void Console_Wait_Command_Task(void);

extern UART_HandleTypeDef huart1;
extern uint8_t console_tx_complete;
extern uint8_t console_rx_buffer[];
extern uint8_t console_rx_complete;
extern uint32_t console_rx_buf_size;
extern uint8_t wifi_tx_complete;
extern uint8_t wifi_rx_buffer[];
extern uint8_t wifi_rx_complete;
extern uint32_t wifi_rx_buf_size;

void User_Start_Tasks(){
	xTaskCreate(
							(TaskFunction_t) APP_Create_Task,
							"APP_Create_Task",
							configMINIMAL_STACK_SIZE,
							NULL,
							4,
							&APP_Create_Task_Handler);
	
	vTaskStartScheduler();
}

static void APP_Create_Task(){
	// 创建LED闪烁的任务
	xTaskCreate(
							(TaskFunction_t) LED_Red_Blink_Task,
							"LED_Red_Blink_Task",
							configMINIMAL_STACK_SIZE,
							NULL,
							2,
							&LED_Red_Blink_Task_Handler);
	
	// 创建获取控制台输入的任务
	xTaskCreate(
							(TaskFunction_t) Console_Wait_Command_Task,
							"Console_Wait_Command_Task",
							configMINIMAL_STACK_SIZE,
							NULL,
							3,
							&Console_Wait_Command_Task_Handler);
	
	// 删除创建任务的任务
	vTaskDelete(APP_Create_Task_Handler);
}


static void LED_Red_Blink_Task(){
	while(1){
		LED_Toggle(LED_R_GPIO_Port, LED_R_Pin);
		vTaskDelay(500);
		LED_Toggle(LED_R_GPIO_Port, LED_R_Pin);
		vTaskDelay(500);
		LED_Toggle(LED_G_GPIO_Port, LED_G_Pin);
		vTaskDelay(500);
		LED_Toggle(LED_G_GPIO_Port, LED_G_Pin);
		vTaskDelay(500);
		LED_Toggle(LED_B_GPIO_Port, LED_B_Pin);
		vTaskDelay(500);
		LED_Toggle(LED_B_GPIO_Port, LED_B_Pin);
		vTaskDelay(500);
	}
}



// ===============================================================================================
// 功能：Console_Get_Command_Task任务，通过控制台接收上位机发送的命令
// 使用方式：无需手动调用，该任务每隔100ms就会检查上位机是否有指令发送，并且会自动匹配指令的相关功能
// ===============================================================================================
static void Console_Wait_Command_Task(){
	Console_Command_Type cmdType;		// 收到的指令类型
	Console_Status_Type cStatus; 
	char *msg;											// 通过控制台输出的消息
	while(1){
		cStatus = Console_Readlines();
		if(cStatus == CONSOLE_OK){
			Wait_Tx_Rx(&console_rx_complete, 100);
			
			cmdType = Console_Parse_Command();
			if(cmdType == Console_Command_WiFi){
				WIFI_Send_Command(console_rx_buffer, console_rx_buf_size);
				Wait_Tx_Rx_Forever(&wifi_tx_complete);		// 和WiFi有关的操作，不知道为什么不能让任务调度，一调度就不能用
				
				WIFI_Receive_Message();
				Wait_Tx_Rx_Forever(&wifi_rx_complete);		// 和WiFi有关的操作，不知道为什么不能让任务调度，一调度就不能用

				Console_Send_Data(wifi_rx_buffer, wifi_rx_buf_size);
				Wait_Tx_Rx(&console_tx_complete, 100);
				
			}else if(cmdType == Console_Command_Unknown){
				msg = "==> error: 未知指令，无操作\n";
				Console_Send_Data((uint8_t*)msg, 0);
				Wait_Tx_Rx(&console_tx_complete, 100);
			}
		}
	}
}

// 等待发送或者接收，完事会清除标志位
void Wait_Tx_Rx(uint8_t *flag, uint32_t delayTime){
	while(*flag != 1){
		vTaskDelay(delayTime);
	}
	*flag = 0;
}
// 一直死循环，等待发送或者接收，完事会清除标志位
void Wait_Tx_Rx_Forever(uint8_t *flag){
	while(*flag != 1);
	*flag = 0;
}

