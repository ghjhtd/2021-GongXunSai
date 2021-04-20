#ifndef __SERVOR_H
#define	__SERVOR_H

#include "sys.h"


/********************关于舵机的设置*******************/
#define Servo_MID 165 			//定义舵机中间位置参数


/**********************函数声明***********************/
extern void Servo1(void);
extern void Servor_GPIO_Config(void);	
extern void Servor_Init(void);
extern void TIM1_PWM_Init(u16 arr,u16 psc);
extern void Servor_Test(void);

#endif 
