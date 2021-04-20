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

//*****************************ѭ��
int Xianfu_Bias(int a);
int Incremental_Juli (int Encoder,int Target);
int Incremental_Bias (int Encoder);
int paral(int zuo,int you, int juli,int Pinxin,int Chuizhi ,int Xunxian);  //ʹС�����߱���ƽ�Уjjuli�����ߵľ��� -1000,1000  Xunxian=1��ʹ��
int MoveTo(int x,int y);  //�ƶ�����ͼ��ָ���������
int MoveX(int x);        //��x�����ƶ�x��
int MOveY(int y);        //��y�����ƶ�y��
int MoveX_T(int aim,int time);        //��x�������ٶ�aim�ƶ�time����
int MOveY_T(int aim,int time);        //��y�������ٶ�aim�ƶ�time����

#endif
