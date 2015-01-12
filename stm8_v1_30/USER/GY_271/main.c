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
#include"I2C_IO.h"
#include"HMC5833.h"
#include"math.h"
double angles;
/* Private defines -----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
void DelayUs(uint16_t times)
{
  uint16_t i,j;
  for(i=times;i>0;i--)
          for(j=2;j>0;j--);
}
void main(void)
{ 
  // InitHCM8553();
  int ju;
  /* 初始化 输出TRAG */
  GPIO_Init(GPIOA, GPIO_PIN_3, GPIO_MODE_OUT_PP_LOW_FAST);// 输出 模式 用于Trag 
  GPIO_WriteLow(GPIOA, GPIO_PIN_3);                       // Let it is LowLave
  bsp_InitI2C();
  if (i2c_CheckDevice(HMC5883L_SLAVE_ADDRESS) == 0)
  {
    ju++;             
          // printf("HMC5883L Ok (0x%02X)\r\n", HMC5883L_SLAVE_ADDRESS);
  }
  else
  {
    ju++;
          // printf("HMC5883L Err (0x%02X)\r\n",HMC5883L_SLAVE_ADDRESS);
  }  
  bsp_InitHMC5883L();
  while(1)
  {
    // MultipleReadHMC5883();
    GPIO_WriteHigh(GPIOA, GPIO_PIN_3);
    DelayUs(200);
    GPIO_WriteLow(GPIOA, GPIO_PIN_3);
    DelayUs(200);
    HMC5883L_ReadData();		/* ?áè? MPU-6050μ?êy?Yμ?è???±?á? g_tMPU6050 */
    angles=atan2((double)g_tMag.Y,(double)g_tMag.X) * (180 / 3.14159265) + 180;
  }
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

