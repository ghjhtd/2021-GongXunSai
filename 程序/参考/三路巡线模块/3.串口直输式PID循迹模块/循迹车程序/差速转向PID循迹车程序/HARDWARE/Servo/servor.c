/**
  ******************************************************************************
  * @�ļ��� servor.c
  * @�ļ�˵�������ļ�Ϊ���ڶ�����ƺ����ļ�
  ******************************************************************************/
#include "servor.h"
#include "usart.h"
#include "delay.h"
#include "common.h"
#include "timer.h"

/*@brief: ������ų�ʼ������
 * @param: None
 * @return: None
 */
void Servor_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);  
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_11;//����TIM1_CH4���PWM����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //ʹ��GPIOA����ʱ��ʹ��
	GPIO_SetBits(GPIOA,GPIO_Pin_11);				 //PA11 ���
}


/*@brief: �����ʼ������
 * @param:
 *  	  [in] angle ,��Χ0-180��
 * @return: None
 */
void Set_Servor_Angle(u8 angle)
{
	u16 PWM;
	PWM=angle*2+360;
	TIM_SetCompare4(TIM1,PWM);
}


/*@brief: �����ʼ������
 * @param: None
 * @return: None
 */
void Servor_Init(void)
{
	TIM1_PWM_Init(7199,199);//���Ƶ��50HZ
//	Servor_GPIO_Config();
//	TIM_SetCompare4(TIM1,Servo_MID);
}


/*@brief: ������Ժ������ö���ڶ���Ƕȱ仯
 * @param: None
 * @return: None
 */
void Servor_Test(void)
{
	TIM_SetCompare4(TIM1,660);
	delay_ms(1000);
	TIM_SetCompare4(TIM1,560);
	delay_ms(1000);
	TIM_SetCompare4(TIM1,460);
	delay_ms(1000);
	TIM_SetCompare4(TIM1,560);
	delay_ms(1000);
}






 
