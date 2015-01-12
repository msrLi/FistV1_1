#include"Bsp_slectLCD.h"

KeyValue keyValue;

void KeyPID(uint8_t keyID)
{
	 switch(keyID)
	 {
		 case 1:
			 break;
		 case 2: 
			 break;
		 default:break;
	 }
}

void hello1(void)
{
	int j;
	j++;
}
void hell02(void)
{
}
/* 
用于显示 主界面 
*/
void MainDeskTopFist(void)
{
//	OS_ERR     err;
	int i,dataBuff;

	/*
	 显示各种信息  and then  on  how to used it 
	*/
//	LCD_ShowString(90,20,"Macrobot technology ");  
//	LCD_ShowString(110,50,"Used By Student ");  
//	OSTimeDlyHMSM((CPU_INT16U) 0u,
//								(CPU_INT16U) 0u,
//								(CPU_INT16U) 2,
//								(CPU_INT32U) 0,
//								(OS_OPT    ) OS_OPT_TIME_HMSM_STRICT,
//								(OS_ERR   *)&err);		
//  LCD_Clear(BackS);
  LCD_ShowString(100,5,(u8 *) "Function Slect");  
	dataBuff=sizeof(Software)/sizeof(FunctionDescription);
	for(i=0;i<dataBuff;i++)
	{
		if(Software[i].FunctioName[0]==0)
		{
			 break;
		}else{
			keyValue.all_program++;
		}	
	}
	if(keyValue.all_program>10)
	{
		keyValue.overFlow=1;
	}else{
		keyValue.overFlow=0;
	}
	showUpdate();
//	LCD_ShowString(15,40+20*9,(u8 *)">>");   

	// if(keyValue)
}
void showUpdate(void)
{
	uint8_t i;

	if(keyValue.PageChage)
	{
		keyValue.PageChage=0;
		LCD_Clear(BackS); 
	}
	LCD_ShowString(100,5,(u8 *) "Function Slect");  	
  
	for(i=0;i<10;i++)
	{
		if(Software[i+keyValue.pages*10].FunctioName[0]==0)
		{
			 break;
		}
		LCD_ShowString(50,40+20*i,(u8 *) Software[keyValue.pages*10+i].FunctioName);  
	} 
	if(keyValue.overFlow)
	{
		if(keyValue.pages==0)
		{
			  LCD_ShowString(220,40+20*9,(u8 *) "NEXT-->Page");
		}else{
			  LCD_ShowString(220,40+20*9,(u8 *) "Page<--NEXT");
		}
	}	
	for(i=0;i<10;i++)
	{
		LCD_ShowString(180,40+20*i,(u8 *)"  ");
	}
  LCD_ShowString(180,40+20*keyValue.numberTop,(u8 *)">>");

}
void showRun(void)
{
	LCD_Clear(BackS); 
	LCD_ShowString(100,50,(u8 *) Software[keyValue.pages*10+keyValue.numberTop].FunctioName);
	LCD_ShowString(100,80,(u8 *) "Runing......");
}
void MainDeskTop(void)
{
	// LCD_ShowString(100,5,(u8 *) "Function Slect");  
	
}
void waitForButtomAdd(void)
{
	while(1)
	{
		
	}
}










