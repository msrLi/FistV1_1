
#include"LCD_Draw.h"

/* 
*  ShowChar
*     ��ʾ �ַ��� 
*	  x,y ���� 
*			buff Ҫ��ʾ���ַ��� 
**/
void ShowChar(uint8_t x,uint8_t y,const char buff[])
{
	LCD_ShowString(x,y,(const u8 *)buff);
}
/*
*  ShowNumber 
*  	  ��ʾ����
*      * x   y ���� 
*      num  ������
**/ 
void ShowNumber(uint8_t x,uint8_t y,int num)
{
	char sbuff[10];
	uint8_t flag=0;
	if(num<0){
		num=0-num;
		flag=1;	
	}
	//LCD_ShowString(x,y,(const u8 *)"    ");
	if(flag==1)
	{
		LCD_ShowString(x,y,(const u8 *)"-");
		x+=8;
	}
	myitoa(num,sbuff,10);
	LCD_ShowString(x,y,(const u8 *)sbuff);
	
}
/*
*  ShowNumber 
*  	  ��ʾ������
*      * x   y ���� 
*      num  ������
**/ 
void ShowNumberFloat(uint8_t x,uint8_t y,float num)
{
	char sbuff[20];
	uint8_t flag=0;
	if(num<0){
		num=0-num;
		flag=1;	
	}
	LCD_ShowString(x,y,(const u8 *)"      ");
	if(flag==1)
	{
		LCD_ShowString(x,y,(const u8 *)"-");
		x+=8;
	}
	my_ftoa(num,2,sbuff);
	LCD_ShowString(x,y,(const u8 *)sbuff);
	
}

