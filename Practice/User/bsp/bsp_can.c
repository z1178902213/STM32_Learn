#include "bsp_can.h"
#include "bsp_usart.h"

void init_can(){
	printf("--> ¿ªÊ±ÖÓ\n");
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN2, ENABLE);
	
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource12, GPIO_AF_CAN2);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource13, GPIO_AF_CAN2);
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_OD;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	
	CAN_InitTypeDef CAN_InitStruct;
	CAN_InitStruct.CAN_Prescaler = 6;
	CAN_InitStruct.CAN_Mode = CAN_Mode_LoopBack;
	CAN_InitStruct.CAN_SJW = CAN_SJW_2tq;
	CAN_InitStruct.CAN_BS1 = CAN_BS1_3tq;
	CAN_InitStruct.CAN_BS2 = CAN_BS2_3tq;
	CAN_InitStruct.CAN_TTCM = DISABLE;
	CAN_InitStruct.CAN_AWUM = ENABLE;
	CAN_InitStruct.CAN_ABOM = ENABLE;
	CAN_InitStruct.CAN_NART = ENABLE;
	CAN_InitStruct.CAN_RFLM = ENABLE;
	CAN_InitStruct.CAN_TXFP = ENABLE;
	CAN_Init(CAN2, &CAN_InitStruct);
	
}

void Config_Tx(CanTxMsg* can_tx){
	uint8_t i = 0;
	can_tx->StdId = 0x555;
	can_tx->IDE = CAN_Id_Standard;
	can_tx->DLC = 8;
	can_tx->RTR = CAN_RTR_Data;
	for(i = 0; i < 8; i++){
		can_tx->Data[i] = 2*i;
	}
}

void Init_Can2_NVIC(){
	NVIC_InitTypeDef CAN_NVIC_InitStruct;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	
	CAN_NVIC_InitStruct.NVIC_IRQChannel = CAN2_RX0_IRQn;
	CAN_NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
	CAN_NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
	CAN_NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	
	NVIC_Init(&CAN_NVIC_InitStruct);
}

void Config_Rx_Filter(){
	CAN_FilterInitTypeDef CAN_FilterInitStruct;
	CAN_FilterInitStruct.CAN_FilterIdHigh = (0x555 << 5) | (0 << 4) | (0 << 3);
	CAN_FilterInitStruct.CAN_FilterIdLow = (0x333 << 5) | (0 << 4) | (0 << 3);
	CAN_FilterInitStruct.CAN_FilterMaskIdHigh = 0xFF00;
	CAN_FilterInitStruct.CAN_FilterMaskIdLow = 0xFF00;
	CAN_FilterInitStruct.CAN_FilterNumber = 14;
	CAN_FilterInitStruct.CAN_FilterMode = CAN_FilterMode_IdMask;
	CAN_FilterInitStruct.CAN_FilterScale = CAN_FilterScale_16bit;
	CAN_FilterInitStruct.CAN_FilterActivation = ENABLE;
	CAN_FilterInitStruct.CAN_FilterFIFOAssignment = CAN_Filter_FIFO0;
	CAN_FilterInit(&CAN_FilterInitStruct);
	CAN_ITConfig(CAN2, CAN_IT_FMP0, ENABLE);
}
