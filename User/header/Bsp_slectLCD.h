#ifndef Bsp_slectLCD_H_
#define Bsp_slectLCD_H_
#include"bsp.h"
#include"string.h"
#define MAXFUNTION  25
typedef void (*Functions)(void);
typedef struct FunctionDescription
{
	Functions pts;
	char FunctioName[20];
}FunctionDescription;

typedef struct KeyValue
{
	uint8_t all_program;
	uint8_t overFlow;     // �����Ƿ񳬳� 10 ��  
	uint8_t PageChage;
	uint8_t pages;        // ��ǰ��ʾҳ�� 
	uint8_t numberTop;    // ��ʾ�ڼ��� 
	uint8_t keyOK;
  Functions KeyDealFunc;	   // ������ ָ�� Ŷ  no �Ҹ���ʲô��  �۸� �˰�
}KeyValue;
extern FunctionDescription Software[MAXFUNTION];
extern KeyValue keyValue;
/* 
*     ������ʾ������ 
*    ��ʾ  �������Ƶ�  ���� 
**/
void MainDeskTop(void);
/* 
������ʾ ������ 
*/
void MainDeskTopFist(void);
void showUpdate(void);
void showRun(void);
void hello1(void);
void hell02(void);
#endif 
