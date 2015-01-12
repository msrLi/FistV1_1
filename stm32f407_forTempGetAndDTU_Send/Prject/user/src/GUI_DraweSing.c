#include"GUI_DraweSing.h"
// #include<wenshiduSongTi16.c>
extern GUI_CONST_STORAGE GUI_FONT GUI_FontwenshiduSongTi16;
extern uint8_t DrawingDataSave[8][4][200];  // ��Ųɼ�����
extern uint8_t numbersDrawing;              //��� �ɼ�������� 
#define GRAPH_CI_BK                  0
#define GRAPH_CI_BORDER              1
#define GRAPH_CI_FRAME               2
#define GRAPH_CI_GRID                3
#define COLOR_BK          GUI_DARKGRAY
#define COLOR_BORDER      0x880000
#define COLOR_FRAME       GUI_BLACK
#define COLOR_GRID        GUI_GRAY
#define GRAPH_DIV         9   // (2^9 = 512) If this value is changed _aWaves[] need to be changed too!
#define GRID_DIST_X       25
#define GRID_DIST_Y       10
#define MAX_NUM_DATA_OBJ 3 
#define Ca_xSize   230   // ͼ���ˮƽλ�ò�ֵ  
GRAPH_DATA_Handle  GRAPH_DATA_YT_Create(GUI_COLOR Color, unsigned MaxNumItems, I16 * pData, unsigned NumItems);

GRAPH_DATA_Handle 		hData[2][2]; 		// ���ݾ��  
GRAPH_Handle          hGraph[2];    //hGraph1
uint8_t last_DrawingNum=0;
GUI_HMEM hMem0,hMem1,hMem00,hMem11;
static uint8_t LastNumbersDrawing=0; 
/*
static int _HeartBeat[] = {
    2,   4,   6,   8,  10,   6,   2,   0,   0,   0,
   -8,  16,  40,  64,  88,  58,  28,  -2, -32, -30,
  -20, -10,   0,   2,   2,   4,   4,   6,   6,   8,
    8,  10,  12,  14,  16,  18,  20,  16,  12,   8,
    4,   2,   2,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0
};
*/
/*********************************************************************
*
*       _cbBk
*/
static void _cbBk(WM_MESSAGE * pMsg)
{
	GUI_COLOR Colorsback;
  switch (pMsg->MsgId) {
  case WM_PAINT:
		Colorsback=GUI_GetBkColor();
		GUI_SetBkColor(COLOR_BORDER);
		// GUI_SetColor(GUI_BLUE);
    GUI_Clear();

	  GUI_SetBkColor(Colorsback);
	  // _pfDrawBk();
  break;
  default:
    WM_DefaultProc(pMsg);
  }
}

static void Drawsing_callback(WM_MESSAGE * pMsg)
{
	  GUI_PID_STATE psas;
		uint8_t i,j;
	  GUI_COLOR Colorsback;
		static const char *_Ss_Hemp[]={    // ʪ��
		 "\xe6\xb8\xa9\xe5\xba\xa6"
	  };
	  static const char *_Ss_Temp[]={    // �¶�
		 "\xe6\xb9\xbf\xe5\xba\xa6"
	  };
		static const char *_S_Soil[]={   // ����
			"\xe5\x9c\x9f\xe5\xa3\xa4"
		};
		static const char *_S_Air[]={   // ����
			"\xe7\xa9\xba\xe6\xb0\x94"
		};
		switch(pMsg->MsgId)
		{
			case WM_PAINT:   // �ػ溯��
				
				Colorsback=GUI_GetBkColor();
				GUI_SetBkColor(COLOR_BORDER);
				// GUI_SetColor(GUI_BLUE);
				GUI_Clear();
			/* �� ͼ�� */
				for(i=0;i<2;i++)
				{
					GUI_SetBkColor(GUI_WHITE);   
					GUI_SetColor(GUI_YELLOW);
					GUI_ClearRect(140+i*Ca_xSize,35,235+i*Ca_xSize,74);
					GUI_DrawRect(140+i*Ca_xSize,35,235+i*Ca_xSize,74);
					GUI_SetColor(0x50C0FF);
					j=GUI_SetPenSize(10);
					GUI_DrawHLine(48,145+i*Ca_xSize,200+i*Ca_xSize);
					GUI_SetColor(0xFFC050);
					GUI_DrawHLine(65,145+i*Ca_xSize,200+i*Ca_xSize);
					GUI_SetPenSize(j);

					
					GUI_SetFont(&GUI_FontwenshiduSongTi16);
	        GUI_UC_SetEncodeUTF8();
	        GUI_SetColor(0);
					for(j=0;j<GUI_COUNTOF(_Ss_Hemp);j++)
			    {
						GUI_DispStringAt(_Ss_Hemp[j],200+i*Ca_xSize+3,38);		
					// GUI_DispNextLine();
			    }
					for(j=0;j<GUI_COUNTOF(_Ss_Temp);j++)
					{
							GUI_DispStringAt(_Ss_Temp[j],200+i*Ca_xSize+3,58);		
							// GUI_DispNextLine();
					}					
				}
				GUI_SetBkColor(GUI_DARKBLUE);
				GUI_SetColor(GUI_LIGHTRED);
				for(i=0;i<GUI_COUNTOF(_S_Soil);i++)
				{
						GUI_DispStringAt(_S_Soil[i],350,240);		
						// GUI_DispNextLine();
				}		
				GUI_SetColor(GUI_LIGHTBLUE);
				for(i=0;i<GUI_COUNTOF(_S_Air);i++)
				{
						GUI_DispStringAt(_S_Air[i],110,240);		
						// GUI_DispNextLine();
				}	
				GUI_SetFont(GUI_FONT_8X16);
				GUI_SetColor(GUI_WHITE);
				GUI_DispStringAt("C/%",25,62);	
				GUI_DispStringAt("C/%",253,62);		 
		    
				GUI_SetBkColor(COLOR_BORDER); 
				GUI_SetBkColor(Colorsback);
				break;
		  case WM_TOUCH:   //�����豸���� 
			case WM_TOUCH_CHILD:
				i=GUI_TOUCH_GetState(&psas);  //get touch station 
			  i=i;
			  if(psas.Layer==1 && psas.Pressed==0)
				{ 
					   pageChangFlag=0;
				}
				break;
				
			default:
				WM_DefaultProc(pMsg);
		}
}
void setcallback01(void)
{
	 WM_SetCallback(WM_HBKWIN, _cbBk);        // ����  �ص�����
}
void Draw_init()
{
	const WIDGET_EFFECT * pEffectOld;
	GRAPH_SCALE_Handle 		sHand;      //�̶ȶ�����	
  unsigned char              i;

  int                   xSize;
  int                   ySize;

   
	xSize=xSize;
	ySize=ySize;
  xSize      = LCD_GetXSize();
  ySize      = LCD_GetYSize();
	GUI_SelectLayer(1);
	GUI_TOUCH_SetLayer(1);
	pEffectOld=pEffectOld;
	pEffectOld = WIDGET_SetDefaultEffect(&WIDGET_Effect_Simple);	  // ��������С���ߵ�Ĭ��Ч��   ��������Ϊ��
	WM_SetCallback(WM_HBKWIN, Drawsing_callback);        // ����  �ص�����


	/* ���� GRAPH С����*/
	for(i=0;i<2;i++)
	{
		hGraph[i]	= GRAPH_CreateEx(20+230*i, 80, 219, 150, WM_HBKWIN, WM_CF_SHOW | WM_CF_CONST_OUTLINE, 0, 0);
		GRAPH_SetBorder(hGraph[i], 19, 0, 0, 11);// ����ͼ��С���ߵ��������ұ߿�
// 		WM_SetHasTrans (hGraph[i]);    // ����͸���Ա�� �ڱ����ػ�ʱ����͸��
		GRAPH_SetColor (hGraph[i], COLOR_BK,     GRAPH_CI_BK);
		GRAPH_SetColor (hGraph[i], COLOR_BORDER, GRAPH_CI_BORDER);
		GRAPH_SetColor (hGraph[i], COLOR_FRAME,  GRAPH_CI_FRAME);
		GRAPH_SetColor (hGraph[i], COLOR_GRID,   GRAPH_CI_GRID);	
	
		// Adjust grid
		//
		GRAPH_SetGridVis  (hGraph[i], 1);
		GRAPH_SetGridDistX(hGraph[i], 20);  //����ˮƽ ������ ���ص������
		GRAPH_SetGridDistY(hGraph[i], 10);  // ���ô�ֱ������  ���ص� ��
		WM_BringToBottom  (hGraph[i]);    // �����ڷ���ͬ����������  ���Ǳ����ڸ���������
		/* �����̶�����*/ //������ֱ����Ŀ̶�
		sHand=GRAPH_SCALE_Create(146,GUI_TA_VCENTER,GRAPH_SCALE_CF_HORIZONTAL,40);
	 //  GRAPH_SCALE_SetPos(sHand, 120);
		
		
		GRAPH_SCALE_SetTickDist(sHand,40);
		GRAPH_AttachScale(hGraph[i],sHand);    // ���̶���ӵ�ͼ��С������
		/* ����ˮƽ����Ŀ̶� */
		sHand=GRAPH_SCALE_Create(12,GUI_TA_HCENTER,GRAPH_SCALE_CF_VERTICAL,20);
		GRAPH_AttachScale(hGraph[i],sHand);    // ���̶���ӵ�ͼ��С������	
		GRAPH_SCALE_SetOff(sHand, 30);  // ��� �̶ȶ���� ƫ��
	}	
	for(i=0;i<8;i++)
	{
		hData[i][0]=GRAPH_DATA_YT_Create(0x50C0FF,200,0,0);  // �����ݶ��󸽼ӵ�����ͼ��С����
		hData[i][1]=GRAPH_DATA_YT_Create(0xFFC050,200,0,0);  // �����ݶ��󸽼ӵ�����ͼ��С����		
	}

   // �����ݶ�����ӵ�GRAPHС����   
		GRAPH_AttachData(hGraph[0],hData[0][0]);
		GRAPH_AttachData(hGraph[0],hData[0][1]);
		GRAPH_AttachData(hGraph[1],hData[1][0]);
		GRAPH_AttachData(hGraph[1],hData[1][1]);
}
void DrawingsSIngs(int add)
{
	uint8_t i;
	for(i=numbersDrawing;i<200;i++)
	{
		//�ж� ���������Ƿ���Ч 
		GRAPH_DATA_YT_AddValue(hData[0][0], DrawingDataSave[add-1][0][i]+30);
		GRAPH_DATA_YT_AddValue(hData[0][1], DrawingDataSave[add-1][1][i]+30);			
		GRAPH_DATA_YT_AddValue(hData[1][0], DrawingDataSave[add-1][2][i]+30);
		GRAPH_DATA_YT_AddValue(hData[1][1], DrawingDataSave[add-1][3][i]+30);
	}
	for(i=0;i<numbersDrawing;i++)
	{
		GRAPH_DATA_YT_AddValue(hData[0][0], DrawingDataSave[add-1][0][i]+30);
		GRAPH_DATA_YT_AddValue(hData[0][1], DrawingDataSave[add-1][1][i]+30);			
		GRAPH_DATA_YT_AddValue(hData[1][0], DrawingDataSave[add-1][2][i]+30);
		GRAPH_DATA_YT_AddValue(hData[1][1], DrawingDataSave[add-1][3][i]+30);
	}
}
void DrawingNewAnew(int add)
{

	uint8_t i;
/*    ÿ�βɼ�����ʾ 
	int datasD;

	if(last_DrawingNum!=add && add>0 && add<9)   //  ���β���ȵĻ� ��Ҫ�Ȱ��ϴε������������ �� Ȼ�� ��ӱ��ε�����
	{

		GRAPH_DATA_YT_Clear(hData[0][0]);
		GRAPH_DATA_YT_Clear(hData[0][1]);
		GRAPH_DATA_YT_Clear(hData[1][0]);
		GRAPH_DATA_YT_Clear(hData[1][1]);
		last_DrawingNum=add;
	}
	if(add>8) return;
	
	datasD=(int) getInformation[add-1].K_tmp;
  GRAPH_DATA_YT_AddValue(hData[0][0], datasD+30);
	
	datasD=(int) getInformation[add-1].K_hemo;
	GRAPH_DATA_YT_AddValue(hData[0][1], datasD+30);
	
	datasD=(int) getInformation[add-1].T_tmp;
  GRAPH_DATA_YT_AddValue(hData[1][0], datasD+30);

	datasD=(int) getInformation[add-1].T_hemp;
	GRAPH_DATA_YT_AddValue(hData[1][1], datasD+30);
*/
	if(last_DrawingNum!=add && add>0 && add<9)   //  ���β���ȵĻ� ��Ҫ�Ȱ��ϴε������������ �� Ȼ�� ��ӱ��ε�����
	{
		GRAPH_DATA_YT_Clear(hData[0][0]);  // �������
		GRAPH_DATA_YT_Clear(hData[0][1]);  // clean datas
		GRAPH_DATA_YT_Clear(hData[1][0]);  // clean datas
		GRAPH_DATA_YT_Clear(hData[1][1]);  // clean datas
		DrawingsSIngs(add);
		last_DrawingNum=add;   
	}else if(add>8) return;    //��������������8 �˳����򣬣���
	/* ��ͼ ����*/
	if(LastNumbersDrawing != numbersDrawing || (LastNumbersDrawing==0 && numbersDrawing==0))
	{
		DrawingsSIngs(add);
		LastNumbersDrawing=numbersDrawing;
	}
}

