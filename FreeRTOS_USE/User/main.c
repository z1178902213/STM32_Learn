#include "FreeRTOS.h"
#include "stm32f4xx.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "event_groups.h"
#include "timers.h"
#include "bsp_led.h"
#include "bsp_key.h"
#include "bsp_usart.h"

/* ********************* */
/* *****  宏定义  ****** */
/* ********************* */
#define LED_GREEN ((uint8_t)0x00)
#define LED_BLUE ((uint8_t)0x01)

/* ************************** */
/* *****  全局变量声明  ****** */
/* ************************** */
// 静态模式下，给空闲任务创建的任务栈和TCB，Timer是软件计时器，目前还没开，先给定义了得了。
static StackType_t Idle_Task_Stack[configMINIMAL_STACK_SIZE];
static StaticTask_t Idle_Task_TCB;
static StackType_t Timer_Task_Stack[configTIMER_TASK_STACK_DEPTH];
static StaticTask_t Timer_Task_TCB;

//static StackType_t AppStaticTaskCreate_Stack[configMINIMAL_STACK_SIZE];
//static StaticTask_t AppStaticTaskCreate_TCB;
//TaskHandle_t AppStaticTaskCreate_Handle;

//static StackType_t LED_RED_TASK_Stack[configMINIMAL_STACK_SIZE];
//static StaticTask_t LED_RED_TASK_TCB;


// 动态任务模式下，配置全局变量
static TaskHandle_t AppDynamicTaskCreate_Handle = NULL;
static TaskHandle_t LED_GREEN_TASK_Handle = NULL;
static TaskHandle_t KEY1_TASK_Handle = NULL;
static TaskHandle_t KEY2_TASK_Handle = NULL;
uint8_t is_led_red_task_running = 0;
uint8_t is_led_green_task_running = 0;
uint8_t is_system_pause = 0;
//QueueHandle_t LED_Semaphore_Handle = NULL;
//SemaphoreHandle_t LED_Mutex_Semaphore_Handle = NULL;
EventGroupHandle_t LED_Event_Group_Handle = NULL;
TimerHandle_t LED_Timer_Handle = NULL;
uint8_t LED_COLOR = LED_GREEN;

/* ********************** */
/* *****  函数声明  ****** */
/* ********************** */
void BSP_Init(void);
void delay500ms(void);
//static void LED_RED_TASK(void);
static void LED_GREEN_TASK(void);
static void KEY1_TASK(void);
static void KEY2_TASK(void);
//static void AppStaticTaskCreate(void);
static void AppDynamicTaskCreate(void);
void vApplicationGetIdleTaskMemory(StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize);
void vApplicationGetTimerTaskMemory(StaticTask_t **ppxTimerTaskTCBBuffer, StackType_t **ppxTimerTaskStackBuffer, uint32_t *pulTimerTaskStackSize);
static void LED_Color_Change(void);

/* ********************** */
/* *****  函数定义  ****** */
/* ********************** */

int main(void){
	uint32_t* LED_Timer_ID;
	BSP_Init();
	
	BaseType_t xReturen = xTaskCreate((TaskFunction_t) AppDynamicTaskCreate,
																	(const char*) "AppDynamicTaskCreate",
																	(uint32_t) configMINIMAL_STACK_SIZE,
																	NULL,
																	(UBaseType_t) 31,
																	(TaskHandle_t *) &AppDynamicTaskCreate_Handle);
	
//	LED_Semaphore_Handle = xSemaphoreCreateCounting(50, 0);
//	LED_Mutex_Semaphore_Handle = xSemaphoreCreateMutex();
	LED_Event_Group_Handle = xEventGroupCreate();
	LED_Timer_Handle = xTimerCreate("LED_Timer", 1000, pdTRUE, LED_Timer_ID, (TimerCallbackFunction_t)LED_Color_Change);		
																	
	if(LED_Event_Group_Handle == NULL){
		printf("[ERROR] LED事件组创建失败！\n");
	}else{
		printf("[SUCCESS] LED事件组创建成功！\n");
	}
	
	if(LED_Timer_Handle == NULL){
		printf("[ERROR] 定时器创建失败！\n");
	}else{
		printf("[SUCCESS] 定时器创建成功！\n");
		xTimerStart(LED_Timer_Handle, 0);
	}
	
	if(xReturen == pdPASS)
	{
		vTaskStartScheduler();
	}else{
		return -1;
	}

	while(1){
		
	}
}

void BSP_Init(){
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
	
	init_led();
	init_key();
	turn_off_red();
	turn_off_green();
	turn_off_blue();
	
	init_usart1();
}

//static void AppStaticTaskCreate(){
//	taskENTER_CRITICAL();
//	LED_RED_TASK_Handle = xTaskCreateStatic(
//																				(TaskFunction_t) LED_RED_TASK,
//																				(const char*) "LED_RED_TASK",
//																				(uint32_t) configMINIMAL_STACK_SIZE,
//																				NULL,
//																				(UBaseType_t) 2,
//																				(StackType_t*) LED_RED_TASK_Stack,
//																				(StaticTask_t*) &LED_RED_TASK_TCB);
//	if(LED_RED_TASK_Handle == NULL){
//		printf("[ERROR] LED任务创建失败！\n");
//	}else{
//		printf("[SUCCESS] LED任务创建成功！\n");
//	}
//	vTaskDelete(AppStaticTaskCreate_Handle);
//	
//	taskEXIT_CRITICAL();
//}

static void AppDynamicTaskCreate(){
	taskENTER_CRITICAL();
	BaseType_t xReturn;
//	xReturn = xTaskCreate(
//																				(TaskFunction_t) LED_RED_TASK,
//																				(const char*) "LED_RED_TASK",
//																				(uint32_t) configMINIMAL_STACK_SIZE,
//																				NULL,
//																				(UBaseType_t) 2,
//																				(TaskHandle_t *) &LED_RED_TASK_Handle);
//	if(xReturn == pdPASS){
//		printf("[SUCCESS] LED_RED任务创建成功！\n");
//	}else{
//		printf("[ERROR] LED_RED任务创建失败！\n");
//	}
	
	
	xReturn = xTaskCreate(
							(TaskFunction_t) LED_GREEN_TASK,
							(const char*) "LED_GREEN_TASK",
							(uint32_t) configMINIMAL_STACK_SIZE,
							NULL,
							(UBaseType_t) 2,
							(TaskHandle_t *) &LED_GREEN_TASK_Handle);
	if(xReturn == pdPASS){
		printf("[SUCCESS] LED_GREEN任务创建成功！\n");
	}else{
		printf("[ERROR] LED_GREEN任务创建失败！\n");
	}
	
	xReturn = xTaskCreate(
							(TaskFunction_t) KEY1_TASK,
							(const char*) "KEY1_TASK",
							(uint32_t) configMINIMAL_STACK_SIZE,
							NULL,
							(UBaseType_t) 2,
							(TaskHandle_t *) &KEY1_TASK_Handle);
	if(xReturn == pdPASS){
		printf("[SUCCESS] KEY1_TASK任务创建成功！\n");
	}else{
		printf("[ERROR] KEY1_TASK任务创建失败！\n");
	}
	
	xReturn = xTaskCreate(
							(TaskFunction_t) KEY2_TASK,
							(const char*) "KEY2_TASK",
							(uint32_t) configMINIMAL_STACK_SIZE,
							NULL,
							(UBaseType_t) 2,
							(TaskHandle_t *) &KEY2_TASK_Handle);
	
	if(xReturn == pdPASS){
		printf("[SUCCESS] KEY2_TASK任务创建成功！\n");
	}else{
		printf("[ERROR] KEY2_TASK任务创建失败！\n");
	}

	vTaskDelete(AppDynamicTaskCreate_Handle);
	
	taskEXIT_CRITICAL();
}

void delay500ms(){
	uint32_t i = 21454112;
	for(;i >0; i --);
}

//static void LED_RED_TASK(){
//	while(1){
//		turn_on_red();
//		vTaskDelay(500);
//		turn_off_red();
//		vTaskDelay(500);
//		is_led_red_task_running = 1;
//	}
//}

static void LED_GREEN_TASK(){
	EventBits_t xReturn;
	EventBits_t LED_Event_MASK = 0x03;
	while(1){
		xReturn = xEventGroupWaitBits(LED_Event_Group_Handle, LED_Event_MASK, pdTRUE, pdTRUE, 100);
		if((xReturn & LED_Event_MASK) == LED_Event_MASK){
			turn_off_red();
			if(LED_COLOR == LED_GREEN){
				turn_on_green();
				turn_off_blue();
			}else{
				turn_on_blue();
				turn_off_green();
			}
		}else{
			if(LED_COLOR == LED_GREEN){
				turn_off_green();
			}else{
				turn_off_blue();
			}
			turn_on_red();
		}
	}
}


static void KEY1_TASK(void){
	while(1){
		if(IS_KEY_PRESS(read_key1())){
			xEventGroupSetBits(LED_Event_Group_Handle, 0x01);
		}else{
			xEventGroupClearBits(LED_Event_Group_Handle, 0x01);
		}
	}
}

static void KEY2_TASK(void){
	while(1){
		if(IS_KEY_PRESS(read_key2())){
			xEventGroupSetBits(LED_Event_Group_Handle, 0x02);
		}else{
			xEventGroupClearBits(LED_Event_Group_Handle, 0x02);
		}
	}
}

static void LED_Color_Change(void){
	if(LED_COLOR == LED_GREEN){
		LED_COLOR = LED_BLUE;
	}else{
		LED_COLOR = LED_GREEN;
	}
}

void vApplicationGetIdleTaskMemory(StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize){
	*ppxIdleTaskStackBuffer = Idle_Task_Stack;
	*ppxIdleTaskTCBBuffer = &Idle_Task_TCB;
	*pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
}

void vApplicationGetTimerTaskMemory(StaticTask_t **ppxTimerTaskTCBBuffer, StackType_t **ppxTimerTaskStackBuffer, uint32_t *pulTimerTaskStackSize){
	*ppxTimerTaskStackBuffer = Timer_Task_Stack;
	*ppxTimerTaskTCBBuffer = &Timer_Task_TCB;
	*pulTimerTaskStackSize = configMINIMAL_STACK_SIZE;
}
