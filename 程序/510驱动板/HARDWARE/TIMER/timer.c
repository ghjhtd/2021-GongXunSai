#include "timer.h"
#include "led.h"
#include "usart.h"
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
void TIM6_Int_Init( u16 arr, u16 psc )
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef	NVIC_InitStructure;

	RCC_APB1PeriphClockCmd( RCC_APB1Periph_TIM6, ENABLE );                  /* ʱ��ʹ�� */

	TIM_TimeBaseStructure.TIM_Period	= arr;                          /* ��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 ������5000Ϊ500ms */
	TIM_TimeBaseStructure.TIM_Prescaler	= psc;                          /* ����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  10Khz�ļ���Ƶ�� */
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;                            /* ����ʱ�ӷָ�:TDTS = Tck_tim */
	TIM_TimeBaseStructure.TIM_CounterMode	= TIM_CounterMode_Up;           /* TIM���ϼ���ģʽ */
	TIM_TimeBaseInit( TIM6, &TIM_TimeBaseStructure );                       /* ����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ */

	TIM_ITConfig( TIM6, TIM_IT_Update, ENABLE );                            /* ʹ��ָ����TIM3�ж�,��������ж� */

	NVIC_InitStructure.NVIC_IRQChannel			= TIM6_IRQn;    /* TIM3�ж� */
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority	= 0;            /* ��ռ���ȼ�0�� */
	NVIC_InitStructure.NVIC_IRQChannelSubPriority		= 2;            /* �����ȼ�2�� */
	NVIC_InitStructure.NVIC_IRQChannelCmd			= ENABLE;       /* IRQͨ����ʹ�� */
	NVIC_Init( &NVIC_InitStructure );                                       /* ����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ��� */

	TIM_Cmd( TIM6, ENABLE );                                                /* ʹ��TIMx���� */
}

/*
 * ͨ�ö�ʱ��6�жϳ�ʼ��
 * ����ʱ��ѡ��ΪAPB1��2������APB1Ϊ36M
 * arr���Զ���װֵ��
 * psc��ʱ��Ԥ��Ƶ��
 * ����ʹ�õ��Ƕ�ʱ��3!
 */
void TIM7_Int_Init( u16 arr, u16 psc )
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef	NVIC_InitStructure;

	RCC_APB1PeriphClockCmd( RCC_APB1Periph_TIM7, ENABLE );                  /* ʱ��ʹ�� */

	TIM_TimeBaseStructure.TIM_Period	= arr;                          /* ��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 ������5000Ϊ500ms */
	TIM_TimeBaseStructure.TIM_Prescaler	= psc;                          /* ����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  10Khz�ļ���Ƶ�� */
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;                            /* ����ʱ�ӷָ�:TDTS = Tck_tim */
	TIM_TimeBaseStructure.TIM_CounterMode	= TIM_CounterMode_Up;           /* TIM���ϼ���ģʽ */
	TIM_TimeBaseInit( TIM7, &TIM_TimeBaseStructure );                       /* ����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ */

	TIM_ITConfig( TIM7, TIM_IT_Update, ENABLE );                            /* ʹ��ָ����TIM3�ж�,��������ж� */

	NVIC_InitStructure.NVIC_IRQChannel			= TIM7_IRQn;    /* TIM3�ж� */
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority	= 0;            /* ��ռ���ȼ�0�� */
	NVIC_InitStructure.NVIC_IRQChannelSubPriority		= 3;            /* �����ȼ�3�� */
	NVIC_InitStructure.NVIC_IRQChannelCmd			= ENABLE;       /* IRQͨ����ʹ�� */
	NVIC_Init( &NVIC_InitStructure );                                       /* ����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ��� */

	TIM_Cmd( TIM7, ENABLE );                                                /* ʹ��TIMx���� */
}

//��ʱ��1�����жϳ�ʼ��
void TIM1_Int_Init( u16 arr, u16 psc )
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef	NVIC_InitStructure;

	RCC_APB2PeriphClockCmd( RCC_APB2Periph_TIM1, ENABLE );                  /* ʱ��ʹ�� */

	TIM_TimeBaseStructure.TIM_Period	= arr;                          /* ��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 ������5000Ϊ500ms */
	TIM_TimeBaseStructure.TIM_Prescaler	= psc;                          /* ����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  10Khz�ļ���Ƶ�� */
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;     /* ����ʱ�ӷָ�:TDTS = Tck_tim */
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;     	
	TIM_TimeBaseStructure.TIM_CounterMode	= TIM_CounterMode_Up;           /* TIM���ϼ���ģʽ */
	TIM_TimeBaseInit( TIM1, &TIM_TimeBaseStructure );                       /* ����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ */

	TIM_ITConfig( TIM8, TIM_IT_Update, ENABLE );                            /* ʹ��ָ����TIM3�ж�,��������ж� */

	NVIC_InitStructure.NVIC_IRQChannel			= TIM1_UP_IRQn;    /* TIM3�ж� */
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority	= 0;            /* ��ռ���ȼ�0�� */
	NVIC_InitStructure.NVIC_IRQChannelSubPriority		= 3;            /* �����ȼ�3�� */
	NVIC_InitStructure.NVIC_IRQChannelCmd			= ENABLE;       /* IRQͨ����ʹ�� */
	NVIC_Init( &NVIC_InitStructure );                                       /* ����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ��� */

	TIM_Cmd( TIM1, ENABLE );                                                /* ʹ��TIMx���� */
}


/* ��ʱ��1�жϷ������ */
void TIM1_UP_IRQHandler( void )                                                    /* TIM3�ж� */
{
	if ( TIM_GetITStatus( TIM1, TIM_IT_Update ) != RESET )                  /* ���ָ����TIM�жϷ������:TIM �ж�Դ */
	{
		
		TIM_ClearITPendingBit( TIM1, TIM_IT_Update );                   /* ���TIMx���жϴ�����λ:TIM �ж�Դ */
		LED1 = !LED1;
	}
}

/*
 * TIM8 PWM���ֳ�ʼ��
 * PWM�����ʼ��
 * arr���Զ���װֵ
 * psc��ʱ��Ԥ��Ƶ��
 */

void TIM8_PWM_Init(u16 arr,u16 psc)
{		 		
	 GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);// 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC| RCC_APB2Periph_AFIO, ENABLE);  //ʹ��GPIO����ʱ��ʹ��
 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9; //TIM_CH1 //TIM_CH4
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  ����Ƶ
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ

 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ1
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_Pulse = 0;                            //���ô�װ�벶��ȽϼĴ���������ֵ
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;     //�������:TIM����Ƚϼ��Ը�
	TIM_OC1Init(TIM8, &TIM_OCInitStructure);  //����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx
	TIM_OC2Init(TIM8, &TIM_OCInitStructure);  //����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx
	TIM_OC3Init(TIM8, &TIM_OCInitStructure);  //����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx
	TIM_OC4Init(TIM8, &TIM_OCInitStructure);  //����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx

  TIM_CtrlPWMOutputs(TIM8,ENABLE);	//MOE �����ʹ��	

	TIM_OC1PreloadConfig(TIM8, TIM_OCPreload_Enable);  //CH1Ԥװ��ʹ��	
	TIM_OC2PreloadConfig(TIM8, TIM_OCPreload_Enable);  //CH1Ԥװ��ʹ��	
	TIM_OC3PreloadConfig(TIM8, TIM_OCPreload_Enable);  //CH1Ԥװ��ʹ��		
	TIM_OC4PreloadConfig(TIM8, TIM_OCPreload_Enable);  //CH4Ԥװ��ʹ��	 
	
	TIM_ARRPreloadConfig(TIM8, ENABLE); //ʹ��TIMx��ARR�ϵ�Ԥװ�ؼĴ���
	
	TIM_Cmd(TIM8, ENABLE);  //ʹ��TIM
 
} 


/*
 * TIM3 PWM���ֳ�ʼ��
 * PWM�����ʼ��
 * arr���Զ���װֵ
 * psc��ʱ��Ԥ��Ƶ��
 */

void TIM3_PWM_Init( u16 arr, u16 psc )
{
	/*
	 * ȫ��ӳ�䣬��TIM3_CH2ӳ�䵽PB5
	 * ����STM32���Ĳο��ֲ�2010�еڵ�119ҳ��֪��
	 * ��û����ӳ��ʱ��TIM3���ĸ�ͨ��CH1��CH2��CH3��CH4�ֱ��ӦPA6��PA7,PB0,PB1
	 * ��������ӳ��ʱ��TIM3���ĸ�ͨ��CH1��CH2��CH3��CH4�ֱ��ӦPB4��PB5,PB0,PB1
	 * ����ȫ��ӳ��ʱ��TIM3���ĸ�ͨ��CH1��CH2��CH3��CH4�ֱ��ӦPC6��PC7,PC8,PC9
	 * Ҳ����˵����ȫ��ӳ��֮���ĸ�ͨ����PWM������ŷֱ�ΪPC6��PC7,PC8,PC9�������õ���ͨ��1��ͨ��2��
	 * ���Զ�Ӧ����ΪPC6��PC7,PC8,PC9�������õ���ͨ��1��ͨ��2�����Զ�Ӧ����Ϊ
	 */

	GPIO_InitTypeDef	GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef	TIM_OCInitStructure;


	RCC_APB1PeriphClockCmd( RCC_APB1Periph_TIM3, ENABLE );                          /* ʹ�ܶ�ʱ��3ʱ�� */
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB |RCC_APB2Periph_AFIO, ENABLE );   /* ʹ��GPIO�����AFIO���ù���ģ��ʱ�� */


                            /* Timer3 ��ȫ��ӳ�� */


	/* ����PC6��PC7��PC8��PC9Ϊ������������4·PWM */
	GPIO_InitStructure.GPIO_Speed	= GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode	= GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin	= GPIO_Pin_6 | GPIO_Pin_7 ;
	GPIO_Init( GPIOA, &GPIO_InitStructure );

GPIO_InitStructure.GPIO_Speed	= GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode	= GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin	= GPIO_Pin_0 | GPIO_Pin_1 ;
	GPIO_Init( GPIOB, &GPIO_InitStructure );

	/* ��ʼ��TIM3 */
	TIM_TimeBaseStructure.TIM_Period	= arr;                          /* ��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ */
	TIM_TimeBaseStructure.TIM_Prescaler	= psc;                          /* ����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ */
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;                            /* ����ʱ�ӷָ�:TDTS = Tck_tim */
	TIM_TimeBaseStructure.TIM_CounterMode	= TIM_CounterMode_Up;           /* TIM���ϼ���ģʽ */
	TIM_TimeBaseInit( TIM3, &TIM_TimeBaseStructure );                       /* ����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ */


	/* ��ʼ��TIM3 Channel 1 PWMģʽ */
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


void TIM2_Int_Init( u16 arr, u16 psc )
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef	NVIC_InitStructure;

	RCC_APB1PeriphClockCmd( RCC_APB1Periph_TIM2, ENABLE );                  /* ʱ��ʹ�� */

	/* ��ʱ��TIM2��ʼ�� */
	TIM_TimeBaseStructure.TIM_Period	= arr;                          /* ��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ */
	TIM_TimeBaseStructure.TIM_Prescaler	= psc;                          /* ����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ */
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;                 /* ����ʱ�ӷָ�:TDTS = Tck_tim */
	TIM_TimeBaseStructure.TIM_CounterMode	= TIM_CounterMode_Up;           /* TIM���ϼ���ģʽ */
	TIM_TimeBaseInit( TIM2, &TIM_TimeBaseStructure );                       /* ����ָ���Ĳ�����ʼ��TIMx��ʱ�������λ */

	TIM_ITConfig( TIM2, TIM_IT_Update, ENABLE );
	/* ʹ��ָ����TIM2�ж�,��������ж� */

	/* �ж����ȼ�NVIC���� */
	NVIC_InitStructure.NVIC_IRQChannel			= TIM2_IRQn;    /* TIM2�ж� */
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority	= 0;            /* ��ռ���ȼ�0�� */
	NVIC_InitStructure.NVIC_IRQChannelSubPriority		= 3;            /* �����ȼ�3�� */
	NVIC_InitStructure.NVIC_IRQChannelCmd			= ENABLE;       /* IRQͨ����ʹ�� */
	NVIC_Init( &NVIC_InitStructure );                                       /* ��ʼ��NVIC�Ĵ��� */


	 TIM_Cmd(TIM2, ENABLE);  //ʹ��TIMx 
}




void TIM4_Int_Init( u16 arr, u16 psc )
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef	NVIC_InitStructure;

	RCC_APB1PeriphClockCmd( RCC_APB1Periph_TIM4, ENABLE );                  /* ʱ��ʹ�� */

	/* ��ʱ��TIM4��ʼ�� */
	TIM_TimeBaseStructure.TIM_Period	= arr;                          /* ��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ */
	TIM_TimeBaseStructure.TIM_Prescaler	= psc;                          /* ����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ */
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;                 /* ����ʱ�ӷָ�:TDTS = Tck_tim */
	TIM_TimeBaseStructure.TIM_CounterMode	= TIM_CounterMode_Up;           /* TIM���ϼ���ģʽ */
	TIM_TimeBaseInit( TIM4, &TIM_TimeBaseStructure );                       /* ����ָ���Ĳ�����ʼ��TIMx��ʱ�������λ */

	TIM_ITConfig( TIM4, TIM_IT_Update, ENABLE );
	/* ʹ��ָ����TIM4�ж�,��������ж� */

	/* �ж����ȼ�NVIC���� */
	NVIC_InitStructure.NVIC_IRQChannel			= TIM4_IRQn;    /* TIM4�ж� */
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority	= 1;            /* ��ռ���ȼ�0�� */
	NVIC_InitStructure.NVIC_IRQChannelSubPriority		= 2;            /* �����ȼ�3�� */
	NVIC_InitStructure.NVIC_IRQChannelCmd			= ENABLE;       /* IRQͨ����ʹ�� */
	NVIC_Init( &NVIC_InitStructure );                                       /* ��ʼ��NVIC�Ĵ��� */


	 TIM_Cmd(TIM4, ENABLE);  //ʹ��TIMx 
}


void TIM5_Int_Init( u16 arr, u16 psc )
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef	NVIC_InitStructure;

	RCC_APB1PeriphClockCmd( RCC_APB1Periph_TIM5, ENABLE );                  /* ʱ��ʹ�� */

	/* ��ʱ��TIM5��ʼ�� */
	TIM_TimeBaseStructure.TIM_Period	= arr;                          /* ��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ */
	TIM_TimeBaseStructure.TIM_Prescaler	= psc;                          /* ����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ */
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;                 /* ����ʱ�ӷָ�:TDTS = Tck_tim */
	TIM_TimeBaseStructure.TIM_CounterMode	= TIM_CounterMode_Up;           /* TIM���ϼ���ģʽ */
	TIM_TimeBaseInit( TIM5, &TIM_TimeBaseStructure );                       /* ����ָ���Ĳ�����ʼ��TIMx��ʱ�������λ */

	TIM_ITConfig( TIM5, TIM_IT_Update, ENABLE );
	/* ʹ��ָ����TIM5�ж�,��������ж� */

	/* �ж����ȼ�NVIC���� */
	NVIC_InitStructure.NVIC_IRQChannel			= TIM5_IRQn;    /* TIM5�ж� */
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority	= 0;            /* ��ռ���ȼ�0�� */
	NVIC_InitStructure.NVIC_IRQChannelSubPriority		= 3;            /* �����ȼ�3�� */
	NVIC_InitStructure.NVIC_IRQChannelCmd			= ENABLE;       /* IRQͨ����ʹ�� */
	NVIC_Init( &NVIC_InitStructure );                                       /* ��ʼ��NVIC�Ĵ��� */


	 TIM_Cmd(TIM5, ENABLE);  //ʹ��TIMx 
}

