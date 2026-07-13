#ifndef INC_TASK_H
#define INC_TASK_H

#include "FreeRTOS.h"
#include "list.h"
#include "portmacro.h"

#define tskIDLE_PRIORITY			       ( ( UBaseType_t ) 0U )
// 类型定义
typedef void (*TaskFunction_t)( void * );						// 定义任务函数，默认任务函数是一个无类型指针
typedef struct tskTaskControlBlock									// 定义了TCB，任务控制块，并重命名为TCB_t
{
	volatile 			StackType_t *pxTopOfStack;							/* 栈顶 */
	ListItem_t 		xStateListItem;													/* 任务节点 */
	StackType_t 	*pxStack;																/* 任务栈起始地址 */
	char 					pcTaskName[ configMAX_TASK_NAME_LEN ];	/* 任务名称，字符串形式 */
	TickType_t 		xTicksToDelay;													// 任务延时时间
	UBaseType_t 	uxPriority;															// 任务优先级
} tskTCB;
typedef tskTCB TCB_t;
typedef void * TaskHandle_t;												// 任务句柄

// 定义任务切换的函数，直接用portYIELD替换，portYIELD已经实现的很好了
#define taskYIELD() portYIELD()

#define taskENTER_CRITICAL()		       portENTER_CRITICAL()
#define taskENTER_CRITICAL_FROM_ISR()      portSET_INTERRUPT_MASK_FROM_ISR()

#define taskEXIT_CRITICAL()			       portEXIT_CRITICAL()
#define taskEXIT_CRITICAL_FROM_ISR( x )    portCLEAR_INTERRUPT_MASK_FROM_ISR( x )

// 任务相关函数的声明
// 创建静态任务
#if( configSUPPORT_STATIC_ALLOCATION == 1 )
TaskHandle_t xTaskCreateStatic(
											TaskFunction_t pxTaskCode,						// 任务入口函数
					            const char * const pcName,						// 任务名称
					            const uint32_t ulStackDepth,					// 任务栈大小
					            void * const pvParameters,						// 任务形参
											UBaseType_t uxPriority,
					            StackType_t * const puxStackBuffer,		// 任务栈栈底指针，任务栈起始地址指针
					            TCB_t * const pxTaskBuffer 						// 任务控制块指针
											);
#endif /* configSUPPORT_STATIC_ALLOCATION */

void prvInitialiseTaskLists( void );
void vTaskStartScheduler( void );
void vTaskSwitchContext( void );
void vTaskDelay( const TickType_t xTicksToDelay );
BaseType_t xTaskIncrementTick( void );
                                
#endif /* INC_TASK_H */ 
