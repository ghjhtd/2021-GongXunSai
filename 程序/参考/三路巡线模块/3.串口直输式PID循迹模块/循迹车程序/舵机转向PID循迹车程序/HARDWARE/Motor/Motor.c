/**
  ******************************************************************************
  * @文件名 motor.c
  * @文件说明：本函数为电机驱动相关函数的文件
  ******************************************************************************/
#include "motor.h"
#include "delay.h"
#include "timer.h"

/*@brief: 电机控制引脚初始化函数
 * @param: None
 * @return: None
 */
void Motor_Gpio_init(void)
{
	 GPIO_InitTypeDef GPIO_InitStructure;
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB , ENABLE);
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE); 
	//设置该引脚为复用输出功能,输TIM4 CH1 TIM4_CH2 TIM4_CH3 TIM4_CH4 PWM脉冲波形  
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7 |GPIO_Pin_8|GPIO_Pin_9; 
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	 GPIO_Init(GPIOB, &GPIO_InitStructure);
}



/* @brief: 设置左轮电机速度PWM值
 * @param: 
*		   [in] motor_a: PWM占空比,范围-5000到5000，绝对值值越大速度越快，大于0正向转，小于0逆向转
 * @return: None
 */
void Set_Pwm_MotorR(int motor_a)
{
	if(motor_a<0)
	{
		PWMA2=MAX_MOTOR_PWM,PWMA1=MAX_MOTOR_PWM+motor_a;
	}		
	else
	{
		PWMA1=MAX_MOTOR_PWM,PWMA2=MAX_MOTOR_PWM-motor_a;
	}		
}

/* @brief: 设置右轮电机速度PWM值
 * @param: 
*		   [in] motor_b:PWM占空比,范围-5000到5000，绝对值值越大速度越快，大于0正向转，小于0逆向转
 * @return: None
 */
void Set_Pwm_MotorL(int motor_b)
{
	if(motor_b<0)
	{
		PWMB1=MAX_MOTOR_PWM,PWMB2=MAX_MOTOR_PWM+motor_b;
	}		
	else
	{
		PWMB2=MAX_MOTOR_PWM,PWMB1=MAX_MOTOR_PWM-motor_b;
	}		
}


/* @brief: 电机初始化函数
 * @param: 	None
 * @return: None
 */
void Motor_Init(void)
{
	TIM4_PWM_Init(MAX_MOTOR_PWM-1,0);//PWM输出频率14.4KHZ
	Motor_Gpio_init();//电机引脚初始化
	TIM_SetCompare1(TIM4,0);
	TIM_SetCompare2(TIM4,0);
	TIM_SetCompare3(TIM4,0);
	TIM_SetCompare4(TIM4,0);
}


/* @brief: 设置电机占空比
 * @param: 	None
 * @return: None
 */
void Set_Motor_PWM(int PWM)
{
	Set_Pwm_MotorL(PWM);
	Set_Pwm_MotorR(PWM);	
}

/* @brief: 电机停止函数，调用让电机停止转动
 * @param: 	None
 * @return: None
 */
void MotorStop(void)
{
	Set_Motor_PWM(0);
}




