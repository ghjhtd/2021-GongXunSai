/**
  ******************************************************************************
  * @�ļ��� motor.c
  * @�ļ�˵����������Ϊ���������غ������ļ�
  ******************************************************************************/
#include "motor.h"
#include "delay.h"
#include "timer.h"

/*@brief: ����������ų�ʼ������
 * @param: None
 * @return: None
 */
void Motor_Gpio_init(void)
{
	 GPIO_InitTypeDef GPIO_InitStructure;
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB , ENABLE);
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE); 
	//���ø�����Ϊ�����������,��TIM4 CH1 TIM4_CH2 TIM4_CH3 TIM4_CH4 PWM���岨��  
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7 |GPIO_Pin_8|GPIO_Pin_9; 
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	 GPIO_Init(GPIOB, &GPIO_InitStructure);
}



/* @brief: �������ֵ���ٶ�PWMֵ
 * @param: 
*		   [in] motor_a: PWMռ�ձ�,��Χ-5000��5000������ֵֵԽ���ٶ�Խ�죬����0����ת��С��0����ת
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

/* @brief: �������ֵ���ٶ�PWMֵ
 * @param: 
*		   [in] motor_b:PWMռ�ձ�,��Χ-5000��5000������ֵֵԽ���ٶ�Խ�죬����0����ת��С��0����ת
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


/* @brief: �����ʼ������
 * @param: 	None
 * @return: None
 */
void Motor_Init(void)
{
	TIM4_PWM_Init(MAX_MOTOR_PWM-1,0);//PWM���Ƶ��14.4KHZ
	Motor_Gpio_init();//������ų�ʼ��
	TIM_SetCompare1(TIM4,0);
	TIM_SetCompare2(TIM4,0);
	TIM_SetCompare3(TIM4,0);
	TIM_SetCompare4(TIM4,0);
}


/* @brief: ���õ��ռ�ձ�
 * @param: 	None
 * @return: None
 */
void Set_Motor_PWM(int PWM)
{
	Set_Pwm_MotorL(PWM);
	Set_Pwm_MotorR(PWM);	
}

/* @brief: ���ֹͣ�����������õ��ֹͣת��
 * @param: 	None
 * @return: None
 */
void MotorStop(void)
{
	Set_Motor_PWM(0);
}




