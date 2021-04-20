#ifndef __CONTROL_H
#define __CONTROL_H
#include "sys.h"
  /**************************************************************************
作者：平衡小车之家
我的淘宝小店：http://shop114407458.taobao.com/
**************************************************************************/
#define PI 3.14159265

 


//extern	int Balance_Pwm,Velocity_Pwm;
//int TIM1_UP_IRQHandler(void);
//int balance(float angle);
//int Position(int Encoder);
int Incremental_PI_A (int Encoder,int Target);
int Incremental_PI_B (int Encoder,int Target);
int Incremental_PI_C (int Encoder,int Target);
int Incremental_PI_D (int Encoder,int Target);

int PositionX_PID (int Encoder,int Target);
int PositionY_PID (int Encoder,int Target);
void Set_Pwm(int moto,int pwm);
void MOTO_FX(int moto,u8 fx);
void Key(void);
int Xianfu_Pwm(int a);
void Motor_Init(void);
//u8 Turn_Off(int voltage);
int myabs(int a);
#endif
