#ifndef _BSP_TIMES_H_
#define _BSP_TIMES_H_
#include"stm32f4xx.h"
/* ��ʱ��	2 ��ʱ ���ڴ��� 1 ����*/
void Times2_init(void);  
void Times3_init(void);
void ChangeTime3State(uint8_t cmd);
void ChangeTime2State(uint8_t cmd);

#endif 
 

