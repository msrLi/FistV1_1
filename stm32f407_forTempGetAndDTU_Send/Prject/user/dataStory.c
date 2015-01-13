
#include"dataStory.h"
#include"String.h"

COMDATA comPortData[MAXCOM];   // 设备描述变量 
uint16_t Values[MAXCOM][2];  

void PortConfig(MODE modes,uint8_t comPort,char buff[])
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
void DevieceConfig(uint8_t com,char *buff)
{
	uint8_t i;
	i=strlen(buff);
	if(i>0 && i<10)
	{
		strcpy(comPortData[com].name,buff);   // 复制字符串 
	}
	comPortData[com].Online=0;              // 接受完成
}

uint16_t GetValue1(char buff[])
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



