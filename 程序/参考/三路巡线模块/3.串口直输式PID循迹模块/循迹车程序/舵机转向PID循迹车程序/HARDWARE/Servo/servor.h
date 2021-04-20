#ifndef __SERVOR_H
#define	__SERVOR_H

#include "sys.h"


/********************关于舵机的设置*******************/
#define Servo_MID 1250 			//定义舵机中间位置参数，范围1000-2000对应舵机0-180度
#define MAX_SERVOR_PWM 400		//定义舵机向一边转向的最大角度

/**********************函数声明***********************/
extern void Servor_Init(void);
extern void Servor_Test(void);
extern void Set_Servor_Angle(u16 PWM);

#endif 
