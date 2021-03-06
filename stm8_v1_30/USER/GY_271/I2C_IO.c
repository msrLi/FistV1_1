
#include"I2C_IO.h"
/*
*********************************************************************************************************
*
*	?��?��??3? : I2C����???y?��?��?��
*	???t??3? : bsp_i2c_gpio.c
*	��?    ��? : V1.0
*	?��    ?�� : ��?gpio?��?ai2c����??, ������?����STM32F4?�̨�DCPU?��???��?��2?�㨹������|��?2??����???��???�㨹����I2C����???����?2������o����y?��
*
*	DT?????? :
*		��?��?o?  ��??��        ����??     ?��?��
*		V1.0    2013-02-01 armfly  ?y��?����2?
*
*	Copyright (C), 2013-2014, ��2??��3��?���� www.armfly.com
*
*********************************************************************************************************
*/

/*
	��|��??��?�¡�o
	?����??��I2C������??���????���̡¨�? i2c_CheckDevice() ?��2aI2C������?��?��??y3���???o����y?��????GPIO
*/


/*
	��2??��3STM32-V5?a�����? i2c����??GPIO:
 		PH4/I2C2_SCL
 		PH5/I2C2_SDA
*/

/* ?����?I2C����??��??����?GPIO???��, ��??��??D����aDT??????4DD�䨲???��?����?��a??��?SCLo��SDA��?��y?? */


/*
*********************************************************************************************************
*	o�� ��y ??: bsp_InitI2C
*	1|?��?��?��: ????I2C����??��?GPIO��?2����??��?aIO��?��?��?����??
*	D?    2?:  ?T
*	���� ?? ?��: ?T
*********************************************************************************************************
*/
void bsp_InitI2C(void)
{
//	GPIO_InitTypeDef GPIO_InitStructure;
//
//	RCC_AHB1PeriphClockCmd(RCC_I2C_PORT, ENABLE);	/* �䨰?aGPIO����?�� */
//
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;		/* ����?a��?3??�� */
//	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;		/* ����?a?a???�꨺? */
//	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;	/* ��???��-��?����2?��1?�� */
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	/* IO?����?�䨮?��?�� */
//	GPIO_InitStructure.GPIO_Pin = I2C_SCL_PIN | I2C_SDA_PIN;
//	GPIO_Init(GPIO_PORT_I2C, &GPIO_InitStructure);
//      GPIO_Init(GPIOA, GPIO_PIN_3, GPIO_MODE_OUT_PP_LOW_FAST)
   GPIO_Init(GPIO_PORT_I2C, I2C_SCL_PIN, GPIO_MODE_OUT_PP_HIGH_FAST);
   GPIO_Init(GPIO_PORT_I2C, I2C_SDA_PIN, GPIO_MODE_OUT_PP_HIGH_FAST);
	/* ??��???����?1D?o?, ?��??I2C����??��?��??����D������?��?��y?��?�꨺? */
   i2c_Stop();
}

/*
*********************************************************************************************************
*	o�� ��y ??: i2c_Delay
*	1|?��?��?��: I2C����?????��3����?��??��400KHz
*	D?    2?:  ?T
*	���� ?? ?��: ?T
*********************************************************************************************************
*/
static void i2c_Delay(void)
{
	uint8_t i;

	/*??
		CPU?��?��168MHz������??��?��2?Flash??DD, MDK1��3��2?��??��?�ꨮ?������?��?2��?��1?2a2��D??��
		?-?����?��y?a5������?SCL?��?�� = 1.78MHz (?��o?����: 92ms, ?��D��?y3���?��?��?��?��?2��?�¨�?����??��??��?��D�䨺��㨹?�꨺��D��?��?������??)
		?-?����?��y?a10������?SCL?��?�� = 1.1MHz (?��o?����: 138ms, ?��?��?��: 118724B/s)
		?-?����?��y?a30������?SCL?��?�� = 440KHz��? SCL??��???����??1.0us��?SCL�̨���???����??1.2us

		��?��-��?����????2.2K?��������?SCL��?��y??����????0.5us��?��?1???4.7K?����??����?��y????1us

		����?����|��?????400KHz����������??��?��?��?��
	*/
	for (i = 0; i < 30; i++);
}

/*
*********************************************************************************************************
*	o�� ��y ??: i2c_Start
*	1|?��?��?��: CPU����?eI2C����?????��D?o?
*	D?    2?:  ?T
*	���� ?? ?��: ?T
*********************************************************************************************************
*/
void i2c_Start(void)
{
	/* �̡�SCL??��???������?SDA3???��?????��???������?I2C����?????��D?o? */
	I2C_SDA_1();
	I2C_SCL_1();
	i2c_Delay();
	I2C_SDA_0();
	i2c_Delay();
	I2C_SCL_0();
	i2c_Delay();
}

/*
*********************************************************************************************************
*	o�� ��y ??: i2c_Start
*	1|?��?��?��: CPU����?eI2C����??����?1D?o?
*	D?    2?:  ?T
*	���� ?? ?��: ?T
*********************************************************************************************************
*/
void i2c_Stop(void)
{
	/* �̡�SCL??��???������?SDA3???��???��?��???������?I2C����??����?1D?o? */
	I2C_SDA_0();
	I2C_SCL_1();
	i2c_Delay();
	I2C_SDA_1();
}

/*
*********************************************************************************************************
*	o�� ��y ??: i2c_SendByte
*	1|?��?��?��: CPU?��I2C����??������?����?��8bit��y?Y
*	D?    2?:  _ucByte ��o �̨���y����?����?��??��
*	���� ?? ?��: ?T
*********************************************************************************************************
*/
void i2c_SendByte(uint8_t _ucByte)
{
	uint8_t i;

	/* ?������?����??����?????bit7 */
	for (i = 0; i < 8; i++)
	{
		if (_ucByte & 0x80)
		{
			I2C_SDA_1();
		}
		else
		{
			I2C_SDA_0();
		}
		i2c_Delay();
		I2C_SCL_1();
		i2c_Delay();
		I2C_SCL_0();
		if (i == 7)
		{
			 I2C_SDA_1(); // ������?����??
		}
		_ucByte <<= 1;	/* ������?��???bit */
		i2c_Delay();
	}
}

/*
*********************************************************************************************************
*	o�� ��y ??: i2c_ReadByte
*	1|?��?��?��: CPU�䨮I2C����??������??����?8bit��y?Y
*	D?    2?:  ?T
*	���� ?? ?��: ?����?��?��y?Y
*********************************************************************************************************
*/
uint8_t i2c_ReadByte(void)
{
	uint8_t i;
	uint8_t value;

	/* ?����?�̨�1??bit?a��y?Y��?bit7 */
	value = 0;
	for (i = 0; i < 8; i++)
	{
		value <<= 1;
		I2C_SCL_1();
		i2c_Delay();
		if (I2C_SDA_READ())
		{
			value++;
		}
		I2C_SCL_0();
		i2c_Delay();
	}
	return value;
}

/*
*********************************************************************************************************
*	o�� ��y ??: i2c_WaitAck
*	1|?��?��?��: CPU2��������???����?����?2��?����??��?t��?ACK��|��eD?o?
*	D?    2?:  ?T
*	���� ?? ?��: ����??0������??y������|��e��?1������??T?��?t?����|
*********************************************************************************************************
*/
uint8_t i2c_WaitAck(void)
{
	uint8_t re;

	I2C_SDA_1();	/* CPU������?SDA����?? */
	i2c_Delay();
	I2C_SCL_1();	/* CPU?y?��SCL = 1, ��?����?��?t?������??ACK��|��e */
	i2c_Delay();
	if (I2C_SDA_READ())	/* CPU?����?SDA?��??���䨬? */
	{
		re = 1;
	}
	else
	{
		re = 0;
	}
	I2C_SCL_0();
	i2c_Delay();
	return re;
}

/*
*********************************************************************************************************
*	o�� ��y ??: i2c_Ack
*	1|?��?��?��: CPU2��������???ACKD?o?
*	D?    2?:  ?T
*	���� ?? ?��: ?T
*********************************************************************************************************
*/
void i2c_Ack(void)
{
	I2C_SDA_0();	/* CPU?y?��SDA = 0 */
	i2c_Delay();
	I2C_SCL_1();	/* CPU2������1??����?�� */
	i2c_Delay();
	I2C_SCL_0();
	i2c_Delay();
	I2C_SDA_1();	/* CPU������?SDA����?? */
}

/*
*********************************************************************************************************
*	o�� ��y ??: i2c_NAck
*	1|?��?��?��: CPU2������1??NACKD?o?
*	D?    2?:  ?T
*	���� ?? ?��: ?T
*********************************************************************************************************
*/
void i2c_NAck(void)
{
	I2C_SDA_1();	/* CPU?y?��SDA = 1 */
	i2c_Delay();
	I2C_SCL_1();	/* CPU2������1??����?�� */
	i2c_Delay();
	I2C_SCL_0();
	i2c_Delay();
}

/*
*********************************************************************************************************
*	o�� ��y ??: i2c_CheckDevice
*	1|?��?��?��: ?��2aI2C����??������?��?CPU?������?��������?��??����?��?o��?����?������?��|��e����?D????������?��?��?��??��
*	D?    2?:  _Address��o������?��?I2C����??��??��
*	���� ?? ?��: ����???�� 0 ������??y������? ����??1������??�䨬?2a��?
*********************************************************************************************************
*/
uint8_t i2c_CheckDevice(uint8_t _Address)
{
	uint8_t ucAck;

	if (I2C_SDA_READ() && I2C_SCL_READ())
	{
		i2c_Start();		/* ����?��???��D?o? */

		/* ����?��������?��??��+?��D��????bit�ꡧ0 = w��? 1 = r) bit7 ?����? */
		i2c_SendByte(_Address | I2C_WR);
		ucAck = i2c_WaitAck();	/* ?��2a������?��?ACK��|��e */

		i2c_Stop();			/* ����?������?1D?o? */

		return ucAck;
	}
	return 1;	/* I2C����??����3�� */
}






