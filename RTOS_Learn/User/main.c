#include "FreeRTOS.h"
#include "task.h"

#define TASK1_STACK_SIZE 128
#define TASK2_STACK_SIZE 128
#define TASK3_STACK_SIZE 128
TaskHandle_t Task1_Handle;
TaskHandle_t Task2_Handle;
TaskHandle_t Task3_Handle;
StackType_t Task1Stack[TASK1_STACK_SIZE];
StackType_t Task2Stack[TASK2_STACK_SIZE];
StackType_t Task3Stack[TASK2_STACK_SIZE];
StackType_t IdleTaskStack[configMINIMAL_STACK_SIZE];
TCB_t Task1TCB;
TCB_t Task2TCB;
TCB_t Task3TCB;
TCB_t IdleTaskTCB;

uint32_t flag1;
uint32_t flag2;
uint32_t flag3;

extern List_t pxReadyTasksLists[ configMAX_PRIORITIES ];

void delay(uint32_t ms){
	uint32_t i = ms;
	for(; i>0; i--);
}

void Task1_Entry(){
	while(1){
		flag1 = 1;
		delay(100);
		flag1 = 0;
		delay(100);
	}
}

void Task2_Entry(){
	while(1){
		flag2 = 1;
		delay(100);
		flag2 = 0;
		delay(100);
	}
}

void Task3_Entry(){
	while(1){
		flag3 = 1;
		vTaskDelay(10);
		flag3 = 0;
		vTaskDelay(10);
	}
}

int main(){
	// 初始化任务就绪列表
	prvInitialiseTaskLists();
	
	// 创建任务
	Task1_Handle = xTaskCreateStatic((TaskFunction_t) Task1_Entry,
																		(char *)"Task1",
																		(uint32_t)TASK1_STACK_SIZE,
																		(void *)NULL,
																		(UBaseType_t) 2,						// 任务优先级
																		(StackType_t *)Task1Stack,
																		(TCB_t *) &Task1TCB);
	Task2_Handle = xTaskCreateStatic((TaskFunction_t) Task2_Entry,
																		(char *)"Task2",
																		(uint32_t)TASK2_STACK_SIZE,
																		(void *)NULL,
																		(UBaseType_t) 2,						// 任务优先级
																		(StackType_t *)Task2Stack,
																		(TCB_t *) &Task2TCB);
	Task3_Handle = xTaskCreateStatic((TaskFunction_t) Task3_Entry,
																		(char *)"Task3",
																		(uint32_t)TASK3_STACK_SIZE,
																		(void *)NULL,
																		(UBaseType_t) 3,						// 任务优先级
																		(StackType_t *)Task3Stack,
																		(TCB_t *) &Task3TCB);
	// 启动调度器，就是启动任务了。
	vTaskStartScheduler();
	
	while(1){
		
	}
}

// 获取空闲任务内存
void vApplicationGetIdleTaskMemory( TCB_t **ppxIdleTaskTCBBuffer, 
                                    StackType_t **ppxIdleTaskStackBuffer, 
                                    uint32_t *pulIdleTaskStackSize )
{
		*ppxIdleTaskTCBBuffer=&IdleTaskTCB;
		*ppxIdleTaskStackBuffer=IdleTaskStack; 
		*pulIdleTaskStackSize=configMINIMAL_STACK_SIZE;
}
