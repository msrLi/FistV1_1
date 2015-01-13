
#include"UserFunction.h"
FunctionDescription Software[MAXFUNTION]=
{
	{XunxianPro,"danxian"},   //  第一个写函数入口   ，第二个写你写的参数名称
	{XunBaoPRO,"xunbao"},
	{hell02,"LIhuibin2"},


	
};	
void XunxianPro()
{
	//	uint8_t ubts;
	uint8_t i,j,count;
	uint8_t adds=0;
  uint8_t *rece;
	int16_t help_left,help_right;
	int common,error,pwm_l,pwm_r;
	GetValueTime(0);
	GetValueTime(6);
	LCD_ShowString(150,150,"LEFT");
  ShowNumber(190,150,(int)Values[6][0]);//ItUp   //Right
	LCD_ShowString(150,100,"RIGHT");
  ShowNumber(190,100,(int)Values[0][0]);//ItUp   //Left
	help_left=Values[6][0];
	help_right=Values[0][0];
	common = (int)((2048-(help_left+help_right))*1.2);
	error = -(help_right-help_left)*5;
	pwm_l = common-error;
	pwm_r = common+error;
	if(pwm_l>2500) pwm_l=2500;
	else if(pwm_l<-200) pwm_l=-200;
	if(pwm_r>2500) pwm_r=2500;
	else if(pwm_r<-200) pwm_r=-200;
}
uint8_t chukong,king;
uint8_t keyss;
void XunBaoPRO()
{
	chukong=GetValue2(1);
	king=GetValue2(8);
	keyss=GetValue2(2);
	// GetValueTime(0);
	LCD_ShowString(150,100,"RIGHT");
	ShowNumber(190,100,(int)chukong);
	ShowNumber(190,120,(int)king);
	ShowNumber(190,140,(int)keyss);
}
