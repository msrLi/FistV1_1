/**
  ******************************************************************************
  * @file    Audio_playback_and_record/src/main.c 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    28-October-2011
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
  */ 
/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"
#include"includes.h"
#include"bsp.h"
extern uint32_t ItUp,ItDown;
/** @addtogroup STM32F4-Discovery_Audio_Player_Recorder
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static OS_TCB AppDateConnectedTCB;    // ����ʱ��� 
static CPU_STK AppTaskDateConnectedStk[APP_CFG_TASK_DATE_CONNECTED_STK_SIZE];  // �����ջ

//static OS_TCB AppDateDtuDealyTCB;    // ����ʱ��� 
//static CPU_STK AppTaskDateDtuDealyStk[APP_CFG_TASK_DATE_DTUDEALY_STK_SIZE];  // �����ջ

static OS_TCB AppTaskStartTCB;    // ����ʱ��� 
static CPU_STK AppTaskStartStk[APP_CFG_TASK_START_STK_SIZE];   // �����ջ 

static  OS_TCB   AppTaskGUITCB;   // 
static  CPU_STK  AppTaskGUIStk[APP_CFG_TASK_GUI_STK_SIZE];

// static  OS_TCB   AppTaskGUIDrawingTCB;
// static  CPU_STK  AppTaskGUIDrawingStk[APP_CFG_TASK_GUIDRAWING_STK_SIZE];

//static  OS_TCB   AppTaskGUIRefreshTCB;
//static  CPU_STK  AppTaskGUIRefreshStk[APP_CFG_TASK_GUIRefresh_STK_SIZE];

/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/
static void AppTaskCreate (void);
static void AppTaskStart(void *p_arg);
void  AppTaskCreate(void)
{
	OS_ERR      err;	 // 
  /* ����GUI ����*/
	OSTaskCreate((OS_TCB       *)&AppTaskGUITCB,              
               (CPU_CHAR     *)"App Task GUI",
               (OS_TASK_PTR   )AppTaskGUI, 
               (void         *)0,
               (OS_PRIO       )APP_CFG_TASK_GUI_PRIO,
               (CPU_STK      *)&AppTaskGUIStk[0],
               (CPU_STK_SIZE  )APP_CFG_TASK_GUI_STK_SIZE / 10,
               (CPU_STK_SIZE  )APP_CFG_TASK_GUI_STK_SIZE,
               (OS_MSG_QTY    )0,
               (OS_TICK       )8,
               (void         *)0,
               (OS_OPT        )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
               (OS_ERR       *)&err);
	/* ���� ��ͼ GUI  ���� */ 
//	OSTaskCreate((OS_TCB       *)&AppTaskGUIDrawingTCB,              
//               (CPU_CHAR     *)"App Task GUI Drawing",
//               (OS_TASK_PTR   )AppTaskGUIDrawing, 
//               (void         *)0,
//               (OS_PRIO       )APP_CFG_TASK_GUIDrawing_PRIO,
//               (CPU_STK      *)&AppTaskGUIDrawingStk[0],
//               (CPU_STK_SIZE  )APP_CFG_TASK_GUIDRAWING_STK_SIZE / 10,
//               (CPU_STK_SIZE  )APP_CFG_TASK_GUIDRAWING_STK_SIZE,
//               (OS_MSG_QTY    )0,
//               (OS_TICK       )8,
//               (void         *)0,
//               (OS_OPT        )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
//               (OS_ERR       *)&err);							 
	/**************����GUIˢ������*********************/			 
//	OSTaskCreate((OS_TCB       *)&AppTaskGUIRefreshTCB,              
//               (CPU_CHAR     *)"App Task GUIRefresh",
//               (OS_TASK_PTR   )AppTaskGUIRefresh, 
//               (void         *)0,
//               (OS_PRIO       )APP_CFG_TASK_GUIRefresh_PRIO,
//               (CPU_STK      *)&AppTaskGUIRefreshStk[0],
//               (CPU_STK_SIZE  )APP_CFG_TASK_GUIRefresh_STK_SIZE / 10,
//               (CPU_STK_SIZE  )APP_CFG_TASK_GUIRefresh_STK_SIZE,
//               (OS_MSG_QTY    )0,
//               (OS_TICK       )8,
//               (void         *)0,
//               (OS_OPT        )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
//               (OS_ERR       *)&err);
	/**************�������ڶ�ȡ�¶�ʪ�ȴ�����********/
	OSTaskCreate((OS_TCB *) &AppDateConnectedTCB,
							(CPU_CHAR *)"App Task Date Connected",
							(OS_TASK_PTR) AppTaskDateConnected,      //�������
							(void *) 0,
							(OS_PRIO ) APP_CFG_TASK_DATE_CONNECTED_PRIO,
							(CPU_STK * )&AppTaskDateConnectedStk[0],
							(CPU_STK_SIZE ) APP_CFG_TASK_DATE_CONNECTED_STK_SIZE/10,
							(CPU_STK_SIZE ) APP_CFG_TASK_DATE_CONNECTED_STK_SIZE,
							(OS_MSG_QTY)0,
							(OS_TICK)  0,
							(void *) 0,
							(OS_OPT )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
							(OS_ERR *)&err);
//	/**************����DTU ���ڴ����� ********/
//	OSTaskCreate((OS_TCB *) &AppDateDtuDealyTCB,
//							(CPU_CHAR *)"App Task Date Connected",
//							(OS_TASK_PTR) AppTaskDTUDealy,      //�������
//							(void *) 0,
//							(OS_PRIO ) APP_CFG_TASK_DTUDealy_PRIO,
//							(CPU_STK * )&AppTaskDateDtuDealyStk[0],
//							(CPU_STK_SIZE ) APP_CFG_TASK_DATE_DTUDEALY_STK_SIZE/10,
//							(CPU_STK_SIZE ) APP_CFG_TASK_DATE_DTUDEALY_STK_SIZE,
//							(OS_MSG_QTY)0,
//							(OS_TICK)  0,
//							(void *) 0,
//							(OS_OPT )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
//							(OS_ERR *)&err);
}
/**
  * @brief  Main program.
  * @param  None
  * @retval None     
*/
int main(void)
 { 
	OS_ERR err;
	
	RCC_ClocksTypeDef Rcc_get;   // ��·ʱ�� 
	RCC_GetClocksFreq(&Rcc_get);
  OSInit(&err);
	OSTaskCreate((OS_TCB *) &AppTaskStartTCB,
							(CPU_CHAR *)"App Task Start",
							(OS_TASK_PTR) AppTaskStart,
							(void *) 0,
							(OS_PRIO ) APP_CFG_TASK_START_PRIO,
							(CPU_STK * )&AppTaskStartStk[0],
							(CPU_STK_SIZE ) APP_CFG_TASK_START_STK_SIZE/10,
							(CPU_STK_SIZE ) APP_CFG_TASK_START_STK_SIZE,
							(OS_MSG_QTY)0,
							(OS_TICK)   0,
							(void *)    0,
							(OS_OPT )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
							(OS_ERR *)&err);
	OSStart(&err);
  (void)&err;
	return (0);
	
}
int Countertimes;
static void AppTaskStart(void *p_arg)
{
		OS_ERR   err;
	
		(void)p_arg;
	  BSP_Init();	
	  CPU_Init();
	  BSP_Tick_Init();

  	Mem_Init();                             
    Math_Init();  
	
#if OS_CFG_STAT_TASK_EN > 0u
     OSStatTaskCPUUsageInit(&err);   
#endif

#ifdef CPU_CFG_INT_DIS_MEAS_EN
    CPU_IntDisMeasMaxCurReset();
#endif
	LCD_ShowString(90,20,(uint8_t *) "Macrobot technology ");  
	LCD_ShowString(110,50,(uint8_t *) "Used By Student ");  
	OSTimeDlyHMSM((CPU_INT16U) 0u,
								(CPU_INT16U) 0u,
								(CPU_INT16U) 2,
								(CPU_INT32U) 0,
								(OS_OPT    ) OS_OPT_TIME_HMSM_STRICT,
								(OS_ERR   *)&err);		
  LCD_Clear(BackS);
   AppTaskCreate();

		while(1)
		{
			OSTimeDlyHMSM((CPU_INT16U) 0u,
										(CPU_INT16U) 0u,
										(CPU_INT16U) 10,
										(CPU_INT32U) 500,
										(OS_OPT ) OS_OPT_TIME_HMSM_STRICT,
										(OS_ERR   *) &err);
		
		}
}
/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
