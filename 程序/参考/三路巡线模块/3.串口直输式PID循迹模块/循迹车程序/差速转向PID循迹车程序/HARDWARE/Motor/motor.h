#ifndef __MOTOR_H__
#define __MOTOR_H__

#include "sys.h"

#define PWMA1   TIM4->CCR1  
#define PWMA2   TIM4->CCR2 

#define PWMB1   TIM4->CCR3  
#define PWMB2   TIM4->CCR4

#define MAX_MOTOR_PWM 5000//����������ٶ�ռ�ձ�

/***************�ⲿ��������****************/
extern void Motor_Gpio_init(void);//������ų�ʼ������
extern void Set_Pwm_MotorL(int motor_a);//�������ֵ��PWM
extern void Set_Pwm_MotorR(int motor_b);//�������ֵ��PWM
extern void Motor_Init(void);//�����ʼ����
extern void Set_Motor_PWM(int PWM);//���õ��ռ�ձ�
extern void MotorStop(void);

#endif
