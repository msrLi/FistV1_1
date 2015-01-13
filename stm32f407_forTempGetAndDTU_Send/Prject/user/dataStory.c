
#include"dataStory.h"
#include"String.h"

COMDATA comPortData[MAXCOM];   // �豸�������� 
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
*  canshu: com �˿ں� 0--15  
*  buff  : ���ƺ�
**/
void DevieceConfig(uint8_t com,char *buff)
{
	uint8_t i;
	i=strlen(buff);
	if(i>0 && i<10)
	{
		strcpy(comPortData[com].name,buff);   // �����ַ��� 
	}
	comPortData[com].Online=0;              // �������
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
*      comPort �˿ں�
*   ���˿ںŷ��ض˿ڶ�ȡ��������
**/
uint16_t GetValue2(int8_t comPort)
{
	if(comPort-1>=16 || comPort-1<0)		return 0;
	GetValueTime(comPort-1);
	return (*comPortData[comPort-1].dataPoint);
}



