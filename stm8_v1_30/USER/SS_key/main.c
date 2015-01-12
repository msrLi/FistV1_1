/**
  ******************************************************************************
  * @file    Project/main.c 
  * @author  MCD Application Team
  * @version V2.1.0
  * @date    18-November-2011
  * @brief   Main program body
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
#include "stm8s.h"

/* Private defines -----------------------------------------------------------*/
#define DEVICE_ID  0x09
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
#define KeyIO_base  GPIOC
#define KeyIO_Pin   GPIO_PIN_7
uint8_t ReceFLag;     //  串口接受中断使能
uint16_t datas;
uint8_t GetUart1Data[4];
uint8_t sendBuff[10];  // 发送数据缓冲 
uint8_t flageExtiA;
//uint8_t i=0;
/* Private defines -----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void init_usart1(void);
void Send(uint8_t dat);
/* Private functions ---------------------------------------------------------*/
void Delay(uint16_t nCount)
{
  /* Decrement nCount value */
  while (nCount != 0)
  {   
    nCount--;
  }
}
void IWDG_init(void)
{
   IWDG->KR = 0xCC;
   IWDG->KR = 0x55;        //解除 PR 及 RLR 的写保护
   IWDG->RLR = 0xFF; //看门狗计数器重装载数值   
   IWDG->PR = 0x06; //分频系数为256，最长超时时间为：1.02S
   IWDG->KR = 0xAA; //刷新IDDG，避免产生看门狗复位，同时恢复 PR 及 RLR 的写保护状态
}
void main(void)
{
  uint8_t i;
//  BitStatus bytes;
  CLK_HSICmd(ENABLE);//开始内部高频RC
  CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);//不分频  16MHz
  /* Initialize I/Os in Output Mode */
  init_usart1();   // 输入判断
  GPIO_Init(GPIOA, GPIO_PIN_3, GPIO_MODE_OUT_PP_LOW_FAST);// 输出 模式 用于Trag 
  GPIO_Init(GPIOA, GPIO_PIN_2, GPIO_MODE_OUT_PP_LOW_FAST);// 输出 模式 用于Trag 
  GPIO_WriteHigh(GPIOA, GPIO_PIN_2);
  GPIO_Init(GPIOA,GPIO_PIN_1,GPIO_MODE_IN_FL_IT); 
  EXTI_SetTLISensitivity(EXTI_TLISENSITIVITY_RISE_ONLY);
  EXTI_SetExtIntSensitivity(EXTI_PORT_GPIOA,EXTI_SENSITIVITY_RISE_ONLY); 
  GPIO_Init(KeyIO_base,KeyIO_Pin,GPIO_MODE_IN_PU_NO_IT); 
//  InitADC();
  enableInterrupts();
  flageExtiA=0;  
  sendBuff[0]=DEVICE_ID;
  sendBuff[3]=0xff;
  sendBuff[4]=0xff;
  sendBuff[5]=0xFF;
  sendBuff[6]=0xA0;
  sendBuff[7]=0xFA; 
  IWDG_init();
  while (1)
  {
     
//    bytes=GPIO_ReadInputPin(GPIOA,GPIO_PIN_1);
//    if(bytes==RESET && flageExtiA==0)    
//    {
//        flageExtiA=1;  
//        GPIO_WriteReverse(GPIOA,GPIO_PIN_3);  
//        for(i=0;i<8;i++)
//        {  
//         // Send(sendBuff[i]);
//         }
//    }else if(bytes!=RESET)
//    {
//      flageExtiA=0;
//    }  
    // datas=readADCs();
   
      if(GPIO_ReadInputPin(KeyIO_base,KeyIO_Pin))
      {
         datas=0;
      }else{
         datas=1;
      }
    IWDG->KR = 0xAA;  //feed dogs
    if(flageExtiA!=1)
    {
      sendBuff[1]=(uint8_t) datas;
      sendBuff[2]=0;
    }     
  }
  
}
static void init_usart1(void)
{
  UART1_DeInit();
  /* 波特率 115200 8位数据  1个停止位 。  无奇偶校验  */
  UART1_Init((u32)115200, UART1_WORDLENGTH_8D, UART1_STOPBITS_1, UART1_PARITY_NO,\
           UART1_SYNCMODE_CLOCK_DISABLE, UART1_MODE_TXRX_ENABLE);
// UART1_ITConfig(UART1_IT_RXNE_OR, ENABLE);
//  UART1_ITConfig(UART1_IT_RXNE_OR, ENABLE);
 // UART1_ClearITPendingBit(UART1_IT_RXNE);     // 清理中断标志位 
}
void Send(uint8_t dat)
{
  while(( UART1_GetFlagStatus(UART1_FLAG_TXE)==RESET));	
    UART1_SendData8(dat);	
}
void Deal_ExtiA()
{
  uint8_t i;
  flageExtiA=1;
  GPIO_WriteReverse(GPIOA,GPIO_PIN_3);  
  sendBuff[5]=0;
  for(i=0;i<5;i++)
  {
    sendBuff[5]+=sendBuff[i];
  }
  for(i=0;i<8;i++)
  {  
    Send(sendBuff[i]);
   }  
  flageExtiA=0;
}
#ifdef USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param file: pointer to the source file name
  * @param line: assert_param error line source number
  * @retval : None
  */
void assert_failed(u8* file, u32 line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/

