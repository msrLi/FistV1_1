#include"GUI_Fist_Page.h"
uint8_t pageChangFlag=0;
WM_HWIN hads;     // ���ھ��
static void Fist_page_callback(WM_MESSAGE * pMsg)
{
	  GUI_PID_STATE psas;
		uint8_t i,j;
	
		switch(pMsg->MsgId)
		{
			case WM_PAINT:   // �ػ溯��
				GUI_Clear();
			  FistPageDrawLine();
				break;
		  case WM_TOUCH:   //�����豸���� 
			case WM_TOUCH_CHILD:
				i=GUI_TOUCH_GetState(&psas);  //get touch station 
			  if(psas.Layer==0 && psas.Pressed==0)
				{
					 i=psas.x/120;
					 if(psas.y>=72)
					   j=(psas.y-72)/100;
					 else break;
					 pageChangFlag=j*4+i+1;		 
				}
				break;				
			default:
				WM_DefaultProc(pMsg);
		}
}
void backWIn_init(void)
{
	 GUI_SelectLayer(0);
	 GUI_TOUCH_SetLayer(0);
	 WM_SetCallback(WM_HBKWIN, &Fist_page_callback);	  //���ñ����ص�����
	 GUI_Delay(1);	 
	 COMAND=0x04;    // ��ʾҳ�� 
	 DATA=0;	
}
