#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

#define configMAX_TASK_NAME_LEN								(16)
#define configMAX_PRIORITIES									(5)
#define configSUPPORT_STATIC_ALLOCATION				1
#define configUSE_16_BIT_TICKS								0
#define configKERNEL_INTERRUPT_PRIORITY				255
#define configMAX_SYSCALL_INTERRUPT_PRIORITY	191

// 把这三个函数定义成几个中断服务函数的名称，分别对应PendSV、SysTick、SVC
#define xPortPendSVHandler   PendSV_Handler
#define xPortSysTickHandler  SysTick_Handler
#define vPortSVCHandler      SVC_Handler

#endif /* FREERTOS_CONFIG_H */
