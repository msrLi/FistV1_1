
#ifndef ADc_H_
#define ADc_H_
#include "stm8s.h"

/* 
*  name : InitADC
*       : ��������AD��ʼ��
**/
void InitADC(void);

/*
*  name : readADCs
*       : ��ȡADֵ�ú���
**/
uint16_t readADCs(void);

#endif 


