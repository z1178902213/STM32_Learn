/**
  ******************************************************************************
  * @file    Project/STM32F4xx_StdPeriph_Templates/stm32f4xx_it.c 
  * @author  MCD Application Team
  * @version V1.8.0
  * @date    04-November-2016
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2016 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_it.h"
#include "bsp_led.h"
#include "bsp_usart.h"
#include "bsp_wwdg.h"

/** @addtogroup Template_Project
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M4 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{

}

/******************************************************************************/
/*                 STM32F4xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f4xx.s).                                               */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/
void USART1_IRQHandler(void)
{
	if(USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == SET)
	{
		if(usart1_receive_c() == 'r'){
			toggle_red();
		}else if(usart1_receive_c() == 'g'){
			toggle_green();
		}else if(usart1_receive_c() == 'b'){
			toggle_blue();
		}
		usart1_send_s("OK\n");
	}
}

void TIM6_DAC_IRQHandler(void){
	if(TIM_GetFlagStatus(TIM6, TIM_IT_Update) != RESET){
		toggle_green();
		TIM_ClearITPendingBit(TIM6, TIM_IT_Update);
	}
}

extern CanRxMsg can2_rx;

void CAN2_RX0_IRQHandler(void){
	uint8_t i = 0;
	if(CAN_GetFlagStatus(CAN2, CAN_FLAG_FMP0) == SET){
		CAN_Receive(CAN2, CAN_FIFO0, &can2_rx);
		printf("--> 接收到StdId：0X%X\n", can2_rx.StdId);
		printf("--> 接收到IDE：%d\n", can2_rx.IDE);
		printf("--> 接收到RTR：%d\n", can2_rx.RTR);
		printf("--> 接收到DLC：%d\n", can2_rx.DLC);
		printf("--> 接收到Data：");
		for(i = 0; i< can2_rx.DLC; i++){
			printf("%d ", can2_rx.Data[i]);
		}
		printf("\n--> 测试完成\n");
	}
}

void WWDG_IRQHandler(void){
	wwdg_reload(127);
	WWDG_ClearFlag();
	printf("\n--> 触发亡语.\n");
	turn_on_red();
}


__IO uint32_t IC1Value;
__IO uint32_t IC2Value;
__IO double DutyCycle;
__IO double Frequency;
void TIM8_CC_IRQHandler(){
	TIM_ClearITPendingBit(TIM8, TIM_IT_CC1);
	
	IC1Value = TIM_GetCapture1(TIM8);
	IC2Value = TIM_GetCapture2(TIM8);		// TIM_ICInitStruct中配置了捕获下降沿，也就是通道2的情况。
	
  printf("IC1Value = %d  IC2Value = %d ",IC1Value,IC2Value);
	if (IC1Value != 0) {
		/* 占空比计算 */
		DutyCycle = (float)((IC2Value+1) * 100) / (IC1Value+1);
		/* 频率计算 */
		Frequency = 168000000/(1680)/(float)(IC1Value+1);
		printf("--> 占空比：%0.2f%%频率：%0.2fHz\n", DutyCycle, Frequency);
	} else {
		DutyCycle = 0;
		Frequency = 0;
	}
}

/**
  * @}
  */ 


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
