
#ifndef Bsp_key_H_
#define Bsp_key_H_
#include"stm32f4xx.h"
#include"Bsp.h"
#include"Bsp_LCD2_4_SPI.h"
// extern uint32_t KeyTimeInit[2];
extern int8_t KeyFlag;
/* 
*  NVIC_Config_Exti 
*  �ⲿ�жϳ�ʼ�� 
**/
static void NVIC_Config_Exti(void);
/* 
*  Exit_config
*  �ⲿ�жϳ�ʼ����
**/
static void Exit_config(void);
/*
*  void Init_key()
**/
void Init_key(void);
/*
*  Deal_keyButtom
**/
void Deal_keyButtom(void);
/*
*
**/
void KeyENCDeal(void);

#endif
