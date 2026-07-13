#include "FreeRTOS.h"
#include "task.h"

#define TASK1_STACK_SIZE 128
#define TASK2_STACK_SIZE 128
TaskHandle_t Task1_Handle;
TaskHandle_t Task2_Handle;
StackType_t Task1Stack[TASK1_STACK_SIZE];
StackType_t Task2Stack[TASK2_STACK_SIZE];
TCB_t Task1TCB;
TCB_t Task2TCB;

uint32_t flag1;
uint32_t flag2;

extern List_t pxReadyTasksLists[ configMAX_PRIORITIES ];

void delay(uint32_t ms){
	uint32_t i = ms;
	for(; i>0; i--);
}

void Task1_Entry(){
	while(1){
		flag1 = 1;
		delay(1000);
		flag1 = 0;
		delay(1000);
		taskYIELD();
	}
}

void Task2_Entry(){
	while(1){
		flag2 = 1;
		delay(1000);
		flag2 = 0;
		delay(1000);
		taskYIELD();
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
																		(StackType_t *)Task1Stack,
																		(TCB_t *) &Task1TCB);
	Task2_Handle = xTaskCreateStatic((TaskFunction_t) Task2_Entry,
																		(char *)"Task2",
																		(uint32_t)TASK2_STACK_SIZE,
																		(void *)NULL,
																		(StackType_t *)Task2Stack,
																		(TCB_t *) &Task2TCB);
	vListInsertEnd(&(pxReadyTasksLists[1]), &( ((TCB_t *)(&Task1TCB))->xStateListItem ));
	vListInsertEnd(&(pxReadyTasksLists[2]), &( ((TCB_t *)(&Task2TCB))->xStateListItem ));
	
	// 启动调度器，就是启动任务了。
	vTaskStartScheduler();
	
	while(1){
//		Task1_Entry();
//		Task2_Entry();
	}
}

