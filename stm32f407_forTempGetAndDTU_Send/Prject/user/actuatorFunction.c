

#include"actuatorFunction.h"

/* 
*  ���ڳ�ʼ�� ���ģ�� 
**/
void motorInit(uint8_t moterNumber)
{
	moterNumber<=MOTOR_2 ? InitPWMAs20kHz(TIM2):InitPWMAs20kHz(TIM3);
}
/*
*   ��ʼ�����
**/
void servoInit(uint8_t moterNumber)
{
	moterNumber==SERVI_2 ? InitPWMAs200Hz(TIM4):InitPWMAs200Hz(TIM5);
}

