#ifndef __MOTOR_H__
#define __MOTOR_H__

#include "sys.h"

#define PWMA1   TIM4->CCR1  
#define PWMA2   TIM4->CCR2 

#define PWMB1   TIM4->CCR3  
#define PWMB2   TIM4->CCR4

#define MAX_MOTOR_PWM 5000//定义电机最大速度占空比

/***************外部函数声明****************/
extern void Motor_Gpio_init(void);//电机引脚初始化函数
extern void Set_Pwm_MotorL(int motor_a);//设置左轮电机PWM
extern void Set_Pwm_MotorR(int motor_b);//设置右轮电机PWM
extern void Motor_Init(void);//电机初始化函
extern void Set_Motor_PWM(int PWM);//设置电机占空比
extern void MotorStop(void);

#endif
