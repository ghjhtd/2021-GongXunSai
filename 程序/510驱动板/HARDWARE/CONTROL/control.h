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

//*****************************循迹
int Xianfu_Bias(int a);
int Incremental_Juli (int Encoder,int Target);
int Incremental_Bias (int Encoder);
int paral(int zuo,int you, int juli,int Pinxin,int Chuizhi ,int Xunxian);  //使小车与线保持平行juli是与线的距离 -1000,1000  Xunxian=1是使能
int MoveTo(int x,int y);  //移动到地图上指定的坐标点
int MoveX(int x);        //在x轴上移动x格
int MOveY(int y);        //在y轴上移动y格
int MoveX_T(int aim,int time);        //在x轴上以速度aim移动time毫秒
int MOveY_T(int aim,int time);        //在y轴上以速度aim移动time毫秒

#endif
