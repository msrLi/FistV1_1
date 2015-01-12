#include"HMC5833.h"

HMC5883L_T g_tMag;		/* ?¡§¨°?¨°???¨¨???¡À?¨¢?¡ê?¡À¡ê¡ä?¨º¦Ì¨º¡À¨ºy?Y */

/*
*********************************************************************************************************
*	o¡¥ ¨ºy ??: bsp_InitHMC5883L
*	1|?¨¹?¦Ì?¡Â: 3?¨º??¡¥HMC5883L
*	D?    2?: ?T
*	¡¤¦Ì ?? ?¦Ì: ?T
*********************************************************************************************************
*/
void bsp_InitHMC5883L(void)
{
	/* ¨¦¨¨??Mode??¡ä??¡Â */
	#if 1
		HMC5883L_WriteByte(0x00, 0x70);	
		HMC5883L_WriteByte(0x01, 0x20);	
		HMC5883L_WriteByte(0x02, 0x00);	
	#else	/* ¡Á?D¡ê¡Á??¡ê¨º? */
		HMC5883L_WriteByte(0x00, 0x70 + 2);	
		HMC5883L_WriteByte(0x01, 0x20);	
		HMC5883L_WriteByte(0x02, 0x00);		
	#endif
	
	
	g_tMag.CfgRegA = HMC5883L_ReadByte(0);
	g_tMag.CfgRegB = HMC5883L_ReadByte(1);
	g_tMag.ModeReg = HMC5883L_ReadByte(2);
	
	g_tMag.IDReg[0] = HMC5883L_ReadByte(10);
	g_tMag.IDReg[1] = HMC5883L_ReadByte(11);
	g_tMag.IDReg[2] = HMC5883L_ReadByte(12);
	g_tMag.IDReg[3] = 0;
	
	/* ¨¦¨¨??¡Á?D?¡Á?¡ä¨®?¦Ì3??¦Ì */
	g_tMag.X_Min = 4096;
	g_tMag.X_Max = -4096;
	
	g_tMag.Y_Min = 4096;
	g_tMag.Y_Max = -4096;

	g_tMag.Z_Min = 4096;
	g_tMag.Z_Max = -4096;
}

/*
*********************************************************************************************************
*	o¡¥ ¨ºy ??: HMC5883L_WriteByte
*	1|?¨¹?¦Ì?¡Â: ?¨° HMC5883L ??¡ä??¡ÂD¡ä¨¨?¨°???¨ºy?Y
*	D?    2?: _ucRegAddr : ??¡ä??¡Â¦Ì??¡¤
*			  _ucRegData : ??¡ä??¡Â¨ºy?Y
*	¡¤¦Ì ?? ?¦Ì: ?T
*********************************************************************************************************
*/
void HMC5883L_WriteByte(uint8_t _ucRegAddr, uint8_t _ucRegData)
{
    i2c_Start();							/* ¡Á¨¹???a¨º?D?o? */

    i2c_SendByte(HMC5883L_SLAVE_ADDRESS);	/* ¡¤¡é?¨ª¨¦¨¨¡À?¦Ì??¡¤+D¡äD?o? */
	i2c_WaitAck();

    i2c_SendByte(_ucRegAddr);				/* ?¨²2???¡ä??¡Â¦Ì??¡¤ */
	i2c_WaitAck();

    i2c_SendByte(_ucRegData);				/* ?¨²2???¡ä??¡Â¨ºy?Y */
	i2c_WaitAck();

    i2c_Stop();                   			/* ¡Á¨¹??¨ª¡ê?1D?o? */
}

/*
*********************************************************************************************************
*	o¡¥ ¨ºy ??: HMC5883L_ReadByte
*	1|?¨¹?¦Ì?¡Â: ?¨¢¨¨? MPU-6050 ??¡ä??¡Â¦Ì?¨ºy?Y
*	D?    2?: _ucRegAddr : ??¡ä??¡Â¦Ì??¡¤
*	¡¤¦Ì ?? ?¦Ì: ?T
*********************************************************************************************************
*/
uint8_t HMC5883L_ReadByte(uint8_t _ucRegAddr)
{
	uint8_t ucData;

	i2c_Start();                  			/* ¡Á¨¹???a¨º?D?o? */
	i2c_SendByte(HMC5883L_SLAVE_ADDRESS);	/* ¡¤¡é?¨ª¨¦¨¨¡À?¦Ì??¡¤+D¡äD?o? */
	i2c_WaitAck();
	i2c_SendByte(_ucRegAddr);     			/* ¡¤¡é?¨ª¡ä?¡ä¡é¦Ì£¤?a¦Ì??¡¤ */
	i2c_WaitAck();

	i2c_Start();                  			/* ¡Á¨¹???a¨º?D?o? */

	i2c_SendByte(HMC5883L_SLAVE_ADDRESS+1); 	/* ¡¤¡é?¨ª¨¦¨¨¡À?¦Ì??¡¤+?¨¢D?o? */
	i2c_WaitAck();

	ucData = i2c_ReadByte();       			/* ?¨¢3???¡ä??¡Â¨ºy?Y */
	i2c_NAck();
	i2c_Stop();                  			/* ¡Á¨¹??¨ª¡ê?1D?o? */
	return ucData;
}


/*
*********************************************************************************************************
*	o¡¥ ¨ºy ??: HMC5883L_ReadData
*	1|?¨¹?¦Ì?¡Â: ?¨¢¨¨? MPU-6050 ¨ºy?Y??¡ä??¡Â¡ê? ?¨¢1?¡À¡ê¡ä??¨²¨¨???¡À?¨¢? g_tMag.  ?¡Â3¨¬D¨°?¨¦¨°??¡§¨º¡À¦Ì¡Â¨®???3¨¬D¨°?¡éD?¨ºy?Y
*	D?    2?: ?T
*	¡¤¦Ì ?? ?¦Ì: ?T
*********************************************************************************************************
*/
void HMC5883L_ReadData(void)
{
	uint8_t ucReadBuf[7];
	uint8_t i;

#if 1 /* ¨¢?D??¨¢ */
	i2c_Start();                  			/* ¡Á¨¹???a¨º?D?o? */
	i2c_SendByte(HMC5883L_SLAVE_ADDRESS);	/* ¡¤¡é?¨ª¨¦¨¨¡À?¦Ì??¡¤+D¡äD?o? */
	i2c_WaitAck();
	i2c_SendByte(DATA_OUT_X);     		/* ¡¤¡é?¨ª¡ä?¡ä¡é¦Ì£¤?a¦Ì??¡¤  */
	i2c_WaitAck();

	i2c_Start();                  			/* ¡Á¨¹???a¨º?D?o? */

	i2c_SendByte(HMC5883L_SLAVE_ADDRESS + 1); /* ¡¤¡é?¨ª¨¦¨¨¡À?¦Ì??¡¤+?¨¢D?o? */
	i2c_WaitAck();

	for (i = 0; i < 6; i++)
	{
		ucReadBuf[i] = i2c_ReadByte();       			/* ?¨¢3???¡ä??¡Â¨ºy?Y */
		i2c_Ack();
	}

	/* ?¨¢¡Á?o¨®¨°???¡Á??¨²¡ê?¨º¡À?? NAck */
	ucReadBuf[6] = i2c_ReadByte();
	i2c_NAck();

	i2c_Stop();                  			/* ¡Á¨¹??¨ª¡ê?1D?o? */

#else	/* ¦Ì£¤¡Á??¨²?¨¢ */
	for (i = 0 ; i < 7; i++)
	{
		ucReadBuf[i] = HMC5883L_ReadByte(DATA_OUT_X + i);
	}
#endif

	/* ???¨¢3?¦Ì?¨ºy?Y¡À¡ê¡ä?¦Ì?¨¨????¨¢11¨¬?¡À?¨¢? */
	g_tMag.X = (int16_t)((ucReadBuf[0] << 8) + ucReadBuf[1]);
	g_tMag.Z = (int16_t)((ucReadBuf[2] << 8) + ucReadBuf[3]);
	g_tMag.Y = (int16_t)((ucReadBuf[4] << 8) + ucReadBuf[5]);
	
	g_tMag.Status = ucReadBuf[6];
	
	/* ¨ª3??¡Á?¡ä¨®?¦Ìo¨ª¡Á?D??¦Ì */
	if ((g_tMag.X > - 2048) && (g_tMag.X < 2048))
	{
		if (g_tMag.X > g_tMag.X_Max)
		{
			g_tMag.X_Max = g_tMag.X;
		}
		if (g_tMag.X < g_tMag.X_Min)
		{
			g_tMag.X_Min = g_tMag.X;
		}	
	}

	if ((g_tMag.Y > - 2048) && (g_tMag.Y < 2048))
	{
		if (g_tMag.Y > g_tMag.Y_Max)
		{
			g_tMag.Y_Max = g_tMag.Y;
		}
		if (g_tMag.Y < g_tMag.Y_Min)
		{
			g_tMag.Y_Min = g_tMag.Y;
		}	
	}
	
	if ((g_tMag.Z > - 2048) && (g_tMag.Z < 2048))
	{
		if (g_tMag.Z > g_tMag.Z_Max)
		{
			g_tMag.Z_Max = g_tMag.Z;
		}
		if (g_tMag.Z < g_tMag.Z_Min)
		{
			g_tMag.Z_Min = g_tMag.Z;
		}	
	}
}

