#include "timer.h"
#include "stm32f10x_tim.h"
#include "usart.h"
#include "sys.h"
/*
 * ////////////////////////////////////////////////////////////////////////////////
 * 本程序只供学习使用，未经作者许可，不得用于其它任何用途
 * ALIENTEK战舰STM32开发板
 * 定时器 驱动代码
 * 正点原子@ALIENTEK
 * 技术论坛:www.openedv.com
 * 修改日期:2012/9/4
 * 版本：V1.1
 * 版权所有，盗版必究。
 * Copyright(C) 广州市星翼电子科技有限公司 2009-2019
 * All rights reserved
 * ********************************************************************************
 * V1.1 20120904
 * 1,增加TIM3_PWM_Init函数。
 * 2,增加LED0_PWM_VAL宏定义，控制TIM3_CH2脉宽
 * ////////////////////////////////////////////////////////////////////////////////
 */

/*
 * 通用定时器6中断初始化
 * 这里时钟选择为APB1的2倍，而APB1为36M
 * arr：自动重装值。
 * psc：时钟预分频数
 * 这里使用的是定时器3!
 */

/*
 * 通用定时器6中断初始化
 * 这里时钟选择为APB1的2倍，而APB1为36M
 * arr：自动重装值。
 * psc：时钟预分频数
 * 这里使用的是定时器3!
 */
void TIM2_Int_Init( u16 arr, u16 psc )
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef	NVIC_InitStructure;

	RCC_APB1PeriphClockCmd( RCC_APB1Periph_TIM2, ENABLE );                  /* 时钟使能 */

	TIM_TimeBaseStructure.TIM_Period	= arr;                          /* 设置在下一个更新事件装入活动的自动重装载寄存器周期的值	 计数到5000为500ms */
	TIM_TimeBaseStructure.TIM_Prescaler	= psc;                          /* 设置用来作为TIMx时钟频率除数的预分频值  10Khz的计数频率 */
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;                            /* 设置时钟分割:TDTS = Tck_tim */
	TIM_TimeBaseStructure.TIM_CounterMode	= TIM_CounterMode_Up;           /* TIM向上计数模式 */
	TIM_TimeBaseInit( TIM2, &TIM_TimeBaseStructure );                       /* 根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位 */

	TIM_ITConfig( TIM2, TIM_IT_Update, ENABLE );                            /* 使能指定的TIM3中断,允许更新中断 */

	NVIC_InitStructure.NVIC_IRQChannel			= TIM2_IRQn;    /* TIM3中断 */
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority	= 0;            /* 先占优先级0级 */
	NVIC_InitStructure.NVIC_IRQChannelSubPriority		= 3;            /* 从优先级3级 */
	NVIC_InitStructure.NVIC_IRQChannelCmd			= ENABLE;       /* IRQ通道被使能 */
	NVIC_Init( &NVIC_InitStructure );                                       /* 根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器 */

	TIM_Cmd( TIM2, ENABLE );                                                /* 使能TIMx外设 */
}


/* 定时器1中断服务程序 */
void TIM2_IRQHandler( void )                                                    /* TIM3中断 */
{
	int i;
	if ( TIM_GetITStatus( TIM2, TIM_IT_Update ) != RESET )                  /* 检查指定的TIM中断发生与否:TIM 中断源 */
	{
		for(i=0;i<8;i++)
		{ if(servo[i][TIME]>=20)
			{
				servo[i][SET_ANGLE]+=servo[i][MOVE_ANGLE];
				servo[i][TIME]-=20;
				servo_set_servo(i,servo[i][SET_ANGLE]);
			}
			
		}

		
		
		
		TIM_ClearITPendingBit( TIM2, TIM_IT_Update );                   /* 清除TIMx的中断待处理位:TIM 中断源 */
	
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
 * TIM3 PWM部分初始化
 * PWM输出初始化
 * arr：自动重装值
 * psc：时钟预分频数
 */

void TIM3_PWM_Init( u16 arr, u16 psc )
{
	
	GPIO_InitTypeDef	GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef	TIM_OCInitStructure;


	RCC_APB1PeriphClockCmd( RCC_APB1Periph_TIM3, ENABLE );                          /* 使能定时器3时钟 */
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB |RCC_APB2Periph_AFIO, ENABLE );   /* 使能GPIO外设和AFIO复用功能模块时钟 */


                      


	GPIO_InitStructure.GPIO_Speed	= GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode	= GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin	= GPIO_Pin_6 | GPIO_Pin_7 ;
	GPIO_Init( GPIOA, &GPIO_InitStructure );

GPIO_InitStructure.GPIO_Speed	= GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode	= GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin	= GPIO_Pin_0 | GPIO_Pin_1 ;
	GPIO_Init( GPIOB, &GPIO_InitStructure );

	/* 初始化TIM */
	TIM_TimeBaseStructure.TIM_Period	= arr;                          /* 设置在下一个更新事件装入活动的自动重装载寄存器周期的值 */
	TIM_TimeBaseStructure.TIM_Prescaler	= psc;                          /* 设置用来作为TIMx时钟频率除数的预分频值 */
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;                            /* 设置时钟分割:TDTS = Tck_tim */
	TIM_TimeBaseStructure.TIM_CounterMode	= TIM_CounterMode_Up;           /* TIM向上计数模式 */
	TIM_TimeBaseInit( TIM3, &TIM_TimeBaseStructure );                       /* 根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位 */


	/* 初始化TIM Channel  PWM模式 */
	TIM_OCInitStructure.TIM_OCMode		= TIM_OCMode_PWM1;              /*选择定时器模式:TIM脉冲宽度调制模式1  在小于时有效 */
	TIM_OCInitStructure.TIM_OutputState	= TIM_OutputState_Enable;       /* 比较输出使能 */
	TIM_OCInitStructure.TIM_OCPolarity	= TIM_OCPolarity_High;          /* 输出极性:TIM输出比较极性高 有效时为高 */

	TIM_OC1Init( TIM3, &TIM_OCInitStructure );                              /* 根据T指定的参数初始化外设TIM3 OC1 */
	TIM_OC1PreloadConfig( TIM3, TIM_OCPreload_Enable );                     /* 使能TIM3在CCR1上的预装载寄存器 */

	TIM_OC2Init( TIM3, &TIM_OCInitStructure );                              /* 根据T指定的参数初始化外设TIM3 OC1 */
	TIM_OC2PreloadConfig( TIM3, TIM_OCPreload_Enable );                     /* 使能TIM3在CCR1上的预装载寄存器 */

TIM_OC3Init( TIM3, &TIM_OCInitStructure );                              /* 根据T指定的参数初始化外设TIM3 OC1 */
	TIM_OC3PreloadConfig( TIM3, TIM_OCPreload_Enable );                     /* 使能TIM3在CCR1上的预装载寄存器 */

TIM_OC4Init( TIM3, &TIM_OCInitStructure );                              /* 根据T指定的参数初始化外设TIM3 OC1 */
	TIM_OC4PreloadConfig( TIM3, TIM_OCPreload_Enable );                     /* 使能TIM3在CCR1上的预装载寄存器 */

//	                    /* 使能TIM3在CCR1上的预装载寄存器 */


	TIM_Cmd( TIM3, ENABLE );                                                /* 使能TIM3 */
}

void TIM4_PWM_Init( u16 arr, u16 psc )
{
	
	GPIO_InitTypeDef	GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef	TIM_OCInitStructure;

	RCC_APB1PeriphClockCmd( RCC_APB1Periph_TIM4, ENABLE );                          /* 使能定时器3时钟 */
	RCC_APB2PeriphClockCmd(  RCC_APB2Periph_GPIOB |RCC_APB2Periph_AFIO, ENABLE );   /* 使能GPIO外设和AFIO复用功能模块时钟 */

  GPIO_InitStructure.GPIO_Speed	= GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode	= GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin	= GPIO_Pin_6 | GPIO_Pin_7|GPIO_Pin_8 | GPIO_Pin_9 ;
	GPIO_Init( GPIOB, &GPIO_InitStructure );

	/* 初始化TIM */
	TIM_TimeBaseStructure.TIM_Period	= arr;                          /* 设置在下一个更新事件装入活动的自动重装载寄存器周期的值 */
	TIM_TimeBaseStructure.TIM_Prescaler	= psc;                          /* 设置用来作为TIMx时钟频率除数的预分频值 */
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;                            /* 设置时钟分割:TDTS = Tck_tim */
	TIM_TimeBaseStructure.TIM_CounterMode	= TIM_CounterMode_Up;           /* TIM向上计数模式 */
	TIM_TimeBaseInit( TIM4, &TIM_TimeBaseStructure );                       /* 根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位 */


	/* 初始化TIM Channel  PWM模式 */
	TIM_OCInitStructure.TIM_OCMode		= TIM_OCMode_PWM1;              /*选择定时器模式:TIM脉冲宽度调制模式1  在小于时有效 */
	TIM_OCInitStructure.TIM_OutputState	= TIM_OutputState_Enable;       /* 比较输出使能 */
	TIM_OCInitStructure.TIM_OCPolarity	= TIM_OCPolarity_High;          /* 输出极性:TIM输出比较极性高 有效时为高 */

	TIM_OC1Init( TIM4, &TIM_OCInitStructure );                              /* 根据T指定的参数初始化外设TIM3 OC1 */
	TIM_OC1PreloadConfig( TIM4, TIM_OCPreload_Enable );                     /* 使能TIM3在CCR1上的预装载寄存器 */

	TIM_OC2Init( TIM4, &TIM_OCInitStructure );                              /* 根据T指定的参数初始化外设TIM3 OC1 */
	TIM_OC2PreloadConfig( TIM4, TIM_OCPreload_Enable );                     /* 使能TIM3在CCR1上的预装载寄存器 */

TIM_OC3Init( TIM4, &TIM_OCInitStructure );                              /* 根据T指定的参数初始化外设TIM3 OC1 */
	TIM_OC3PreloadConfig( TIM4, TIM_OCPreload_Enable );                     /* 使能TIM3在CCR1上的预装载寄存器 */

TIM_OC4Init( TIM4, &TIM_OCInitStructure );                              /* 根据T指定的参数初始化外设TIM3 OC1 */
	TIM_OC4PreloadConfig( TIM4, TIM_OCPreload_Enable );                     /* 使能TIM3在CCR1上的预装载寄存器 */

//	                    /* 使能TIM3在CCR1上的预装载寄存器 */


	TIM_Cmd( TIM4, ENABLE );                                                /* 使能TIM3 */
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
//转到绝对角度
void servo_control(u8 servo_id,float angle,float time)
{
	
	servo[servo_id][LAST_ANGLE]=servo[servo_id][NOW_ANGLE];
	servo[servo_id][SET_ANGLE]=servo[servo_id][LAST_ANGLE];
	servo[servo_id][TIME]=time;
  servo[servo_id][NOW_ANGLE]=angle;
  servo[servo_id][MOVE_ANGLE]=(servo[servo_id][NOW_ANGLE]-servo[servo_id][LAST_ANGLE])/(time/20.0);

}
//转向相对角度
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

