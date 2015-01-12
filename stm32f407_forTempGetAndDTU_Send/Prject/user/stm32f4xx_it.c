/**
  ******************************************************************************
  * @file    Audio_playback_and_record/src/stm32f4xx_it.c 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    28-October-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include"stm32f4xx_it.h"
#include"Bsp_Led.h"

//#include "stm32f4xx_usart.h"
int32_t ItUp,ItDown;
uint16_t times[2];
uint8_t ExitFlag;
/** @addtogroup STM32F4-Discovery_Audio_Player_Recorder
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
// static uint8_t lastBuffUsart2;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M4 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief   This function handles NMI exception.
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

void USART1_IRQHandler(void)
{	
	OS_ERR     err;
	uint8_t i;
	uint16_t buff;
  OSIntEnter();  // ֪ͨucos�����ж� 
	buff=USART_ReceiveData(USART1);
	if(USART1_RX_STA<Max_date1)
	{
		if(USART1_RX_STA==0)
		{
			i=0;
		}else{
			i=USART1_RX_STA-1;
		}
		if(buff==0xFA && rece1_buff[i]==0xA0)
		{
			rece1_buff[USART1_RX_STA++]=buff;
			rece1_buff[Max_date1-1]=0;  // ������־	
			USART_ClearFlag(USART1,USART_FLAG_RXNE);
			OSSemPost((OS_SEM *)&Usart1RecerveSem,
							 (OS_OPT  )OS_OPT_POST_ALL,
							 (OS_ERR *)&err);				
		}else{
			rece1_buff[USART1_RX_STA++]=buff;
		}
	}else
	{
		USART1_RX_STA|=1<<15;					//ǿ�Ʊ�ǽ������
		rece1_buff[Max_date1-1]=0;  // ������־
		OSSemPost((OS_SEM *)&Usart1RecerveSem,
						 (OS_OPT  )OS_OPT_POST_ALL,
						 (OS_ERR *)&err);	
	}
	 USART_ClearFlag(USART1,USART_FLAG_RXNE);
	 OSIntExit();    // ֪ͨucos �˳��ж�
}

void USART2_IRQHandler(void)
{
	OS_ERR     err;
	uint8_t i;
	uint16_t buff;
	OSIntEnter();  // ֪ͨucos�����ж� 
	buff=USART_ReceiveData(USART2);
	if(USART2_RX_STA<Max_date2)
	{
		if(USART2_RX_STA==0)
		{
			i=0;
		}else{
			i=USART2_RX_STA-1;
		}
		if(buff==0xFA && rece2_buff[i]==0xA0)
		{
			rece2_buff[USART2_RX_STA++]=buff;
			rece2_buff[Max_date2-1]=0;  // ������־	
			USART_ClearFlag(USART2,USART_FLAG_RXNE);
			OSSemPost((OS_SEM *)&Usart2RecerveSem,
							 (OS_OPT  )OS_OPT_POST_ALL,
							 (OS_ERR *)&err);				
		}else{
			rece2_buff[USART2_RX_STA++]=buff;
		}
	}else
	{
		USART_ClearFlag(USART2,USART_FLAG_RXNE);
		OSSemPost((OS_SEM *)&Usart2RecerveSem,
						 (OS_OPT  )OS_OPT_POST_ALL,
						 (OS_ERR *)&err);	
	}
	 USART_ClearFlag(USART2,USART_FLAG_RXNE);
	 OSIntExit();    // ֪ͨucos �˳��ж�
}
/*
extern uint8_t Usart3RecerveData[MaxRecrveDatas];
extern uint16_t Usart3RecerveStart;
*/
void USART3_IRQHandler(void)
{
//	OS_ERR     err;
	uint16_t buff;
	OSIntEnter();  // ֪ͨucos�����ж� 
  buff = USART_ReceiveData(USART3);
	if(Usart3RecerveStart<MaxRecrveDatas-1)    // �ж���ȡ���������Ƿ��ڻ���������Χ֮��
	{
		TIM3->CNT=0;
		if(Usart3RecerveStart==0)
		{
			// ChangeTime4State(1);			
		}
		Usart3RecerveData[Usart3RecerveStart++]=buff;
	}else{   // ��������������
		Usart3RecerveStart |= 0x01<<15;
		Usart3RecerveData[MaxRecrveDatas-1]=0;   // ��� ������
		USART_ClearFlag(USART3,USART_FLAG_RXNE);
//		OSSemPost((OS_SEM *)&Usart3RecerveSem,
//						 (OS_OPT  )OS_OPT_POST_ALL,
//						 (OS_ERR *)&err);			
	}
	USART_ClearFlag(USART3,USART_FLAG_RXNE);
	OSIntExit();    // ֪ͨucos �˳��ж�
}

void TIM2_IRQHandler(void)
{
	OS_ERR     err;
	OSIntEnter();  // ֪ͨucos�����ж� 
	if(TIM_GetITStatus(TIM2 , TIM_IT_Update) != RESET )
	{	
		// ChangeTime2State(0); // ������ʱ��2���� 
		rece1_buff[USART1_RX_STA]=0;
		USART1_RX_STA|=1<<15;					//ǿ�Ʊ�ǽ������
		OSSemPost((OS_SEM *)&Usart1RecerveSem,
						 (OS_OPT  )OS_OPT_POST_ALL,
						 (OS_ERR *)&err);			
	}
	TIM_ClearITPendingBit(TIM2,TIM_FLAG_Update);	//clear interrupt flags
	OSIntExit();    // ֪ͨucos �˳��ж�
}
void TIM3_IRQHandler(void)
{
	OS_ERR     err;
	OSIntEnter();  // ֪ͨucos�����ж� 
	if(TIM_GetITStatus(TIM3 , TIM_IT_Update) != RESET )
	{
		// ChangeTime3State(0); // ������ʱ��2���� 
		rece2_buff[USART2_RX_STA]=0;
		USART2_RX_STA|=1<<15;					//ǿ�Ʊ�ǽ������
		OSSemPost((OS_SEM *)&Usart2RecerveSem,
						 (OS_OPT  )OS_OPT_POST_ALL,
						 (OS_ERR *)&err);
	}
	TIM_ClearITPendingBit(TIM3,TIM_FLAG_Update);	//clear interrupt flags
	OSIntExit();    // ֪ͨucos �˳��ж�
}

void TIM4_IRQHandler(void)
{
//	OS_ERR     err;
	OSIntEnter();  // ֪ͨucos�����ж� 
	if(TIM_GetITStatus(TIM4 , TIM_IT_Update) != RESET )   // ��ʱ��4 ��ʱ �ж� 
	{
//		ChangeTime4State(0); // ������ʱ��4���� 
//		Usart3RecerveData[Usart3RecerveStart]=0;
//		Usart3RecerveStart |= 0x01<<15;
//		OSSemPost((OS_SEM *)&Usart3RecerveSem,
//						 (OS_OPT  )OS_OPT_POST_ALL,
//						 (OS_ERR *)&err);		
	}
	TIM_ClearITPendingBit(TIM4,TIM_FLAG_Update);	//clear interrupt flags
	OSIntExit();    // ֪ͨucos �˳��ж�
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
  * @brief  This function handles External line 1 interrupt request.
  * @param  None
  * @retval None
  */
void EXTI0_IRQHandler(void)
{
	
	OSIntEnter();  // ֪ͨucos�����ж� 
	Deal_keyButtom();
	EXTI_ClearITPendingBit(EXTI_Line0);
	OSIntExit();    // ֪ͨucos �˳��ж�
}

void EXTI1_IRQHandler(void)
{
	uint8_t i;
	OSIntEnter();  // ֪ͨucos�����ж� 
	i=255;
	while(i--)
	{
		i=i;
	}
  if(EXTI_GetFlagStatus(EXTI_Line1))
	{
		if(GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_1)==Bit_RESET && GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_2)==Bit_SET)   // �͵�ƽ 
		{
			EXTI->EMR &=  (~EXTI_Line2);   // �رյڶ�·�ж�
		}else if(GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_1)==Bit_SET && GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_2)==Bit_RESET){    //  �ߵ�ƽ
				// ItUp++;
			if(keyValue.keyOK==0)
			{
			   keyValue.numberTop--;
			}
			if(keyValue.numberTop>0xf0)   // С�� 0 
			{
				 keyValue.PageChage=1;
          if(keyValue.pages==0)
					{					
						if(keyValue.all_program>10)
						{
							keyValue.pages=1;
							keyValue.numberTop=keyValue.all_program-11;
						}else{
							keyValue.numberTop=keyValue.all_program-1;
						}						
					}else{
						keyValue.pages=0;
						keyValue.numberTop=9;
					}
			}
				EXTI->EMR |=  EXTI_Line2;
		}
  }
	EXTI_ClearITPendingBit(EXTI_Line1);
	OSIntExit();    // ֪ͨucos �˳��ж�
}
void EXTI2_IRQHandler(void)
{
	uint8_t i;
	OSIntEnter();  // ֪ͨucos�����ж� 	
	i=255;
	while(i--)
	{
		i=i;
	}
	if(EXTI_GetFlagStatus(EXTI_Line2))
	{
		if(GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_2)==Bit_RESET && GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_1)==Bit_SET)   // �͵�ƽ 
		{
			EXTI->EMR &=  (~EXTI_Line1);   // �رյڶ�·�ж�
		}else if(GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_2)==Bit_SET && GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_1)==Bit_RESET){    //  �ߵ�ƽ
		 //  ItUp--;
			if(keyValue.keyOK==0)
			{
				keyValue.numberTop++;
			}
			if(keyValue.numberTop>=10)
			{
				keyValue.pages=1;
				keyValue.PageChage=1;
				keyValue.numberTop=0;
			}
		 if(keyValue.pages*10+keyValue.numberTop>=keyValue.all_program)
		 {
			 keyValue.pages=0;
			 keyValue.PageChage=1;
			 keyValue.numberTop=0;
		 }
		
			EXTI->EMR |=  EXTI_Line1;
		}
	}
  EXTI_ClearITPendingBit(EXTI_Line2);
	OSIntExit();    // ֪ͨucos �˳��ж�
}
void EXTI3_IRQHandler(void)
{
	OSIntEnter();  // ֪ͨucos�����ж� 
	Deal_keyButtom();
	EXTI_ClearITPendingBit(EXTI_Line3);
	OSIntExit();    // ֪ͨucos �˳��ж�
}
void EXTI4_IRQHandler(void)
{
	OSIntEnter();  // ֪ͨucos�����ж� 
	Deal_keyButtom();
	EXTI_ClearITPendingBit(EXTI_Line4);
	OSIntExit();    // ֪ͨucos �˳��ж�
}
/**
  * @brief  This function handles TIM4 global interrupt request.
  * @param  None
  * @retval None
  */


//#if defined MEDIA_USB_KEY
///**
//  * @brief  EXTI0_IRQHandler
//  *         This function handles External line 0 interrupt request.
//  * @param  None
//  * @retval None
//  */
//void EXTI0_IRQHandler(void)
//{

//}


///**
//  * @brief  This function handles TIM2 global interrupt request.
//  * @param  None
//  * @retval None
//  */
//void TIM2_IRQHandler(void)
//{
//  // USB_OTG_BSP_TimerIRQ();
//}


///**
//  * @brief  This function handles USB-On-The-Go FS global interrupt request.
//  * @param  None
//  * @retval None
//  */
//void OTG_FS_IRQHandler(void)
//{
//  // USBH_OTG_ISR_Handler(&USB_OTG_Core);
//}
//#endif /* MEDIA_USB_KEY */

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/


/**
  * @}
  */ 
  
/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
