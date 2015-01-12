#include"SHT10_01.h"


#define noACK 0 // ��Ӧ��
#define ACK   1 // Ӧ��

#define STATUS_REG_W    0x06   //000   0011    0
#define STATUS_REG_R    0x07   //000   0011    1
#define MEASURE_TEMP    0x03   //000   0001    1
#define MEASURE_HUMI    0x05   //000   0010    1
#define RESET           0x1e   //000   1111    0
uint32_t adfd;
/* Private variables ---------------------------------------------------------*/

uint8_t Test_Timetick_1 = 0;
uint16_t Test_Counter_1 = 0;
/* Private function prototypes -----------------------------------------------*/
/**
  * @brief  ��ʼ�� SHT10 IO ��
  * @param  None
  * @retval None
  */
void SHT10_Config_1(void)
{
    GPIO_Init(SCK_BAS_1,SCK_Pin_1,GPIO_MODE_OUT_OD_HIZ_SLOW);   //SCK  ��ʼ�� ��� 
    GPIO_Init(SDA_BAS_1,SDA_Pin_1,GPIO_MODE_OUT_OD_HIZ_SLOW);    
    SDA_H_1();
    SCK_L_1();
}
/**
  * @brief  ����SDA����Ϊ���� 
  * @param  None
  * @retval None
  */
void SHT10_SDAIn_1(void)
{
    GPIO_Init(SDA_BAS_1,SDA_Pin_1,GPIO_MODE_IN_FL_NO_IT); 
 
}
/**
  * @brief  ����Ϊ���״̬
  * @param  None
  * @retval None
  */
void SHT10_SDAOut_1(void)
{
     GPIO_Init(SDA_BAS_1,SDA_Pin_1,GPIO_MODE_OUT_OD_HIZ_SLOW);
     SDA_H_1();
}
/**
  * @brief  д����
  * @param  ��д�������
  * @retval Ӧ��
  */
uint8_t SHT10_WriteByte_1(uint8_t value)
{ 
    uint8_t i,error=0;  
    //SDA??
    SHT10_SDAOut_1();
    
    for( i = 0x80 ; i>0 ; i/=2)             
    { 
        if ( i & value) 
            SDA_H_1();            
        else 
            SDA_L_1();
        
        SHT10_Delay_1();                       
        SCK_H_1();                          
        SHT10_Delay_1();                       
        SCK_L_1();
        SHT10_Delay_1();                     
    }
    
    //SDA����
    SHT10_SDAIn_1();
    
    SCK_H_1();    
    
    error = SDA_R_1();   // ��ȡӦ��λ             
    SCK_L_1(); 
    
    return error;                 
}
/**
  * @brief  ������
  * @param  Ӧ��
  * @retval ��������
  */
uint8_t SHT10_ReadByte_1(uint8_t Ack)
{ 
    uint8_t i,val=0;
    uint8_t reads=0;
    //����״̬
    SHT10_SDAIn_1();  
    
    for (i=0x80;i>0;i/=2)         
    { 
        SHT10_Delay_1();  
        SCK_H_1();   
        SHT10_Delay_1(); 
        reads=SDA_R_1();
        if(reads) 
            val=(val | i);        //������
        SCK_L_1();                                           
    }
    
    //���״̬
    SHT10_SDAOut_1();  
    if(Ack)
        SDA_L_1();                //Ӧ��Ϊ�͵�ƽ
    else
        SDA_H_1();

    SHT10_Delay_1();  
    SCK_H_1();                     
    SHT10_Delay_1();  
    SCK_L_1();
    SHT10_Delay_1();                                              
    return val;
}
/**
  * @brief  ����
  * @param  ��
  * @retval ��
  */
void SHT10_Start_1(void)
{  
   //SDA??
    SHT10_SDAOut_1();
   
    SCK_L_1();                   
    SHT10_Delay_1();          
    SCK_H_1();
    SHT10_Delay_1(); 
    SHT10_Delay_1();
    SDA_L_1();
    SHT10_Delay_1();          
    SCK_L_1();  
    SHT10_Delay_1();          
    SCK_H_1();
    SHT10_Delay_1(); 
    SHT10_Delay_1(); 
    SDA_H_1();                   
    SHT10_Delay_1();          
    SCK_L_1();    
}
/**
  * @brief  ��������
  * @param  ��
  * @retval ��
  */
void SHT10_ConReset_1(void)
{
    uint8_t i;
    //���״̬
    SHT10_SDAOut_1();
    
    SDA_H_1();    //����ߵ�ƽ
    SCK_L_1();
   //  SHT10_Delay_1();
    for(i = 0 ; i < 9 ; i++)                  
    { 
        SCK_H_1();
        SHT10_Delay_1();
        SCK_L_1();
        SHT10_Delay_1();
    }
    
    SHT10_Start_1();                   
}
/**
  * @brief  �������
  * @param  ��
  * @retval ��
  */
uint8_t SHT10_SoftReset_1(void)
{ 
    uint8_t error=0;  
    SHT10_ConReset_1();              
    error += SHT10_WriteByte_1(RESET);       
    return error;                    
}
/**
  * @brief  �¶Ȼ�ʪ�Ȳ���
  * @param  �¶Ȼ���ʪ��ָ�����ݣ�У��ֵָ�룬ģʽ
  * @retval ����
  */
uint8_t SHT10_Measure_1(uint16_t* pValue, uint8_t* pCheckSum, uint8_t mode)
{ 
    uint8_t error=0;
    uint8_t Value_H = 0;
    uint8_t Value_L = 0;
    uint8_t readsl;
    //����
    SHT10_Start_1();                
    switch(mode)
    {                     
    case TEMP1: 
        error += SHT10_WriteByte_1(MEASURE_TEMP); 
        break;
    case HUMI1: 
        error += SHT10_WriteByte_1(MEASURE_HUMI); 
        break;
    default: 
        break;         
    }
    
    //SDA����״̬
    SHT10_SDAIn_1();
    //�ȴ�ת����� ������ѭ��  
    readsl=SDA_R_1();
    adfd=4000;
    while(readsl && adfd>0 )  // && i
    {
        readsl=SDA_R_1();
        if(adfd>0)
          adfd--;
        
    }
    if(adfd<=0) return 0;

    Value_H = SHT10_ReadByte_1(ACK);    //����λ
    Value_L = SHT10_ReadByte_1(ACK);    //����λ
   
    *pCheckSum = SHT10_ReadByte_1(noACK);  //��У����
    
    //���ؽ��
    *pValue = (Value_H << 8) | Value_L;    
    
    return error;
}
/**
  * @brief  �����¶Ⱥ�ʪ������
  * @param  �¶����ݣ�ʪ�����ݣ��¶Ƚ����ʪ�Ƚ��
  * @retval ��
  */
void SHT10_Cal_1(uint16_t Temp,uint16_t Hum, float* pTempValue,float* pHumValue)
{ 
    const float d1 = -40.1;
    const float d2 = 0.01;
    float Temp_C;
    const float C1 = -2.0468;           
    const float C2 = +0.0367;           
    const float C3 = -0.0000015955;     
    const float T1 = +0.01;             
    const float T2 = +0.00008;           
    //ʪ������ֵ
    float RH_Lin;
    //ʪ����ʵֵ
    float RH_True; 
	
	 //�¶Ƚ�� ������       
    Temp_C = d1 + d2 * Temp;  
    //RH���Խ��
    RH_Lin = C1 + C2 * Hum + C3 * Hum *Hum;
    RH_True = (Temp_C - 25) * (T1 + T2 * Hum) + RH_Lin;
    //�޶���Χ
    if( RH_True > 100 ) RH_True = 100; 
    if( RH_True < 0.01) RH_True = 0.01;
    
    *pTempValue = Temp_C;
    *pHumValue = RH_True;
    
}
/**
  * @brief  ��ʱ����
  * @param  ��
  * @retval ��
  */
void SHT10_Delay_1(void)
{
    //��ʱ����,i�д��޸�
	 uint16_t i=0;
    for( i = 20 ; i > 0 ; i--)
    {
        ;
    }
}





