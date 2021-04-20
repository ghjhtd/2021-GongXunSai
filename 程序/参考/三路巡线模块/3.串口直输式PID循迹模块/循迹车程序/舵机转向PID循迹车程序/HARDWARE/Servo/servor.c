/**
  ******************************************************************************
  * @文件名 servor.c
  * @文件说明：本文件为关于舵机控制函数文件
  ******************************************************************************/
#include "servor.h"
#include "usart.h"
#include "delay.h"
#include "common.h"
#include "timer.h"

/*@brief: 舵机引脚初始化函数
 * @param: None
 * @return: None
 */
void Servor_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);  
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_11;//设置TIM1_CH4输出PWM波形
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //使能GPIOA外设时钟使能
	GPIO_SetBits(GPIOA,GPIO_Pin_11);				 //PA11 输出
}



/*@brief: 设置舵机角度函数
 * @param:
 *  	  [in] PWM ,范围1000-2000,对应舵机0-180度
 * @return: None
 */
void Set_Servor_Angle(u16 PWM)
{
	TIM_SetCompare4(TIM1,PWM);
}


/*@brief: 舵机初始化函数
 * @param: None
 * @return: None
 */
void Servor_Init(void)
{
	TIM1_PWM_Init(20000-1,72-1);//输出频率50HZ
	Servor_GPIO_Config();
	TIM_SetCompare4(TIM1,Servo_MID);
}


/*@brief: 舵机测试函数，让舵机在多个角度变化
 * @param: None
 * @return: None
 */
void Servor_Test(void)
{
	TIM_SetCompare4(TIM1,1000);
	delay_ms(1000);
	TIM_SetCompare4(TIM1,1300);
	delay_ms(1000);
	TIM_SetCompare4(TIM1,1700);
	delay_ms(1000);
	TIM_SetCompare4(TIM1,2000);
	delay_ms(1000);
}






 
