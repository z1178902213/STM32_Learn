#include "test.h"
#include "bsp_usart.h"
#include "bsp_can.h"

CanTxMsg can2_tx;
CanRxMsg can2_rx;

void test_can(){
	init_usart1();
	Init_Can2_NVIC();
	
	init_can();
	Config_Rx_Filter();
	
	delay50ms();
	
	Config_Tx(&can2_tx);
	delay500ms();
	
	printf("--> 发送can2_tx的数据：StdId: 0x%X\n", can2_tx.StdId);
	CAN_Transmit(CAN2, &can2_tx);
	delay500ms();
	
	// 把ID改成0x337(0011 0011 0111)，掩码对应0xFF00，由于ID在筛选器中左移了5位，掩码中只有第[7:5]位是通配符，因此原监听0x333的ID变成了可以监听0x330-0x337。
	can2_tx.StdId = 0x330;
	printf("--> 发送can2_tx的数据：StdId: 0x%X\n", can2_tx.StdId);
	CAN_Transmit(CAN2, &can2_tx);
	
	printf("--> 测试CAN启动完成，不知道有没有启动。\n");
}
