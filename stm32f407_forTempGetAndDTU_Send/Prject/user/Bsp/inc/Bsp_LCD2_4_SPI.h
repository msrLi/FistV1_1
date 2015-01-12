
#ifndef Bsp_LCD2_4_SPI_H_
#define Bsp_LCD2_4_SPI_H_
#include "stm32f4xx.h"

#define BackS 0x20FF
/* 
*  name : _InitLCD 
* 			��ʼ��LCD��ʾ��
* 
**/
void _InitLCD(void);

/*
*   ���㺯�� 
**/
void Address_set(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2);

/*
*
**/
static void LCD_WR_DATA(int da);
	
void LCD_Clear(u16 Color);
//��ʾ�ַ���
//x,y:�������  
//*p:�ַ�����ʼ��ַ
//��16����
void LCD_ShowString(u16 x,u16 y,const u8 *p);
#endif 
