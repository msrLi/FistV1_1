#include"Bsp_Led.h"
/* 
*		 ��ʼ�� LED ���� 
**/
void Bsp_InitLed(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	GPIO_InitStructure.GPIO_Pin = LED_Pin ;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOD, &GPIO_InitStructure);
  GPIO_SetBits(LED_PORT,LED_Pin);  // 
}
/* 
*   ��ת  LED  ״̬ 
*/
void Trage_Led(void)
{
	GPIO_ToggleBits(LED_PORT,LED_Pin);
}
/* 
*   �ı�LED״̬ 
*   sw    1 : LED ����
* 				0 ��LED �ر�
**/
void LED_Change(uint8_t sw)
{
	const BitAction BitVals[2]={Bit_SET,Bit_RESET};
	if(sw>=2)  sw=0;
	GPIO_WriteBit(LED_PORT,LED_Pin,BitVals[sw]);
}

