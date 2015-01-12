
#ifndef LCD_Draw_H_
#define LCD_Draw_H_
#include"stm32f4xx.h"
#include"bsp.h"

/* 
*  ShowChar
*     ��ʾ �ַ��� 
*	  x,y ���� 
*			buff Ҫ��ʾ���ַ��� 
**/
void ShowChar(uint8_t x,uint8_t y,const char buff[]);
/*
*  ShowNumber 
*  	  ��ʾ����
*      * x   y ���� 
*      num  ������
**/ 
void ShowNumber(uint8_t x,uint8_t y,int num);
/*
*  ShowNumber 
*  	  ��ʾ������
*      * x   y ���� 
*      num  ������
**/ 
void ShowNumberFloat(uint8_t x,uint8_t y,float num);
#endif 
