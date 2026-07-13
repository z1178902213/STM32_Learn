#ifndef INC_TASK_H
#define INC_TASK_H

#include "list.h"
#include "portmacro.h"

typedef void (*TaskFunction_t)( void * );

// 定义了TCB，任务控制块，并重命名为TCB_t
typedef struct tskTaskControlBlock
{
	volatile StackType_t *pxTopOfStack;								/* 栈顶 */
	ListItem_t xStateListItem;												/* 任务节点 */
	StackType_t *pxStack;															/* 任务栈起始地址 */
	char pcTaskName[ configMAX_TASK_NAME_LEN ];				/* 任务名称，字符串形式 */
} tskTCB;
typedef tskTCB TCB_t;

// 任务句柄
typedef void * TaskHandle_t;

#define taskYIELD()			portYIELD()

// 创建静态任务
#if( configSUPPORT_STATIC_ALLOCATION == 1 )
TaskHandle_t xTaskCreateStatic(
											TaskFunction_t pxTaskCode,						// 任务入口函数
					            const char * const pcName,						// 任务名称
					            const uint32_t ulStackDepth,					// 任务栈大小
					            void * const pvParameters,						// 任务形参
					            StackType_t * const puxStackBuffer,		// 任务栈栈底指针，任务栈起始地址指针
					            TCB_t * const pxTaskBuffer 						// 任务控制块指针
											);
#endif /* configSUPPORT_STATIC_ALLOCATION */
											
// 
static void prvInitialiseNewTask( 	TaskFunction_t pxTaskCode,              /* 任务入口 */
									const char * const pcName,              /* 任务名称，字符串形式 */
									const uint32_t ulStackDepth,            /* 任务栈大小，单位为字 */
									void * const pvParameters,              /* 任务形参 */
									TaskHandle_t * const pxCreatedTask,     /* 任务句柄 */
									TCB_t *pxNewTCB );                       /* 任务控制块指针 */
											
void prvInitialiseTaskLists( void );
void vTaskStartScheduler( void );
void vTaskSwitchContext( void );
                                
#endif /* INC_TASK_H */ 
