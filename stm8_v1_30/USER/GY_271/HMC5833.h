
#ifndef HMC5833_H_
#define HMC5833_H_

#include"I2C_IO.h"

#define HMC5883L_SLAVE_ADDRESS    0x3C		/* I2C�䨮?����??�� */

//****************************************
// ?����?HMC5883L?��2?��??��
//****************************************
#define DATA_OUT_X		0x03

typedef struct
{
	int16_t X;
	int16_t Y;
	int16_t Z;

	int16_t X_Min;
	int16_t Y_Min;
	int16_t Z_Min;

	int16_t X_Max;
	int16_t Y_Max;
	int16_t Z_Max;	

	uint8_t	Status;
	
	uint8_t CfgRegA;
	uint8_t CfgRegB;
	uint8_t CfgRegC;
	uint8_t ModeReg;
	
	uint8_t IDReg[3+1];	
}HMC5883L_T;

extern HMC5883L_T g_tMag;

void bsp_InitHMC5883L(void);

void HMC5883L_ReadData(void);
void HMC5883L_WriteByte(uint8_t _ucRegAddr, uint8_t _ucRegData);
uint8_t HMC5883L_ReadByte(uint8_t _ucRegAddr);

#endif 
