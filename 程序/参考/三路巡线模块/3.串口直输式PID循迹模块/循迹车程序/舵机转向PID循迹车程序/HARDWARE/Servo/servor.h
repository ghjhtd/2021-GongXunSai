#ifndef __SERVOR_H
#define	__SERVOR_H

#include "sys.h"


/********************���ڶ��������*******************/
#define Servo_MID 1250 			//�������м�λ�ò�������Χ1000-2000��Ӧ���0-180��
#define MAX_SERVOR_PWM 400		//��������һ��ת������Ƕ�

/**********************��������***********************/
extern void Servor_Init(void);
extern void Servor_Test(void);
extern void Set_Servor_Angle(u16 PWM);

#endif 
