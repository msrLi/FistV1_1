#ifndef _TASK_GUI_H_
#define _TASK_GUI_H_
#include"includes.h"
#include"EmWinAllHeader.h"
typedef struct DreawPage
{
	uint8_t page;
	uint8_t valueOfPage;
}DreawPage;
extern DreawPage FistPages;
void AppTaskGUI(void *p_arg);          // ��������
void AppTaskGUIRefresh(void *p_arg);   // ˢ������
void AppTaskGUIDrawing(void *p_arg);   // ��ͼˢ�º���
#endif
