/*********************************************************************
*                SEGGER Microcontroller GmbH & Co. KG                *
*        Solutions for real time microcontroller applications        *
**********************************************************************
*                                                                    *
*        (c) 1996 - 2013  SEGGER Microcontroller GmbH & Co. KG       *
*                                                                    *
*        Internet: www.segger.com    Support:  support@segger.com    *
*                                                                    *
**********************************************************************

** emWin V5.22 - Graphical user interface for embedded applications **
All  Intellectual Property rights  in the Software belongs to  SEGGER.
emWin is protected by  international copyright laws.  Knowledge of the
source code may not be used to write a similar product.  This file may
only be used in accordance with the following terms:

The software has been licensed to  ARM LIMITED whose registered office
is situated at  110 Fulbourn Road,  Cambridge CB1 9NJ,  England solely
for  the  purposes  of  creating  libraries  for  ARM7, ARM9, Cortex-M
series,  and   Cortex-R4   processor-based  devices,  sublicensed  and
distributed as part of the  MDK-ARM  Professional  under the terms and
conditions  of  the   End  User  License  supplied  with  the  MDK-ARM
Professional. 
Full source code is available at: www.segger.com

We appreciate your understanding and fairness.
----------------------------------------------------------------------
File        : GUI_TOUCH_X.C
Purpose     : Config / System dependent externals for GUI
---------------------------END-OF-HEADER------------------------------
*/

#include "GUI.h"
#include"Bsp_Touch_SPI.h"
void GUI_TOUCH_X_ActivateX(void) 
{
}
uint16_t TouchX_Vale,TouchY_Vale;
uint8_t Touchflag;
void GUI_TOUCH_X_ActivateY(void) 
{
}
int  GUI_TOUCH_X_MeasureX(void) 
{
	 if(GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_12)==0)
	 {
			Touch_Rd_Addata(&TouchY_Vale,&TouchX_Vale);
		  Touchflag=1;
		  return TouchX_Vale;
	 }else{	
		 Touchflag=0;
		 return 0;
	 }
}

int  GUI_TOUCH_X_MeasureY(void) 
{
	if(Touchflag)
	{
			return TouchY_Vale;
	}else
  return 0;
}


