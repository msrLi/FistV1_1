
#ifndef _Bsp_PWM_H_
#define _Bsp_PWM_H_
#include"stm32f4xx.h"
typedef enum {
	ANGLE=0,
	NUMBER=1	
}AngleState;

//#define ANGLE 1
//#define NUMBER
/* 
*   ��ʱ��23  ����PWM 20KHz
*  Time2 CH1  PA15
*				 CH2  PB3
* 			 CH3  PB10
*				 Ch4  PB11
*  Time3 CH1  PC6 
*        CH2  PC7 
*        CH3  PC8 
*        CH4  PC9 
**/
void InitPWMAs20kHz(TIM_TypeDef* TIMx);
/* 
*   ��ʱ��23  ����PWM 20KHz
*  Time4 CH1  PB6
*				 CH2  PB7
* 			 CH3  PB8
*				 Ch4  PB9
*  Time5 CH1  PA0 
*        CH2  PA1
*        CH3  PA2
*        CH4  PA3
**/
void InitPWMAs200Hz(TIM_TypeDef* TIMx);
/* 
*		 Port   ѡ���� 
*    Speed  �ٶ�   ������ʾ��ת   ������ʾ��ת
*          <-4000,0,4000>  
**/
void ChangeSpeed(uint8_t Port,int32_t Speed);
/* 
*	 	 Port   ѡ�����ӿ�
*		 angle  ת���Ƕ�
**/
/* 
*	 	 Port   ѡ�����ӿ�
*		 angle  ת���Ƕ�
**/
void ChangeAngle(uint8_t Port,int32_t angle,AngleState def);
#endif 
