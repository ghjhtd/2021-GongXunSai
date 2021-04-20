#ifndef _TASK_H__
#define _TASK_H__



#include "sys.h"

extern void LedTwinkleTask(void);//LED闪烁任务
extern void KeyTask(void);//按键扫描任务
extern void TraceTask(void);//循迹任务
extern  void TraceConfigTask(void);//循迹传感器配置任务
extern void OledShowTask(void);//OLED显示任务

#endif


