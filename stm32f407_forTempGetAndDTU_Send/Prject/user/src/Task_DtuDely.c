#include"Task_DtuDely.h"
//#define MaxSendBuffLen  400      // ���ڷ��� ��󻺳���������
//OS_SEM  Usart1RecerveSem;       // ����1  �ź��� 
//OS_SEM  Usart3RecerveSem;       //  ����3 ͬ���ź���
//uint8_t rece1_buff[Max_date1];  // �������ݻ��� 
//uint16_t USART1_RX_STA=0;     //���ڽ��ս�����־�� �����������λ��
//uint8_t DTUOkFlag=0;          // DTU ״̬ ָʾ��־ 


extern uint8_t statrSpeed;
void AppTaskDTUDealy(void *p_arg)
{
	OS_ERR     err;
  uint8_t times;
	int common,error,pwm_l,pwm_r;
//	GPIO_InitTypeDef GPIO_InitStructure;
  (void) p_arg;
	  
	/* ���� �ź��� ����ͬ���������� */
	// ����ͬ��  cn=0;
//	OSSemCreate((OS_SEM    *)&Usart3RecerveSem,
//							(CPU_CHAR  *)"Usart3RecerveSem",
//							(OS_SEM_CTR )0,
//							(OS_ERR    *)&err);	

	// Usart3_init();
//	Usart3RecerveStart=0;
	while(1)
	{
		

		
//		OSSemPend((OS_SEM *)&Usart3RecerveSem,
//					(OS_TICK )0,
//					(OS_OPT  )OS_OPT_PEND_BLOCKING,
//					(CPU_TS  )0,
//					(OS_ERR *)&err);     	
//		 //�����ж� 

		OSTimeDlyHMSM((CPU_INT16U) 0u,
                  (CPU_INT16U) 0u,
                  (CPU_INT16U) 1,
                  (CPU_INT32U) 10,
                  (OS_OPT    ) OS_OPT_TIME_HMSM_STRICT,
                  (OS_ERR   *)&err);
//		while(1)
//		{
//			congdad++;
//			times++; 
//			if(times==0xfe)
//			{
//				times=0;
//			}
//		}		
	}
}

