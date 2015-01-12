#include"Bsp_Usart2.h"
/* 
 PD5  -- TX   USART2 
 PD6  -- RX
 */
void Usart2_init(void)
{
   GPIO_InitTypeDef GPIO_InitStructure;
   USART_InitTypeDef USART_InitStructure;
  //EXTI_InitTypeDef EXTI_InitStructure;
   NVIC_InitTypeDef NVIC_InitStructure;
	
   USART_DeInit(USART2);
   //set PA2 and PA3 as USART2 pin function 
   RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);  // open PA clock 
   RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE); // open USART2 clock 
   GPIO_PinAFConfig(GPIOD, GPIO_PinSource5, GPIO_AF_USART2);    // as TX 
   GPIO_PinAFConfig(GPIOD, GPIO_PinSource6, GPIO_AF_USART2); 		// as RX
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
   GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
   GPIO_Init(GPIOD, &GPIO_InitStructure);
   //usart init 
   USART_InitStructure.USART_BaudRate = 115200;//����������
   USART_InitStructure.USART_WordLength = USART_WordLength_8b;
   USART_InitStructure.USART_StopBits = USART_StopBits_1;
   USART_InitStructure.USART_Parity = USART_Parity_No;
   USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
   USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
   USART_Init(USART2, &USART_InitStructure);
   USART_Cmd(USART2, ENABLE);
	 USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);    //�ж�ʹ��
   USART_ClearFlag(USART2, USART_FLAG_TC);
	 // ���� ���ڶ� �����ж�
	
	 NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn; //Ƕ���ж�ͨ��Ϊ  USART1_IRQn
	 NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; //��ռ���ȼ� 0 
	 NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;    //��Ӧ���ȼ� 0
	 NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;     //�ж�ʹ��
	 NVIC_Init(&NVIC_InitStructure);	 
}
void Usart2_sendString(uint16_t * BuffAdd)
{
	 while (*BuffAdd)
	 {
			USART_SendData(USART2, *BuffAdd++);
	 /* Loop until the end of transmission */
			while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET)
			{}
	 }
}

void Usart2_sendChar(uint16_t buff)
{
	USART_SendData(USART2, buff);
	while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET)
	{}
}



