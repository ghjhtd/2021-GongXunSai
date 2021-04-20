#include "timer.h"
#include "stm32f10x_tim.h"
#include "usart.h"
#include "sys.h"
/*
 * ////////////////////////////////////////////////////////////////////////////////
 * ������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
 * ALIENTEKս��STM32������
 * ��ʱ�� ��������
 * ����ԭ��@ALIENTEK
 * ������̳:www.openedv.com
 * �޸�����:2012/9/4
 * �汾��V1.1
 * ��Ȩ���У�����ؾ���
 * Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
 * All rights reserved
 * ********************************************************************************
 * V1.1 20120904
 * 1,����TIM3_PWM_Init������
 * 2,����LED0_PWM_VAL�궨�壬����TIM3_CH2����
 * ////////////////////////////////////////////////////////////////////////////////
 */

/*
 * ͨ�ö�ʱ��6�жϳ�ʼ��
 * ����ʱ��ѡ��ΪAPB1��2������APB1Ϊ36M
 * arr���Զ���װֵ��
 * psc��ʱ��Ԥ��Ƶ��
 * ����ʹ�õ��Ƕ�ʱ��3!
 */

/*
 * ͨ�ö�ʱ��6�жϳ�ʼ��
 * ����ʱ��ѡ��ΪAPB1��2������APB1Ϊ36M
 * arr���Զ���װֵ��
 * psc��ʱ��Ԥ��Ƶ��
 * ����ʹ�õ��Ƕ�ʱ��3!
 */
void TIM2_Int_Init( u16 arr, u16 psc )
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef	NVIC_InitStructure;

	RCC_APB1PeriphClockCmd( RCC_APB1Periph_TIM2, ENABLE );                  /* ʱ��ʹ�� */

	TIM_TimeBaseStructure.TIM_Period	= arr;                          /* ��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 ������5000Ϊ500ms */
	TIM_TimeBaseStructure.TIM_Prescaler	= psc;                          /* ����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  10Khz�ļ���Ƶ�� */
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;                            /* ����ʱ�ӷָ�:TDTS = Tck_tim */
	TIM_TimeBaseStructure.TIM_CounterMode	= TIM_CounterMode_Up;           /* TIM���ϼ���ģʽ */
	TIM_TimeBaseInit( TIM2, &TIM_TimeBaseStructure );                       /* ����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ */

	TIM_ITConfig( TIM2, TIM_IT_Update, ENABLE );                            /* ʹ��ָ����TIM3�ж�,��������ж� */

	NVIC_InitStructure.NVIC_IRQChannel			= TIM2_IRQn;    /* TIM3�ж� */
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority	= 0;            /* ��ռ���ȼ�0�� */
	NVIC_InitStructure.NVIC_IRQChannelSubPriority		= 3;            /* �����ȼ�3�� */
	NVIC_InitStructure.NVIC_IRQChannelCmd			= ENABLE;       /* IRQͨ����ʹ�� */
	NVIC_Init( &NVIC_InitStructure );                                       /* ����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ��� */

	TIM_Cmd( TIM2, ENABLE );                                                /* ʹ��TIMx���� */
}


/* ��ʱ��1�жϷ������ */
void TIM2_IRQHandler( void )                                                    /* TIM3�ж� */
{
	int i;
	if ( TIM_GetITStatus( TIM2, TIM_IT_Update ) != RESET )                  /* ���ָ����TIM�жϷ������:TIM �ж�Դ */
	{
		for(i=0;i<8;i++)
		{ if(servo[i][TIME]>=20)
			{
				servo[i][SET_ANGLE]+=servo[i][MOVE_ANGLE];
				servo[i][TIME]-=20;
				servo_set_servo(i,servo[i][SET_ANGLE]);
			}
			
		}

		
		
		
		TIM_ClearITPendingBit( TIM2, TIM_IT_Update );                   /* ���TIMx���жϴ�����λ:TIM �ж�Դ */
	
	}
}
void servo_set_servo(int servo_id,float angle)
{
	int pwm;
	pwm=750+angle/90*500.0;
	switch (servo_id)
	{
		case 5:
			TIM_SetCompare1( TIM3, pwm );
		break;
		case 0:
			TIM_SetCompare2( TIM3, pwm );
		break;
		case 1:
			TIM_SetCompare3( TIM3, pwm );
		break;
		case 4:
			TIM_SetCompare4( TIM3, pwm );
		break;
		case 3:
			TIM_SetCompare1( TIM4, pwm );
		break;
		case 2:
			TIM_SetCompare2( TIM4, pwm );
		break;
		case 6:
			TIM_SetCompare3( TIM4, pwm );
		break;
		case 7:
			TIM_SetCompare4( TIM4, pwm );
		break;
	}
}


/*
 * TIM3 PWM���ֳ�ʼ��
 * PWM�����ʼ��
 * arr���Զ���װֵ
 * psc��ʱ��Ԥ��Ƶ��
 */

void TIM3_PWM_Init( u16 arr, u16 psc )
{
	
	GPIO_InitTypeDef	GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef	TIM_OCInitStructure;


	RCC_APB1PeriphClockCmd( RCC_APB1Periph_TIM3, ENABLE );                          /* ʹ�ܶ�ʱ��3ʱ�� */
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB |RCC_APB2Periph_AFIO, ENABLE );   /* ʹ��GPIO�����AFIO���ù���ģ��ʱ�� */


                      


	GPIO_InitStructure.GPIO_Speed	= GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode	= GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin	= GPIO_Pin_6 | GPIO_Pin_7 ;
	GPIO_Init( GPIOA, &GPIO_InitStructure );

GPIO_InitStructure.GPIO_Speed	= GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode	= GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin	= GPIO_Pin_0 | GPIO_Pin_1 ;
	GPIO_Init( GPIOB, &GPIO_InitStructure );

	/* ��ʼ��TIM */
	TIM_TimeBaseStructure.TIM_Period	= arr;                          /* ��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ */
	TIM_TimeBaseStructure.TIM_Prescaler	= psc;                          /* ����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ */
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;                            /* ����ʱ�ӷָ�:TDTS = Tck_tim */
	TIM_TimeBaseStructure.TIM_CounterMode	= TIM_CounterMode_Up;           /* TIM���ϼ���ģʽ */
	TIM_TimeBaseInit( TIM3, &TIM_TimeBaseStructure );                       /* ����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ */


	/* ��ʼ��TIM Channel  PWMģʽ */
	TIM_OCInitStructure.TIM_OCMode		= TIM_OCMode_PWM1;              /*ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ1  ��С��ʱ��Ч */
	TIM_OCInitStructure.TIM_OutputState	= TIM_OutputState_Enable;       /* �Ƚ����ʹ�� */
	TIM_OCInitStructure.TIM_OCPolarity	= TIM_OCPolarity_High;          /* �������:TIM����Ƚϼ��Ը� ��ЧʱΪ�� */

	TIM_OC1Init( TIM3, &TIM_OCInitStructure );                              /* ����Tָ���Ĳ�����ʼ������TIM3 OC1 */
	TIM_OC1PreloadConfig( TIM3, TIM_OCPreload_Enable );                     /* ʹ��TIM3��CCR1�ϵ�Ԥװ�ؼĴ��� */

	TIM_OC2Init( TIM3, &TIM_OCInitStructure );                              /* ����Tָ���Ĳ�����ʼ������TIM3 OC1 */
	TIM_OC2PreloadConfig( TIM3, TIM_OCPreload_Enable );                     /* ʹ��TIM3��CCR1�ϵ�Ԥװ�ؼĴ��� */

TIM_OC3Init( TIM3, &TIM_OCInitStructure );                              /* ����Tָ���Ĳ�����ʼ������TIM3 OC1 */
	TIM_OC3PreloadConfig( TIM3, TIM_OCPreload_Enable );                     /* ʹ��TIM3��CCR1�ϵ�Ԥװ�ؼĴ��� */

TIM_OC4Init( TIM3, &TIM_OCInitStructure );                              /* ����Tָ���Ĳ�����ʼ������TIM3 OC1 */
	TIM_OC4PreloadConfig( TIM3, TIM_OCPreload_Enable );                     /* ʹ��TIM3��CCR1�ϵ�Ԥװ�ؼĴ��� */

//	                    /* ʹ��TIM3��CCR1�ϵ�Ԥװ�ؼĴ��� */


	TIM_Cmd( TIM3, ENABLE );                                                /* ʹ��TIM3 */
}

void TIM4_PWM_Init( u16 arr, u16 psc )
{
	
	GPIO_InitTypeDef	GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef	TIM_OCInitStructure;

	RCC_APB1PeriphClockCmd( RCC_APB1Periph_TIM4, ENABLE );                          /* ʹ�ܶ�ʱ��3ʱ�� */
	RCC_APB2PeriphClockCmd(  RCC_APB2Periph_GPIOB |RCC_APB2Periph_AFIO, ENABLE );   /* ʹ��GPIO�����AFIO���ù���ģ��ʱ�� */

  GPIO_InitStructure.GPIO_Speed	= GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode	= GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin	= GPIO_Pin_6 | GPIO_Pin_7|GPIO_Pin_8 | GPIO_Pin_9 ;
	GPIO_Init( GPIOB, &GPIO_InitStructure );

	/* ��ʼ��TIM */
	TIM_TimeBaseStructure.TIM_Period	= arr;                          /* ��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ */
	TIM_TimeBaseStructure.TIM_Prescaler	= psc;                          /* ����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ */
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;                            /* ����ʱ�ӷָ�:TDTS = Tck_tim */
	TIM_TimeBaseStructure.TIM_CounterMode	= TIM_CounterMode_Up;           /* TIM���ϼ���ģʽ */
	TIM_TimeBaseInit( TIM4, &TIM_TimeBaseStructure );                       /* ����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ */


	/* ��ʼ��TIM Channel  PWMģʽ */
	TIM_OCInitStructure.TIM_OCMode		= TIM_OCMode_PWM1;              /*ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ1  ��С��ʱ��Ч */
	TIM_OCInitStructure.TIM_OutputState	= TIM_OutputState_Enable;       /* �Ƚ����ʹ�� */
	TIM_OCInitStructure.TIM_OCPolarity	= TIM_OCPolarity_High;          /* �������:TIM����Ƚϼ��Ը� ��ЧʱΪ�� */

	TIM_OC1Init( TIM4, &TIM_OCInitStructure );                              /* ����Tָ���Ĳ�����ʼ������TIM3 OC1 */
	TIM_OC1PreloadConfig( TIM4, TIM_OCPreload_Enable );                     /* ʹ��TIM3��CCR1�ϵ�Ԥװ�ؼĴ��� */

	TIM_OC2Init( TIM4, &TIM_OCInitStructure );                              /* ����Tָ���Ĳ�����ʼ������TIM3 OC1 */
	TIM_OC2PreloadConfig( TIM4, TIM_OCPreload_Enable );                     /* ʹ��TIM3��CCR1�ϵ�Ԥװ�ؼĴ��� */

TIM_OC3Init( TIM4, &TIM_OCInitStructure );                              /* ����Tָ���Ĳ�����ʼ������TIM3 OC1 */
	TIM_OC3PreloadConfig( TIM4, TIM_OCPreload_Enable );                     /* ʹ��TIM3��CCR1�ϵ�Ԥװ�ؼĴ��� */

TIM_OC4Init( TIM4, &TIM_OCInitStructure );                              /* ����Tָ���Ĳ�����ʼ������TIM3 OC1 */
	TIM_OC4PreloadConfig( TIM4, TIM_OCPreload_Enable );                     /* ʹ��TIM3��CCR1�ϵ�Ԥװ�ؼĴ��� */

//	                    /* ʹ��TIM3��CCR1�ϵ�Ԥװ�ؼĴ��� */


	TIM_Cmd( TIM4, ENABLE );                                                /* ʹ��TIM3 */
}

void servo_init(int servo)
{
	switch (servo)
	{
		case 1:
			TIM3_PWM_Init( 9999, 143 );
		  break;
		case 2:
			TIM4_PWM_Init( 9999, 143 );	
		  break;
		case 3:
			TIM4_PWM_Init( 9999, 143 );			
			TIM3_PWM_Init( 9999, 143 );
		  break;
	}
  TIM2_Int_Init(9999,143);
}
//ת�����ԽǶ�
void servo_control(u8 servo_id,float angle,float time)
{
	
	servo[servo_id][LAST_ANGLE]=servo[servo_id][NOW_ANGLE];
	servo[servo_id][SET_ANGLE]=servo[servo_id][LAST_ANGLE];
	servo[servo_id][TIME]=time;
  servo[servo_id][NOW_ANGLE]=angle;
  servo[servo_id][MOVE_ANGLE]=(servo[servo_id][NOW_ANGLE]-servo[servo_id][LAST_ANGLE])/(time/20.0);

}
//ת����ԽǶ�
void servo_move(u8 servo_id,float angle,float time)
{
	
	servo[servo_id][LAST_ANGLE]=servo[servo_id][NOW_ANGLE];
	servo[servo_id][SET_ANGLE]=servo[servo_id][LAST_ANGLE];
	servo[servo_id][TIME]=time;
  servo[servo_id][NOW_ANGLE]=angle+servo[servo_id][LAST_ANGLE];
	if(servo[servo_id][NOW_ANGLE]>90)
		servo[servo_id][NOW_ANGLE]=90;
	if(servo[servo_id][NOW_ANGLE]<-90)
		servo[servo_id][NOW_ANGLE]=-90;
  servo[servo_id][MOVE_ANGLE]=(servo[servo_id][NOW_ANGLE]-servo[servo_id][LAST_ANGLE])/(time/20.0);

}

