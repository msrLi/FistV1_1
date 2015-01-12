#include"SHT10.h"

int32_t datas=0;
#define noACK 0 // ��Ӧ��
#define ACK   1 // Ӧ��

#define STATUS_REG_W    0x06   //000   0011    0
#define STATUS_REG_R    0x07   //000   0011    1
#define MEASURE_TEMP    0x03   //000   0001    1
#define MEASURE_HUMI    0x05   //000   0010    1
#define RESET           0x1e   //000   1111    0

/* Private variables ---------------------------------------------------------*/

uint8_t Test_Timetick = 0;
uint16_t Test_Counter = 0;
/* Private function prototypes -----------------------------------------------*/
/**
  * @brief  ��ʼ�� SHT10 IO ��
  * @param  None
  * @retval None
  */
void SHT10_Config(void)
{
    GPIO_Init(SCK_BAS ,SCK_Pin ,GPIO_MODE_OUT_OD_HIZ_SLOW);   //SCK  ��ʼ�� ��� 
    GPIO_Init(SDA_BAS ,SDA_Pin ,GPIO_MODE_OUT_OD_HIZ_SLOW);    
    SDA_H();
    SCK_L();
}
/**
  * @brief  ����SDA����Ϊ���� 
  * @param  None
  * @retval None
  */
void SHT10_SDAIn (void)
{
    GPIO_Init(SDA_BAS,SDA_Pin,GPIO_MODE_IN_FL_NO_IT); 
 
}
/**
  * @brief  ����Ϊ���״̬
  * @param  None
  * @retval None
  */
void SHT10_SDAOut (void)
{
     GPIO_Init(SDA_BAS ,SDA_Pin ,GPIO_MODE_OUT_OD_HIZ_SLOW);
     SDA_H ();
}
/**
  * @brief  д����
  * @param  ��д�������
  * @retval Ӧ��
  */
uint8_t SHT10_WriteByte (uint8_t value)
{ 
    uint8_t i,error=0;  
    //SDA??
    SHT10_SDAOut ();
    
    for( i = 0x80 ; i>0 ; i/=2)             
    { 
        if ( i & value) 
            SDA_H ();            
        else 
            SDA_L ();
        
        SHT10_Delay ();                       
        SCK_H ();                          
        SHT10_Delay ();                       
        SCK_L ();
        SHT10_Delay ();                     
    }
    
    //SDA����
    SHT10_SDAIn ();
    
    SCK_H ();    
    
    error = SDA_R ();   // ��ȡӦ��λ             
    SCK_L (); 
    
    return error;                 
}
/**
  * @brief  ������
  * @param  Ӧ��
  * @retval ��������
  */
uint8_t SHT10_ReadByte (uint8_t Ack)
{ 
    uint8_t i,val=0;
    uint8_t reads=0;
    //����״̬
    SHT10_SDAIn ();  
    
    for (i=0x80;i>0;i/=2)         
    { 
        SHT10_Delay ();  
        SCK_H ();   
        SHT10_Delay (); 
        reads=SDA_R ();
        if(reads) 
            val=(val | i);        //������
        SCK_L ();                                           
    }
    
    //���״̬
    SHT10_SDAOut ();  
    if(Ack)
        SDA_L ();                //Ӧ��Ϊ�͵�ƽ
    else
        SDA_H ();

    SHT10_Delay ();  
    SCK_H ();                     
    SHT10_Delay ();  
    SCK_L ();
    SHT10_Delay ();                                              
    return val;
}
/**
  * @brief  ����
  * @param  ��
  * @retval ��
  */
void SHT10_Start (void)
{  
   //SDA??
    SHT10_SDAOut ();
   
    SCK_L ();                   
    SHT10_Delay ();          
    SCK_H ();
    SHT10_Delay (); 
    SHT10_Delay ();
    SDA_L ();
    SHT10_Delay ();          
    SCK_L ();  
    SHT10_Delay ();          
    SCK_H ();
    SHT10_Delay (); 
    SHT10_Delay (); 
    SDA_H ();                   
    SHT10_Delay ();          
    SCK_L ();    
}
/**
  * @brief  ��������
  * @param  ��
  * @retval ��
  */
void SHT10_ConReset (void)
{
    uint8_t i;
    //���״̬
    SHT10_SDAOut ();
    
    SDA_H ();    //����ߵ�ƽ
    SCK_L ();
   //  SHT10_Delay ();
    for(i = 0 ; i < 9 ; i++)                  
    { 
        SCK_H ();
        SHT10_Delay ();
        SCK_L ();
        SHT10_Delay ();
    }
    
    SHT10_Start ();                   
}
/**
  * @brief  �������
  * @param  ��
  * @retval ��
  */
uint8_t SHT10_SoftReset (void)
{ 
    uint8_t error=0;  
    SHT10_ConReset ();              
    error += SHT10_WriteByte (RESET);       
    return error;                    
}
/**
  * @brief  �¶Ȼ�ʪ�Ȳ���
  * @param  �¶Ȼ���ʪ��ָ�����ݣ�У��ֵָ�룬ģʽ
  * @retval ����
  */
uint8_t SHT10_Measure (uint16_t* pValue, uint8_t* pCheckSum, uint8_t mode)
{ 
    uint8_t error=0;
    uint8_t Value_H = 0;
    uint8_t Value_L = 0;
    uint8_t readsl;
    //����
    SHT10_Start ();                
    switch(mode)
    {                     
    case TEMP: 
        error += SHT10_WriteByte (MEASURE_TEMP); 
        break;
    case HUMI: 
        error += SHT10_WriteByte (MEASURE_HUMI); 
        break;
    default: 
        break;         
    }
    
    //SDA����״̬
    SHT10_SDAIn ();
    //�ȴ�ת����� ������ѭ��  
    
    // datas=0;
    readsl=SDA_R ();
    datas=4000;
    while(readsl && datas>0 )  // 
    {
        readsl=SDA_R ();
         if(datas>0)
          datas--;
         // datas++;
    }
    if(datas<=0) return 0;


    Value_H = SHT10_ReadByte (ACK);    //����λ
    Value_L = SHT10_ReadByte (ACK);    //����λ
   
    *pCheckSum = SHT10_ReadByte (noACK);  //��У����
    
    //���ؽ��
    *pValue = (Value_H << 8) | Value_L;    
    
    return error;
}
/**
  * @brief  �����¶Ⱥ�ʪ������
  * @param  �¶����ݣ�ʪ�����ݣ��¶Ƚ����ʪ�Ƚ��
  * @retval ��
  */
void SHT10_Cal (uint16_t Temp,uint16_t Hum, float* pTempValue,float* pHumValue)
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
void SHT10_Delay (void)
{
    //��ʱ����,i�д��޸�
	 uint16_t i=0;
    for( i = 20 ; i > 0 ; i--)
    {
        ;
    }
}
