#include"HMC5833.h"

HMC5883L_T g_tMag;		/* ?����?��???��???��?��?��?�����?���̨�����y?Y */

/*
*********************************************************************************************************
*	o�� ��y ??: bsp_InitHMC5883L
*	1|?��?��?��: 3?��??��HMC5883L
*	D?    2?: ?T
*	���� ?? ?��: ?T
*********************************************************************************************************
*/
void bsp_InitHMC5883L(void)
{
	/* ����??Mode??��??�� */
	#if 1
		HMC5883L_WriteByte(0x00, 0x70);	
		HMC5883L_WriteByte(0x01, 0x20);	
		HMC5883L_WriteByte(0x02, 0x00);	
	#else	/* ��?D���??�꨺? */
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
	
	/* ����??��?D?��?�䨮?��3??�� */
	g_tMag.X_Min = 4096;
	g_tMag.X_Max = -4096;
	
	g_tMag.Y_Min = 4096;
	g_tMag.Y_Max = -4096;

	g_tMag.Z_Min = 4096;
	g_tMag.Z_Max = -4096;
}

/*
*********************************************************************************************************
*	o�� ��y ??: HMC5883L_WriteByte
*	1|?��?��?��: ?�� HMC5883L ??��??��D�䨨?��???��y?Y
*	D?    2?: _ucRegAddr : ??��??�¦�??��
*			  _ucRegData : ??��??�¨�y?Y
*	���� ?? ?��: ?T
*********************************************************************************************************
*/
void HMC5883L_WriteByte(uint8_t _ucRegAddr, uint8_t _ucRegData)
{
    i2c_Start();							/* ����???a��?D?o? */

    i2c_SendByte(HMC5883L_SLAVE_ADDRESS);	/* ����?��������?��??��+D��D?o? */
	i2c_WaitAck();

    i2c_SendByte(_ucRegAddr);				/* ?��2???��??�¦�??�� */
	i2c_WaitAck();

    i2c_SendByte(_ucRegData);				/* ?��2???��??�¨�y?Y */
	i2c_WaitAck();

    i2c_Stop();                   			/* ����??����?1D?o? */
}

/*
*********************************************************************************************************
*	o�� ��y ??: HMC5883L_ReadByte
*	1|?��?��?��: ?����? MPU-6050 ??��??�¦�?��y?Y
*	D?    2?: _ucRegAddr : ??��??�¦�??��
*	���� ?? ?��: ?T
*********************************************************************************************************
*/
uint8_t HMC5883L_ReadByte(uint8_t _ucRegAddr)
{
	uint8_t ucData;

	i2c_Start();                  			/* ����???a��?D?o? */
	i2c_SendByte(HMC5883L_SLAVE_ADDRESS);	/* ����?��������?��??��+D��D?o? */
	i2c_WaitAck();
	i2c_SendByte(_ucRegAddr);     			/* ����?����?���̣�?a��??�� */
	i2c_WaitAck();

	i2c_Start();                  			/* ����???a��?D?o? */

	i2c_SendByte(HMC5883L_SLAVE_ADDRESS+1); 	/* ����?��������?��??��+?��D?o? */
	i2c_WaitAck();

	ucData = i2c_ReadByte();       			/* ?��3???��??�¨�y?Y */
	i2c_NAck();
	i2c_Stop();                  			/* ����??����?1D?o? */
	return ucData;
}


/*
*********************************************************************************************************
*	o�� ��y ??: HMC5883L_ReadData
*	1|?��?��?��: ?����? MPU-6050 ��y?Y??��??�¡�? ?��1?�����??����???��?��? g_tMag.  ?��3��D��?����??�������̡¨�???3��D��?��D?��y?Y
*	D?    2?: ?T
*	���� ?? ?��: ?T
*********************************************************************************************************
*/
void HMC5883L_ReadData(void)
{
	uint8_t ucReadBuf[7];
	uint8_t i;

#if 1 /* ��?D??�� */
	i2c_Start();                  			/* ����???a��?D?o? */
	i2c_SendByte(HMC5883L_SLAVE_ADDRESS);	/* ����?��������?��??��+D��D?o? */
	i2c_WaitAck();
	i2c_SendByte(DATA_OUT_X);     		/* ����?����?���̣�?a��??��  */
	i2c_WaitAck();

	i2c_Start();                  			/* ����???a��?D?o? */

	i2c_SendByte(HMC5883L_SLAVE_ADDRESS + 1); /* ����?��������?��??��+?��D?o? */
	i2c_WaitAck();

	for (i = 0; i < 6; i++)
	{
		ucReadBuf[i] = i2c_ReadByte();       			/* ?��3???��??�¨�y?Y */
		i2c_Ack();
	}

	/* ?����?o����???��??����?����?? NAck */
	ucReadBuf[6] = i2c_ReadByte();
	i2c_NAck();

	i2c_Stop();                  			/* ����??����?1D?o? */

#else	/* �̣���??��?�� */
	for (i = 0 ; i < 7; i++)
	{
		ucReadBuf[i] = HMC5883L_ReadByte(DATA_OUT_X + i);
	}
#endif

	/* ???��3?��?��y?Y�����?��?��????��11��?��?��? */
	g_tMag.X = (int16_t)((ucReadBuf[0] << 8) + ucReadBuf[1]);
	g_tMag.Z = (int16_t)((ucReadBuf[2] << 8) + ucReadBuf[3]);
	g_tMag.Y = (int16_t)((ucReadBuf[4] << 8) + ucReadBuf[5]);
	
	g_tMag.Status = ucReadBuf[6];
	
	/* ��3??��?�䨮?��o����?D??�� */
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

