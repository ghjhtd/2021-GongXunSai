#ifndef __CONTROL_H
#define __CONTROL_H
#include "sys.h"
  /**************************************************************************
���ߣ�ƽ��С��֮��
�ҵ��Ա�С�꣺http://shop114407458.taobao.com/
**************************************************************************/
#define PI 3.14159265

//extern	int Balance_Pwm,Velocity_Pwm;
//int TIM1_UP_IRQHandler(void);
//int balance(float angle);
//int Position(int Encoder);
int PositionX_PID (int Encoder,int Target);
int PositionY_PID (int Encoder,int Target);
void Set_Pwm(int moto);
void Key(void);
int Xianfu_Pwm(int a);
//u8 Turn_Off(int voltage);
int myabs(int a);
#endif
