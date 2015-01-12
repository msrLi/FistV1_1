#include"Task_GUI.h"
//#include"GUIDEMO.h"
//#include<songti16.c>
//#include<SongTi24.c>
//#include<songti48.c>
//#include<zhandian16.c>
//#include"LCD_interface.h"
//#include"Bsp_Touch_SPI.h"
//#include"GUI_DraweSing.h"
#include "MainTaskGUI.h"
DreawPage FistPages;
void AppTaskGUI(void *p_arg)
{
//	uint8_t i;
	OS_ERR      err;
  OSTimeGet(&err);	
	(void) p_arg;
  MainDeskTopFist();	
	 
	 while(1)
	 {
		 BSP_OS_TimeDly(50);
		 
	 }
}
void AppTaskGUIRefresh(void *p_arg)
{
  (void)p_arg;
	while(1)
	{
		  // GUI_Exec();             //  GUI ÇÐ»»
		  BSP_OS_TimeDly(300);
	}
}

