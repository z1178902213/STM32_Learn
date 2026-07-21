#include "user_hal_callback.h"

extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart3;
extern DMA_HandleTypeDef hdma_usart1_tx;
extern DMA_HandleTypeDef hdma_usart1_rx;
extern DMA_HandleTypeDef hdma_usart3_rx;
extern DMA_HandleTypeDef hdma_usart3_tx;

extern uint8_t console_tx_complete;
extern uint8_t console_rx_complete;
extern uint32_t console_rx_buf_size;

extern uint8_t wifi_tx_complete;
extern uint8_t wifi_rx_complete;
extern uint32_t wifi_rx_buf_size;

// 数据发送完成的回调函数
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart){
	if(huart == &huart1){
		console_tx_complete = 1;
	}else if(huart == &huart3){
		wifi_tx_complete = 1;
	}
}

// 数据接收完成的回调函数
void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size){
//	// 接受完的回调函数，判断是空闲
//	HAL_UART_RxEventTypeTypeDef rxStatue = HAL_UARTEx_GetRxEventType(huart);
//	if(rxStatue == HAL_UART_RXEVENT_IDLE){
//		if(Size > 0){
//			if(huart == &huart1){
//				console_rx_buf_size = Size;
//				console_rx_complete = 1;
//			}else if(huart == &huart3){
//				wifi_rx_buf_size = Size;
//				wifi_rx_complete = 1;
//			}
//		}
//	}else if(rxStatue == HAL_UART_RXEVENT_TC){		// 如果是接收溢出了的处理方案
//		
//	}else if(rxStatue == HAL_UART_RXEVENT_HT){		// 如果是半满了的处理办法
//		
//	}
}

