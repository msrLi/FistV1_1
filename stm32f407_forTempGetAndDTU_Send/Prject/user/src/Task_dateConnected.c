#include"Task_dateConnected.h"
#include"Bsp_Led.h"
#include"dataStory.h"
#define Base  2
#define SAVEDATATIME    360000
#define  time_out_dely  300
#define A_154Pin  GPIO_Pin_10
#define B_154Pin  GPIO_Pin_11
#define C_154Pin  GPIO_Pin_12
#define D_154Pin  GPIO_Pin_13
#define U1_A_405Pin  GPIO_Pin_0
#define U1_B_405Pin  GPIO_Pin_1
#define U1_C_405Pin  GPIO_Pin_2
#define U2_A_405Pin  GPIO_Pin_3
#define U2_B_405Pin  GPIO_Pin_4
#define U2_C_405Pin  GPIO_Pin_5

OS_SEM  Usart1RecerveSem;       // 串口1  信号量 
OS_SEM * semTemp;
//OS_SEM  Usart3RecerveSem;       //  串口3 同步信号量
uint8_t rece1_buff[Max_date1];  // 串口数据缓冲 
uint16_t USART1_RX_STA=0;     //串口接收结束标志和 接收数量存放位置

OS_SEM  Usart2RecerveSem;
uint8_t  rece2_buff[Max_date2];
uint16_t USART2_RX_STA;

uint16_t ModeOkFlage=0;     // 外围设备 准备好数据 标志位 

uint32_t congdad;
uint32_t help_left,help_right;
void GetValueTime(uint8_t Ports);
/* 分类存储*/
void Deal_Recerve(uint8_t buff,uint8_t * adds)
{
	uint16_t buffs;
	comPortData[buff].DeviceID=adds[0];   // 设备ID
	comPortData[buff].Online=1;	
	buffs=0;
	switch(comPortData[buff].DeviceID)
	{
		case 0x08:    // 红外对管 
		{
			buffs+=adds[1];
			buffs+=(adds[2]<<8);
			comPortData[buff].dataPoint[0]=(uint16_t)(buffs*0.09765625);
		}
		break;
		case 0x09:   // 微动 开关 
		{
//			buffs+=adds[1];
//			buffs+=(adds[2]<<8);
			comPortData[buff].dataPoint[0]=adds[1];
		}
		break;
	}
//	if(comPortData[buff].DeviceID==0x08)
//	{
//		buffs+=adds[1];
//		buffs+=(adds[2]<<8);
//		comPortData[buff].dataPoint[0]=buffs;
////		buffs=GetValue2(15);
////		buffs=buffs;
//	}
//	comPortData[buff].dataPoint[0]=adds[1];
//	comPortData[buff].dataPoint[1]=adds[2];	
}
/* 
*   选中输入的信号
*   sle  0--15
**/
void Slect_CS(uint8_t sle)
{
	uint8_t i;
	const BitAction BitVals[2]={Bit_RESET,Bit_SET};
	uint8_t buff;
	
	if(sle>=16) return ;
	buff=sle;
	i=buff/8;
	GPIO_WriteBit(GPIOC,D_154Pin,BitVals[i]);
	buff-=(i*8);
	i=buff/4;
	GPIO_WriteBit(GPIOC,C_154Pin,BitVals[i]);	
	buff-=(i*4);
	i=buff/2;
	GPIO_WriteBit(GPIOC,B_154Pin,BitVals[i]);		
	buff-=(i*2);
	i=buff;
	GPIO_WriteBit(GPIOC,A_154Pin,BitVals[i]);	
	
	GPIO_ResetBits(GPIOB,GPIO_Pin_0);	
}
void OpenCharge(uint16_t data)
{
	uint16_t IO_data;
	IO_data=GPIOC->ODR;   // GPIOC IO Out Put Pin numbers 
	IO_data &= 0xFFC0;
	if(data<8)
	{
		IO_data |=data;

	}else{
		data-=8;
		IO_data |=(data<<3);
	}
	GPIOC->ODR = IO_data;
}
/* 
*   HC4054_Init
*   选通器初始化 
**/ 
void HC4054_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);	
	
	GPIO_InitStructure.GPIO_Pin = U1_A_405Pin | U1_B_405Pin | U1_C_405Pin | \
	U2_A_405Pin | U2_B_405Pin | U2_C_405Pin ;  // Init 
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOC, &GPIO_InitStructure);	
}
/*
*    初始化 4--16 译码器
**/
void HC154_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 ;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_SetBits(GPIOB,GPIO_Pin_0);
	
	GPIO_InitStructure.GPIO_Pin = A_154Pin | B_154Pin | C_154Pin | D_154Pin ;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
	
}
/* 
*    设置输入读取 IO状态  初始化 
**/ 
void ExamFlagInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);	
	GPIO_DeInit(GPIOE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_Init(GPIOE, &GPIO_InitStructure);	
}

void AppTaskDateConnected(void *p_arg)
{
	OS_ERR     err;
	static uint8_t flag=0;
//	uint8_t ubts;
//	uint8_t i,j,count;
//	uint8_t adds=0;
//  uint8_t *rece;
//	int common,error,pwm_l,pwm_r;
	ExamFlagInit();       // 初始化tick时钟
	HC154_Init();
	HC4054_Init();
	ModeOkFlage=GPIO_ReadInputData(GPIOE);  		// 获取 状态标志位
	/* 创建 信号量 用与同步两个进程 */
	// 用于同步  cn=0;
	OSSemCreate((OS_SEM    *)&Usart2RecerveSem,
							(CPU_CHAR  *)"Usart2RecerveSem",
							(OS_SEM_CTR )0,
							(OS_ERR    *)&err);	

	OSSemCreate((OS_SEM    *)&Usart1RecerveSem,
							(CPU_CHAR  *)"Usart1RecerveSem",
							(OS_SEM_CTR )0,
							(OS_ERR    *)&err);		

  USART2_RX_STA=0;
  USART1_RX_STA=0;
	GPIO_SetBits(GPIOB,GPIO_Pin_0);
  MainDeskTopFist();

	ChangeSpeed(1,0);
	ChangeSpeed(2,0);
	ChangeSpeed(3,0);
	ChangeSpeed(4,0);
	ChangeAngle(1,10,1);
	ChangeAngle(2,110,1);
	ChangeAngle(3,130,1);
	ChangeAngle(4,3000,2);
	 
	while(1)
	{		
		// keyValue.keyOK==0 ?  showUpdate():showRun();
		if(keyValue.keyOK)
		{
			if(flag==0)
			{
				LCD_Clear(BackS); 
			  LCD_ShowString(20,20,(u8 *) Software[keyValue.pages*10+keyValue.numberTop].FunctioName);
				LCD_ShowString(160,20,(u8 *) "Runing......");		  // 清除标志 显示字符 
			}
			flag=1;
			(*keyValue.KeyDealFunc)();
//			OSTimeDlyHMSM((CPU_INT16U) 0u,
//										(CPU_INT16U) 0u,
//										(CPU_INT16U) 0,
//										(CPU_INT32U) 1,
//										(OS_OPT    ) OS_OPT_TIME_HMSM_STRICT,
//										(OS_ERR   *)&err);				
		}else{
			if(flag==1)
			{
				LCD_Clear(BackS);
			}else{
				flag=0;
			}
			showUpdate();
			OSTimeDlyHMSM((CPU_INT16U) 0u,
										(CPU_INT16U) 0u,
										(CPU_INT16U) 0,
										(CPU_INT32U) 50,
										(OS_OPT    ) OS_OPT_TIME_HMSM_STRICT,
										(OS_ERR   *)&err);				
		}
//		XunBaoPRO();
//	   ChangeSpeed(2,pwm_r);   // Right_Q 
////	   ChangeSpeed(3,pwm_r);  //Right_H 
//		 ChangeSpeed(1,-pwm_l);		// Left_Q 
////	   ChangeSpeed(4,-pwm_l);   // Left_H
		
//		GetValueTime(6);
//		LCD_ShowString(150,150,"LEFT");
//    ShowNumber(190,150,(int)Values[6][0]);//ItUp   //Right
//		LCD_ShowString(150,100,"RIGHT");
//    ShowNumber(190,100,(int)Values[0][0]);//ItUp   //Left
//		help_left=Values[6][0];
//		help_right=Values[0][0];
//		common = (int)((2048-(help_left+help_right))*1.2);
//		error = -(help_right-help_left)*5;
//		pwm_l = common-error;
//		pwm_r = common+error;
//		if(pwm_l>2500) pwm_l=2500;
//		else if(pwm_l<-200) pwm_l=-200;
//		if(pwm_r>2500) pwm_r=2500;
//		else if(pwm_r<-200) pwm_r=-200;
//		ChangeAngle(7,cGg);
//		ChangeAngle(8,cGg);
		// Usart1_sendChar(0xFA);

		 // GPIO_SetBits(GPIOB,GPIO_Pin_0);    // 不选中 4--16 译码器 
		/*  查询频率 设置 */
//		OSTimeDlyHMSM((CPU_INT16U) 0u,
//                  (CPU_INT16U) 0u,
//                  (CPU_INT16U) 0,
//                  (CPU_INT32U) 1,
//                  (OS_OPT    ) OS_OPT_TIME_HMSM_STRICT,
//                  (OS_ERR   *)&err);	
	 }	  
}
void GetValueTime(uint8_t Ports)
{
	OS_ERR     err;
	uint8_t j,count;
	uint8_t adds=0;
  uint8_t *rece;
	GPIO_SetBits(GPIOB,GPIO_Pin_0);
	ModeOkFlage=GPIO_ReadInputData(GPIOE);  		// 获取 状态标志位
		
	count=(uint8_t)(Ports/8);     // 将 16 分为 前8 和后 8 两个数据段
	count>=1? USART_ITConfig(USART1, USART_IT_RXNE, DISABLE):USART_ITConfig(USART1, USART_IT_RXNE, ENABLE); 
	count>=1? USART_ITConfig(USART2, USART_IT_RXNE, ENABLE):USART_ITConfig(USART2, USART_IT_RXNE, DISABLE); 

	OSSemSet(&Usart2RecerveSem,0,&err);
	OSSemSet(&Usart1RecerveSem,0,&err);
	if(ModeOkFlage & (0x01<<Ports))
	{
		OpenCharge(Ports);  //选通器打开
		
		USART1_RX_STA=0;
		USART2_RX_STA=0;
		semTemp= count>=1? &Usart2RecerveSem:&Usart1RecerveSem;
		Slect_CS(Ports);     // CS 输出有效 
		
		GPIO_SetBits(GPIOB,GPIO_Pin_0);
		OSSemPend((OS_SEM *) semTemp,
						(OS_TICK )18,
						(OS_OPT  )OS_OPT_PEND_BLOCKING,
						(CPU_TS  )NULL,
						(OS_ERR *)&err); 	
		
		rece= count>=1? rece2_buff:rece1_buff;
		if(err==0)       //成功返回
		{
			
			adds=rece[0];
			for(j=1;j<5;j++)
			{
				adds+=rece[j];				
			}
			if(adds==rece[j])   // 收取正确
			{
				Trage_Led();
				Deal_Recerve(Ports,rece);
			}else{
				USART1_RX_STA=0;
				USART2_RX_STA=0;
			}
				USART1_RX_STA=0;
				USART2_RX_STA=0;
		}
		if(err==OS_ERR_TIMEOUT)   // 超时 进行下一个循环 
		{

		}
		if(err==OS_ERR_OBJ_TYPE)
		{
			OSSemCreate((OS_SEM    *) semTemp,
									(CPU_CHAR  *)"UsartRecerveSem",
									(OS_SEM_CTR )0,
									(OS_ERR    *)&err);			
		}	
		OSTimeDlyHMSM((CPU_INT16U) 0u,
									(CPU_INT16U) 0u,
									(CPU_INT16U) 0,
									(CPU_INT32U) 1,
									(OS_OPT    ) OS_OPT_TIME_HMSM_STRICT,
									(OS_ERR   *)&err);					
	}
}
