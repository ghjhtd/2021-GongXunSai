/**
  ******************************************************************************
  * @�ļ��� servor.c
  * @�ļ�˵�������ļ�Ϊ���ڱ�����������غ����ļ�
  ******************************************************************************/
#include "encoder.h"
#include "led.h"
#include "timer.h"

extern int Encoder_A_EXTI;


int Encode_Left=0;			//�������ֱ�������ȡֵ���������Ļᵼ�´���
int Encode_Right=0;			//�������ֱ�������ȡֵ���������Ļᵼ�´���
int Encode_Left_ALL=0;		//�������ֱ������ۼ�ֵ
int Encode_Right_ALL=0;		//�������ֱ������ۼ�ֵ
int	Encode_Speed=0;			//����ͨ����������ȡ��С��ǰ���ٶ�,����0ǰ���ٶȣ�С��0�����ٶ�
int	Encode_Spin_Speed=0;	//ͨ����������ȡ��С����ת�ٶȣ�������ת�ٶȣ�С��0��ת�ٶ�


/*@brief: ��������ʼ������
 * @param: None
 * @return: None
 */
void Encoder_Init(void)
{
	Encoder_Init_TIM2();//������ʼ������
	Encoder_Init_TIM3();//�ҵ����ʼ������
	TIM1_Int_Init(5000-1,72-1);//��ʼ����ʱ1����ʱʱ��5ms�������ж�ȡ����������
}



/* @brief: ��λʱ���ȡ����������
 * @param: 
 *			[in] TIMX ��ȡ����������ֵ��λ����ţ���Χ2-4
 * @return: ��ȡ�ı���������ֵ���붨ʱ����ȡʱ���й�
 */
int Read_Encoder(u8 TIMX)
{
	int Encoder_TIM;    
	switch(TIMX)
	{
		case 2:  Encoder_TIM= (short)TIM2 -> CNT;  TIM2 -> CNT=0;break;
		case 3:  Encoder_TIM= (short)TIM3 -> CNT;  TIM3 -> CNT=0;break;	
		case 4:  Encoder_TIM= (short)TIM4 -> CNT;  TIM4 -> CNT=0;break;	
		default:  Encoder_TIM=0;
	}
	return Encoder_TIM;
}



