#ifndef _EXCHANGEDATA_H_
#define _EXCHANGEDATA_H_
// #include"headerAllConfig.h"
#include "stm32f4xx.h"
#include<string.h>
#include<math.h>  
#include<assert.h> 
/* ����ת����  �ַ�����  */ 
char* myitoa(int num,char*str,int radix);
char *my_ftoa(double number,int ndigit,char *buf);

/*  �ַ���ת���� */ 
int my_atoi(const char * str);

/*  �ַ���ת����double������ */
double myatof(char *s);
#endif 

