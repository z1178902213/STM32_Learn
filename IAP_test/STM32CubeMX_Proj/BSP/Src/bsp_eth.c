#include "bsp_eth.h"

//extern ETH_HandleTypeDef EthHandle;

//void ETH_IRQHandler(void)
//{
//	uint32_t ulReturn;
//	/* 进入临界段，临界段可以嵌套 */
//	ulReturn = taskENTER_CRITICAL_FROM_ISR();

//	HAL_ETH_IRQHandler(&EthHandle);

//	/* 退出临界段 */
//	taskEXIT_CRITICAL_FROM_ISR( ulReturn );
//}


//extern xSemaphoreHandle s_xSemaphore;

//void HAL_ETH_RxCpltCallback(ETH_HandleTypeDef *heth)
//{
//	// LED2_TOGGLE;
//	portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;
//	xSemaphoreGiveFromISR( s_xSemaphore, &xHigherPriorityTaskWoken );
//	portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
//}
