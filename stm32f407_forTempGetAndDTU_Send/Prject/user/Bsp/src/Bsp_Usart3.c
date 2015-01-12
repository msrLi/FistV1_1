#include"Bsp_Usart3.h"
/* 
	 PD8 ---TX 
	 PD9 ---RX
*/
uint8_t Usart3RecerveData[MaxRecrveDatas];
uint16_t Usart3RecerveStart=0;
void Usart3_init(void)
{
   GPIO_InitTypeDef GPIO_InitStructure;
   USART_InitTypeDef USART_InitStructure;
  //EXTI_InitTypeDef EXTI_InitStructure;
  //NVIC_InitTypeDef NVIC_InitStructure;
	/* used as DTU controal  */
//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
//	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;
//  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
//  GPIO_Init(GPIOC, &GPIO_InitStructure);	
//	GPIO_ResetBits(GPIOC,GPIO_Pin_1);
	
   USART_DeInit(USART3);    
   // PB10,PB11 
   RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);    // ���� IO ��ʱ��
   RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);      // ��ʼ���� 3 ʱ�� 
   GPIO_PinAFConfig(GPIOD, GPIO_PinSource8, GPIO_AF_USART3);   //���� ����3 ����ʱ�Ӻ����� �������� 
   GPIO_PinAFConfig(GPIOD, GPIO_PinSource9, GPIO_AF_USART3);   //���� ����3 ����ʱ�Ӻ����� �������� 
	 GPIO_StructInit(&GPIO_InitStructure);   // �ָ�Ĭ��ֵ 

   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
   GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
   GPIO_Init(GPIOD, &GPIO_InitStructure);
	 
   USART_InitStructure.USART_BaudRate = 115200;  					// BPS 9600 
   USART_InitStructure.USART_WordLength = USART_WordLength_8b;   // Bit 9 bit 
   USART_InitStructure.USART_StopBits = USART_StopBits_1;       // ֹͣλ 1   
   USART_InitStructure.USART_Parity = USART_Parity_No;            //������żУ��
   USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;  
   USART_InitStructure.USART_Mode = USART_Mode_Tx;   // alow  in and out  USART_Mode_Rx
   USART_Init(USART3, &USART_InitStructure);
	 /* set enable and set recerve interrupt   */
   USART_Cmd(USART3, ENABLE);	 
	 USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);    //�ж�ʹ��
   USART_ClearFlag(USART3, USART_FLAG_TC);
	 NVIC_Config_usart3();
	//  Times4_init();
}
void NVIC_Config_usart3()
{
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn; //Ƕ���ж�ͨ��Ϊ  USART1_IRQn
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2; //��ռ���ȼ� 0 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;    //��Ӧ���ȼ� 0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;     //�ж�ʹ��
	NVIC_Init(&NVIC_InitStructure);
	
}
/*************************************************
Function: void USART3_Puts(char * str) 
Description: USART3          
Input: strings                 
Output: null                             
Return: null                               
*************************************************/
void USART3_Puts(char * str)
{
	 while (*str)
	 {
				USART_SendData(USART3, *str++);

	 /* Loop until the end of transmission */
			while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET)
			{}
	 }
}
///* ��ʱ��	4 ��ʱ ���ڴ��� 3 ����*/
//void Times4_init(void)    // ��ʱ20ms
//{ 
//	uint32_t i;
//	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
//	NVIC_InitTypeDef NVIC_InitStructure;
//  RCC_ClocksTypeDef  rcc_clocks;
//  RCC_GetClocksFreq(&rcc_clocks);	
//	/* open clock*/
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
//	
//	NVIC_InitStructure.NVIC_IRQChannel=TIM4_IRQn;
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;
//	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
//	NVIC_Init(&NVIC_InitStructure);
//	
//	i=rcc_clocks.PCLK1_Frequency/1000000;
//	TIM_TimeBaseStructure.TIM_Period=20000;
//	TIM_TimeBaseStructure.TIM_Prescaler = i-1;      // 10^6 Hz   1us
//	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
//	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//????
//	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
//	TIM_ClearFlag(TIM4, TIM_FLAG_Update); 
//	  /* Enable TIM2 Update interrupt [TIM2??????]*/
//	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);  
//    /* TIM2 enable counter */
////  TIM_Cmd(TIM3, ENABLE);  	
//}
//void ChangeTime4State(uint8_t cmd)
//{
//  if(cmd)
//	{
//		TIM4->CNT=0;         //���������	 
//		TIM4->CR1|=1<<0;     //ʹ�ܶ�ʱ��4
//		TIM4->CNT=0;         //���������
//	}else  TIM4->CR1&=~(1<<0);     //��ֹ��ʱ��4	    
//}

