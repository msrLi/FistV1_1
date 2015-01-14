
#include"dataStory.h"
#include"String.h"

COMDATA comPortData[MAXCOM];   // 设备描述变量 
uint16_t Values[MAXCOM][2];  


void PortConfig(MODE modes,uint8_t comPort,const char *buff)
{
	if(comPort>16)
	{
		return;
	}
	
}
void GiveValue(void)
{
	uint8_t i;
	for(i=0;i<MAXCOM;i++)
	{
		comPortData[i].dataPoint=Values[i];
	}
}
/*
*  name : DevieceConfig
*  canshu: com 端口号 0--15  
*  buff  : 名称号
**/
void DevieceConfig(int8_t com,const char *buff)
{
	uint8_t i;
	if(com>16 || com<=0)
		return ;
	com--;
	i=strlen(buff);
	if(i>0 && i<10)
	{
		strcpy(comPortData[com].name,buff);   // 复制字符串 
	}
	comPortData[com].Online=0;              // 接受完成
}
/* 
*   name:GetValue1 
*   camshu: buff[]
*   按字符串取回值大小
**/
uint16_t GetValue1(const char buff[])
{
	uint8_t i;
	for(i=0;i<MAXCOM;i++)
	{
		if(strcmp(buff,comPortData[i].name)==0)
		{
			 GetValueTime(i);
			 return (*comPortData[i].dataPoint);
		}
	}
	return 0;
}
/*
* name : GetValue2
*      comPort 端口号
*   按端口号返回端口读取到的数据
**/
uint16_t GetValue2(int8_t comPort)
{
	if(comPort-1>=16 || comPort-1<0)		return 0;
	GetValueTime(comPort-1);
	return (*comPortData[comPort-1].dataPoint);
}



