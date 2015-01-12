

#include"actuatorFunction.h"

/* 
*  用于初始化 电机模块 
**/
void motorInit(uint8_t moterNumber)
{
	moterNumber<=MOTOR_2 ? InitPWMAs20kHz(TIM2):InitPWMAs20kHz(TIM3);
}
/*
*   初始化舵机
**/
void servoInit(uint8_t moterNumber)
{
	moterNumber==SERVI_2 ? InitPWMAs200Hz(TIM4):InitPWMAs200Hz(TIM5);
}

