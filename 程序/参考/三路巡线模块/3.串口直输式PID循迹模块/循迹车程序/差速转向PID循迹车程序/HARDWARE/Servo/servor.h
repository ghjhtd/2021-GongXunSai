#ifndef __SERVOR_H
#define	__SERVOR_H

#include "sys.h"


/********************���ڶ��������*******************/
#define Servo_MID 165 			//�������м�λ�ò���


/**********************��������***********************/
extern void Servo1(void);
extern void Servor_GPIO_Config(void);	
extern void Servor_Init(void);
extern void TIM1_PWM_Init(u16 arr,u16 psc);
extern void Servor_Test(void);

#endif 
