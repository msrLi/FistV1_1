#include"exchangeData.h"
typedef enum {FALSE = 0, TRUE = !FALSE} bool;
/* 
function :
can:
--------number :  ����������
--------ndigit :   С���������λ����
--------*buf   :  �ַ��������׵�ַ
*/
char *my_ftoa(double number,int ndigit,char *buf)    // �� ������ת���� �ַ�����
{  
    long int_part;  
    double float_part;  
	int i;
    char str_int[32];  
    char str_float[32];  
    memset(str_int,0,32);  
    memset(str_float,0,32);  
    int_part = (long)number;  
    float_part = number - int_part;  
    // �������ִ���  
    myitoa(int_part,str_int,10);  
    // С�����ִ���  
    if(ndigit>0)  
    {  
        float_part = fabs( pow(10,ndigit)*float_part);  
        myitoa((long)float_part,str_float,10);  
    }  
    i = strlen(str_int);  
    str_int[i] = '.';  
    strcat(str_int,str_float);  
    strcpy(buf,str_int);  
    return buf;  
} 
/* ����ת����  ������ʽ */
char* myitoa(int num,char*str,int radix)
{/*������*/
	char index[]="0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	unsigned unum;/*�м����*/
	int i=0,j,k;
	char temp;
	/*ȷ��unum��ֵ*/
	if(radix==10&&num<0)/*ʮ���Ƹ���*/
	{
		unum=(unsigned)-num;
		str[i++]='-';
	}
	else unum=(unsigned)num;/*�������*/
	/*ת��*/
	do{
		str[i++]=index[unum%(unsigned)radix];
		unum/=radix;
	}while(unum);
	str[i]='\0';
	/*����*/
	if(str[0]=='-') k=1;/*ʮ���Ƹ���*/
	else k=0;
	
	for(j=k;j<=(i-1)/2;j++)
	{
		temp=str[j];
		str[j]=str[i-1+k-j];
		str[i-1+k-j]=temp;
	}
	return str;
}
int my_atoi(const char * str)
{
	int res=0,begin=0;
	bool minus=FALSE;
	while( *str!= '\0')
	{
		if(begin==0&&(('0'<*str&&*str<'9')|| *str=='-') )         //�ӵ�һ�����ֻ���'-'�ſ�ʼ
		{
			begin=1;
			if(*str == '-')
			{
				minus=TRUE;
				str++;
			}
		}else if( begin==1&&(*str<'0'||*str>'9') )           //������һ�������֣��˳�
			break;
		if(begin==1)
		res=res*10+(*str-'0');                       //����
		str++;
	}
	return minus? -res : res;
}
static int is_digit(char ch)  
{  
    if(ch>='0'&&ch<='9')  
        return 1;  
    else  
        return 0;  
}  
static int is_space(char ch)  
{  
    if(ch==' ')  
        return 1;  
    else  
        return 0;  
}  
double myatof(char *s)  
{  
    double power,value;  
    int i,sign;  
    // assert(s!=NULL);//�ж��ַ����Ƿ�Ϊ��  
	if(s[0]==0 || s[0]=='\0') 
		return 0;
    for(i=0;is_space(s[i]);i++);//��ȥ�ַ���ǰ�Ŀո�  
    sign=(s[i]=='-')?-1:1;  
    if(s[i]=='-'||s[i]=='+')//Ҫ���з���λ��ǰ��һλ  
        i++;  
    for(value=0.0;is_digit(s[i]);i++)//����С����Ǯ������  
        value=value*10.0+(s[i]-'0');  
    if(s[i]=='.')  
        i++;  
    for(power=1.0;is_digit(s[i]);i++)//����С����������  
    {  
        value=value*10.0+(s[i]-'0');  
        power*=10.0;  
    }  
    return sign*value/power;  
}  
