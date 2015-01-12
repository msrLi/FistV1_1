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
	uint8_t overFlow;     // 函数是否超出 10 个  
	uint8_t PageChage;
	uint8_t pages;        // 当前显示页面 
	uint8_t numberTop;    // 显示第几个 
	uint8_t keyOK;
  Functions KeyDealFunc;	   // 处理函数 指针 哦  no 我干了什么呢  欺负 人啊
}KeyValue;
extern FunctionDescription Software[MAXFUNTION];
extern KeyValue keyValue;
/* 
*     用于显示主界面 
*    显示  程序名称的  界面 
**/
void MainDeskTop(void);
/* 
用于显示 主界面 
*/
void MainDeskTopFist(void);
void showUpdate(void);
void showRun(void);
void hello1(void);
void hell02(void);
#endif 
