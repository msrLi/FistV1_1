
#include"ADc.h"
/* 
*  name : InitADC
*       : ��������AD��ʼ��
**/
void InitADC(void)
{
  ADC1_DeInit();
  ADC1_Init(ADC1_CONVERSIONMODE_SINGLE, ADC1_CHANNEL_3, ADC1_PRESSEL_FCPU_D2, ADC1_EXTTRIG_TIM, DISABLE, ADC1_ALIGN_RIGHT, ADC1_SCHMITTTRIG_CHANNEL3, ENABLE);
  ADC1_Cmd(ENABLE);
}
/*
*  name : readADCs
*       : ��ȡADֵ�ú���
**/
uint16_t readADCs(void)
{
  FlagStatus flag_status;
  uint16_t u16_adc1_value;
  ADC1_StartConversion();
  flag_status = ADC1_GetFlagStatus(ADC1_FLAG_EOC);
  while(flag_status == RESET); // SET or RESET
  u16_adc1_value = ADC1_GetConversionValue();
  return u16_adc1_value;
}

