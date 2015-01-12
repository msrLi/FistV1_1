#ifndef _BSP_LED_H_
#define _BSP_LED_H_
#include "stm32f4xx.h"
#include "bsp.h"
#define LED_PORT  GPIOD
#define LED_Pin  GPIO_Pin_10

/* 
*		 ��ʼ�� LED ���� 
**/
void Bsp_InitLed(void);
/* 
*   ��ת  LED  ״̬ 
*/
void Trage_Led(void);
/* 
*   �ı�LED״̬ 
*   sw    1 : LED ����
* 				0 ��LED �ر�
**/
void LED_Change(uint8_t sw);
#endif
