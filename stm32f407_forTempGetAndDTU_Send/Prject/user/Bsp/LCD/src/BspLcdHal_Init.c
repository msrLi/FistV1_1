#include"BspLcdHal_Init.h"


void LCD_FMSC()
{
	FSMC_NORSRAMInitTypeDef  init;
	FSMC_NORSRAMTimingInitTypeDef  timingWrite;
	FSMC_NORSRAMTimingInitTypeDef  timingRead;
	/*-- FSMC Configuration ------------------------------------------------------*/
	/*----------------------- SRAM Bank 1 ----------------------------------------*/
	/* FSMC_Bank1_NORSRAM4 configuration */
	/* ����ͷDMA��㣬������ 4 0 5 2 0 0 */
	timingWrite.FSMC_AddressSetupTime = 4;
	timingWrite.FSMC_AddressHoldTime = 0;
	timingWrite.FSMC_DataSetupTime = 6;
	timingWrite.FSMC_BusTurnAroundDuration = 1;
	timingWrite.FSMC_CLKDivision = 0;
	timingWrite.FSMC_DataLatency = 0;
	timingWrite.FSMC_AccessMode = FSMC_AccessMode_B;

	timingRead.FSMC_AddressSetupTime = 4;
	timingRead.FSMC_AddressHoldTime = 0;
	timingRead.FSMC_DataSetupTime = 8;
	timingRead.FSMC_BusTurnAroundDuration = 1;
	timingRead.FSMC_CLKDivision = 0;
	timingRead.FSMC_DataLatency = 0;
	timingRead.FSMC_AccessMode = FSMC_AccessMode_B;

	/*
	 LCD configured as follow:
	    - Data/Address MUX = Disable
	    - Memory Type = SRAM
	    - Data Width = 16bit
	    - Write Operation = Enable
	    - Extended Mode = Enable
	    - Asynchronous Wait = Disable
	*/
	init.FSMC_Bank = FSMC_Bank1_NORSRAM1;
	init.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable;
	init.FSMC_MemoryType = FSMC_MemoryType_SRAM;
	init.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;
	init.FSMC_BurstAccessMode = FSMC_BurstAccessMode_Disable;
	init.FSMC_AsynchronousWait = FSMC_AsynchronousWait_Disable;	/* ע��ɿ��������Ա */
	init.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
	init.FSMC_WrapMode = FSMC_WrapMode_Disable;
	init.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;
	init.FSMC_WriteOperation = FSMC_WriteOperation_Enable;
	init.FSMC_WaitSignal = FSMC_WaitSignal_Disable;
	init.FSMC_ExtendedMode = FSMC_ExtendedMode_Disable;
	init.FSMC_WriteBurst = FSMC_WriteBurst_Disable;

	init.FSMC_ReadWriteTimingStruct = &timingRead;
	init.FSMC_WriteTimingStruct = &timingWrite;

	FSMC_NORSRAMInit(&init);

	/* - BANK 1 (of NOR/SRAM Bank 1~4) is enabled */
	FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM1, ENABLE);
	
//      FSMC_NORSRAMInitTypeDef  FSMC_NORSRAMInitStructure;
//      FSMC_NORSRAMTimingInitTypeDef  p;
//    
//      RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC,ENABLE);
//    
//      /* FSMC_Bank1_NORSRAM1 timing configuration */
//      p.FSMC_AddressSetupTime = 0;/*��ַ����ʱ������*/                                            
//      p.FSMC_AddressHoldTime = 0;/*��ַ�ĳ���ʱ��*/
//      p.FSMC_DataSetupTime = 1;/*�趨����ʱ������*/
//      p.FSMC_BusTurnAroundDuration = 0x00;/*����ת��ʱ��*/
//      p.FSMC_CLKDivision = 0x00;/*CLKʱ������źŵ�HCLK��������ʾʱ��???*/
//      p.FSMC_DataLatency = 0x00;/*ָ���ڻ�õ�һ������ǰ��ʱ������*/
//      p.FSMC_AccessMode = FSMC_AccessMode_B;
//    
//      FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM1;/*ָ����FSMC��*/
//      FSMC_NORSRAMInitStructure.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable; /*��ַ������ֵ�����õ���������*/                                         
//      FSMC_NORSRAMInitStructure.FSMC_MemoryType = FSMC_MemoryType_NOR;     /*�ⲿ�洢��������*/
//      FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;/*���ݿ��*/
//      FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode = FSMC_BurstAccessMode_Disable;/* ����ͻ������ģʽ*/
//      FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;/*ָ���ȴ��źŵļ���*/
//      FSMC_NORSRAMInitStructure.FSMC_WrapMode = FSMC_WrapMode_Disable;/*Enables or disables the Wrapped burst access mode for Flash*/
//      FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;
//      FSMC_NORSRAMInitStructure.FSMC_WriteOperation = FSMC_WriteOperation_Enable;/*����ָ����FSMC���д����*/
//      FSMC_NORSRAMInitStructure.FSMC_WaitSignal = FSMC_WaitSignal_Disable;
//      FSMC_NORSRAMInitStructure.FSMC_ExtendedMode = FSMC_ExtendedMode_Disable;/*��չģʽ*/
//      FSMC_NORSRAMInitStructure.FSMC_WriteBurst = FSMC_WriteBurst_Disable;/*����дͻ������*/
//      FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &p;
//      FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct = &p;	     
//      FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure);   
//      /* Enable FSMC Bank1_SRAM Bank */
//      FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM1, ENABLE);  
}
/*
	��ʾ�� ���ӷ�ʽ 

	PD0/FSMC_D2
	PD1/FSMC_D3
	PD4/FSMC_NOE		--- �������źţ�OE = Output Enable �� N ��ʾ����Ч
	PD5/FSMC_NWE		--- д�����źţ�WE = Output Enable �� N ��ʾ����Ч
	PD8/FSMC_D13
	PD9/FSMC_D14
	PD10/FSMC_D15
	PD11/FSMC_A16		--- ��ַ RS
	PD14/FSMC_D0
	PD15/FSMC_D1


	PE7/FSMC_D4
	PE8/FSMC_D5
	PE9/FSMC_D6
	PE10/FSMC_D7
	PE11/FSMC_D8
	PE12/FSMC_D9
	PE13/FSMC_D10
	PE14/FSMC_D11
	PE15/FSMC_D12

	PD7/FSMC_NE1		--- ��Ƭѡ��TFT��
  PE1 --> LCD_reset 
//	PC3/TP_INT			--- ����оƬ�ж� ������RA8875������RA8875������ж�)  ������δʹ��Ӳ���ж�

//	---- ������ TFT LCD�ӿ������ź� ��FSMCģʽ��ʹ�ã�----
//	PD3/LCD_BUSY		--- ����оƬæ       ��RA8875����RA8875оƬ��æ�ź�)
//	PF6/LCD_PWM			--- LCD����PWM����  ��RA8875������˽ţ�������RA8875����)

//	PI10/TP_NCS			--- ����оƬ��Ƭѡ		(RA8875������SPI�ӿڴ���оƬ��
//	PB3/SPI3_SCK		--- ����оƬSPIʱ��		(RA8875������SPI�ӿڴ���оƬ��
//	PB4/SPI3_MISO		--- ����оƬSPI������MISO(RA8875������SPI�ӿڴ���оƬ��
//	PB5/SPI3_MOSI		--- ����оƬSPI������MOSI(RA8875������SPI�ӿڴ���оƬ��
*/
void BUS_dataAndAddress_config()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	/* ʹ��FSMCʱ�� */
	RCC_AHB3PeriphClockCmd(RCC_AHB3Periph_FSMC, ENABLE);	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD | RCC_AHB1Periph_GPIOE , ENABLE);
	/* ���� PD.00(D2), PD.01(D3), PD.04(NOE), PD.05(NWE), PD.08(D13), PD.09(D14),
	 PD.10(D15), PD.14(D0), PD.15(D1) Ϊ����������� */
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource0, GPIO_AF_FSMC);   // F_D2
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource1, GPIO_AF_FSMC);   // F_D3
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource4, GPIO_AF_FSMC);   // F_NOE
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource5, GPIO_AF_FSMC);   // F_NWR
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource8, GPIO_AF_FSMC);   // F_D13
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource9, GPIO_AF_FSMC);   // F_D14
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource10, GPIO_AF_FSMC);  // F_D15
	
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource14, GPIO_AF_FSMC);  // F_D0
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource15, GPIO_AF_FSMC);  // F_D1

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_4 | GPIO_Pin_5 |
	                            GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_14 |
	                            GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	/* ���� PE.07(D4), PE.08(D5), PE.09(D6), PE.10(D7), PE.11(D8), PE.12(D9), PE.13(D10),
	 PE.14(D11), PE.15(D12) Ϊ����������� */

//	GPIO_PinAFConfig(GPIOE, GPIO_PinSource4 , GPIO_AF_FSMC);
//	GPIO_PinAFConfig(GPIOE, GPIO_PinSource5 , GPIO_AF_FSMC);

	GPIO_PinAFConfig(GPIOE, GPIO_PinSource7 , GPIO_AF_FSMC);       // F_D4
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource8 , GPIO_AF_FSMC);       // F_D5
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource9 , GPIO_AF_FSMC);			 // F_D6
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource10 , GPIO_AF_FSMC);			 // F_D7
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource11 , GPIO_AF_FSMC);			 // F_D8
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource12 , GPIO_AF_FSMC);			 // F_D9
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource13 , GPIO_AF_FSMC);			 // F_D10
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource14 , GPIO_AF_FSMC);			 // F_D11
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource15 , GPIO_AF_FSMC);			 // F_D12

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 |
	                            GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 |
	                            GPIO_Pin_15;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	/* ���� PD.11(A16 (RS))  Ϊ����������� */
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource11, GPIO_AF_FSMC);    // F_A16

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	/* ���� PD7 (LCD/CS)) Ϊ����������� */
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource7, GPIO_AF_FSMC);     // F_NE1

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_Init(GPIOD, &GPIO_InitStructure);	
	
/* ��λ�ܽ� */	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
//      GPIO_InitTypeDef GPIO_InitStructure;
//      // enable time clock about gpio mode 
//      RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOE |
//                             RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO, ENABLE);
//      
//      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
//      GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//      
//      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 ; 	 //LCD-Reset==PE1
//      GPIO_Init(GPIOE, &GPIO_InitStructure);
//      
//      
//      GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
//      // Set PD.00(D2), PD.01(D3),
//	  // PD.04(NOE/RD),  PD.05(NWE/WR), PD.08(D13), PD.09(D14),
//      //   PD.10(D15), PD.14(D0), PD.15(D1) as alternate function push pull 
//      
//      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_8 |
//                                    GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_14 | GPIO_Pin_15;

//      GPIO_Init(GPIOD, &GPIO_InitStructure);
//    
//      // Set PE.07(D4), PE.08(D5), PE.09(D6), PE.10(D7), PE.11(D8), PE.12(D9), PE.13(D10),
//      //   PE.14(D11), PE.15(D12) as alternate function push pull 
//      GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | 
//                                    GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | 
//                                    GPIO_Pin_15;
//      GPIO_Init(GPIOE, &GPIO_InitStructure); 
//      
//        /* CS Ϊ��FSMC_NE1(PD7) */
//      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7; 
//      GPIO_Init(GPIOD, &GPIO_InitStructure);
//  
//      /* RS ΪFSMC_A16(PD11)*/
//      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 ; 
//      GPIO_Init(GPIOD, &GPIO_InitStructure);

//      GPIO_SetBits(GPIOD, GPIO_Pin_7);			//CS=1 
//      GPIO_SetBits(GPIOD, GPIO_Pin_11);			//RS=1
//      GPIO_SetBits(GPIOD, GPIO_Pin_8| GPIO_Pin_9 |GPIO_Pin_10);  	 
//      GPIO_SetBits(GPIOE, GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10);
//      GPIO_SetBits(GPIOE, GPIO_Pin_1);			//RESET=1
//      GPIO_SetBits(GPIOD, GPIO_Pin_4);		    //RD=1
//      GPIO_SetBits(GPIOD, GPIO_Pin_5);			//WR=1
}

