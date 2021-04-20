#include "timer.h"
#include "led.h"
#include "usart.h"
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
void TIM6_Int_Init( u16 arr, u16 psc )
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef	NVIC_InitStructure;

	RCC_APB1PeriphClockCmd( RCC_APB1Periph_TIM6, ENABLE );                  /* 时钟使能 */

	TIM_TimeBaseStructure.TIM_Period	= arr;                          /* 设置在下一个更新事件装入活动的自动重装载寄存器周期的值	 计数到5000为500ms */
	TIM_TimeBaseStructure.TIM_Prescaler	= psc;                          /* 设置用来作为TIMx时钟频率除数的预分频值  10Khz的计数频率 */
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;                            /* 设置时钟分割:TDTS = Tck_tim */
	TIM_TimeBaseStructure.TIM_CounterMode	= TIM_CounterMode_Up;           /* TIM向上计数模式 */
	TIM_TimeBaseInit( TIM6, &TIM_TimeBaseStructure );                       /* 根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位 */

	TIM_ITConfig( TIM6, TIM_IT_Update, ENABLE );                            /* 使能指定的TIM3中断,允许更新中断 */

	NVIC_InitStructure.NVIC_IRQChannel			= TIM6_IRQn;    /* TIM3中断 */
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority	= 0;            /* 先占优先级0级 */
	NVIC_InitStructure.NVIC_IRQChannelSubPriority		= 2;            /* 从优先级2级 */
	NVIC_InitStructure.NVIC_IRQChannelCmd			= ENABLE;       /* IRQ通道被使能 */
	NVIC_Init( &NVIC_InitStructure );                                       /* 根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器 */

	TIM_Cmd( TIM6, ENABLE );                                                /* 使能TIMx外设 */
}

/*
 * 通用定时器6中断初始化
 * 这里时钟选择为APB1的2倍，而APB1为36M
 * arr：自动重装值。
 * psc：时钟预分频数
 * 这里使用的是定时器3!
 */
void TIM7_Int_Init( u16 arr, u16 psc )
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef	NVIC_InitStructure;

	RCC_APB1PeriphClockCmd( RCC_APB1Periph_TIM7, ENABLE );                  /* 时钟使能 */

	TIM_TimeBaseStructure.TIM_Period	= arr;                          /* 设置在下一个更新事件装入活动的自动重装载寄存器周期的值	 计数到5000为500ms */
	TIM_TimeBaseStructure.TIM_Prescaler	= psc;                          /* 设置用来作为TIMx时钟频率除数的预分频值  10Khz的计数频率 */
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;                            /* 设置时钟分割:TDTS = Tck_tim */
	TIM_TimeBaseStructure.TIM_CounterMode	= TIM_CounterMode_Up;           /* TIM向上计数模式 */
	TIM_TimeBaseInit( TIM7, &TIM_TimeBaseStructure );                       /* 根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位 */

	TIM_ITConfig( TIM7, TIM_IT_Update, ENABLE );                            /* 使能指定的TIM3中断,允许更新中断 */

	NVIC_InitStructure.NVIC_IRQChannel			= TIM7_IRQn;    /* TIM3中断 */
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority	= 0;            /* 先占优先级0级 */
	NVIC_InitStructure.NVIC_IRQChannelSubPriority		= 3;            /* 从优先级3级 */
	NVIC_InitStructure.NVIC_IRQChannelCmd			= ENABLE;       /* IRQ通道被使能 */
	NVIC_Init( &NVIC_InitStructure );                                       /* 根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器 */

	TIM_Cmd( TIM7, ENABLE );                                                /* 使能TIMx外设 */
}

//定时器1更新中断初始化
void TIM1_Int_Init( u16 arr, u16 psc )
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef	NVIC_InitStructure;

	RCC_APB2PeriphClockCmd( RCC_APB2Periph_TIM1, ENABLE );                  /* 时钟使能 */

	TIM_TimeBaseStructure.TIM_Period	= arr;                          /* 设置在下一个更新事件装入活动的自动重装载寄存器周期的值	 计数到5000为500ms */
	TIM_TimeBaseStructure.TIM_Prescaler	= psc;                          /* 设置用来作为TIMx时钟频率除数的预分频值  10Khz的计数频率 */
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;     /* 设置时钟分割:TDTS = Tck_tim */
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;     	
	TIM_TimeBaseStructure.TIM_CounterMode	= TIM_CounterMode_Up;           /* TIM向上计数模式 */
	TIM_TimeBaseInit( TIM1, &TIM_TimeBaseStructure );                       /* 根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位 */

	TIM_ITConfig( TIM8, TIM_IT_Update, ENABLE );                            /* 使能指定的TIM3中断,允许更新中断 */

	NVIC_InitStructure.NVIC_IRQChannel			= TIM1_UP_IRQn;    /* TIM3中断 */
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority	= 0;            /* 先占优先级0级 */
	NVIC_InitStructure.NVIC_IRQChannelSubPriority		= 3;            /* 从优先级3级 */
	NVIC_InitStructure.NVIC_IRQChannelCmd			= ENABLE;       /* IRQ通道被使能 */
	NVIC_Init( &NVIC_InitStructure );                                       /* 根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器 */

	TIM_Cmd( TIM1, ENABLE );                                                /* 使能TIMx外设 */
}


/* 定时器1中断服务程序 */
void TIM1_UP_IRQHandler( void )                                                    /* TIM3中断 */
{
	if ( TIM_GetITStatus( TIM1, TIM_IT_Update ) != RESET )                  /* 检查指定的TIM中断发生与否:TIM 中断源 */
	{
		
		TIM_ClearITPendingBit( TIM1, TIM_IT_Update );                   /* 清除TIMx的中断待处理位:TIM 中断源 */
		LED1 = !LED1;
	}
}

/*
 * TIM8 PWM部分初始化
 * PWM输出初始化
 * arr：自动重装值
 * psc：时钟预分频数
 */

void TIM8_PWM_Init(u16 arr,u16 psc)
{		 		
	 GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);// 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC| RCC_APB2Periph_AFIO, ENABLE);  //使能GPIO外设时钟使能
 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9; //TIM_CH1 //TIM_CH4
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	 
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值  不分频
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位

 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //选择定时器模式:TIM脉冲宽度调制模式1
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_Pulse = 0;                            //设置待装入捕获比较寄存器的脉冲值
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;     //输出极性:TIM输出比较极性高
	TIM_OC1Init(TIM8, &TIM_OCInitStructure);  //根据TIM_OCInitStruct中指定的参数初始化外设TIMx
	TIM_OC2Init(TIM8, &TIM_OCInitStructure);  //根据TIM_OCInitStruct中指定的参数初始化外设TIMx
	TIM_OC3Init(TIM8, &TIM_OCInitStructure);  //根据TIM_OCInitStruct中指定的参数初始化外设TIMx
	TIM_OC4Init(TIM8, &TIM_OCInitStructure);  //根据TIM_OCInitStruct中指定的参数初始化外设TIMx

  TIM_CtrlPWMOutputs(TIM8,ENABLE);	//MOE 主输出使能	

	TIM_OC1PreloadConfig(TIM8, TIM_OCPreload_Enable);  //CH1预装载使能	
	TIM_OC2PreloadConfig(TIM8, TIM_OCPreload_Enable);  //CH1预装载使能	
	TIM_OC3PreloadConfig(TIM8, TIM_OCPreload_Enable);  //CH1预装载使能		
	TIM_OC4PreloadConfig(TIM8, TIM_OCPreload_Enable);  //CH4预装载使能	 
	
	TIM_ARRPreloadConfig(TIM8, ENABLE); //使能TIMx在ARR上的预装载寄存器
	
	TIM_Cmd(TIM8, ENABLE);  //使能TIM
 
} 


/*
 * TIM3 PWM部分初始化
 * PWM输出初始化
 * arr：自动重装值
 * psc：时钟预分频数
 */

void TIM3_PWM_Init( u16 arr, u16 psc )
{
	/*
	 * 全部映射，将TIM3_CH2映射到PB5
	 * 根据STM32中文参考手册2010中第第119页可知：
	 * 当没有重映射时，TIM3的四个通道CH1，CH2，CH3，CH4分别对应PA6，PA7,PB0,PB1
	 * 当部分重映射时，TIM3的四个通道CH1，CH2，CH3，CH4分别对应PB4，PB5,PB0,PB1
	 * 当完全重映射时，TIM3的四个通道CH1，CH2，CH3，CH4分别对应PC6，PC7,PC8,PC9
	 * 也即是说，完全重映射之后，四个通道的PWM输出引脚分别为PC6，PC7,PC8,PC9，我们用到了通道1和通道2，
	 * 所以对应引脚为PC6，PC7,PC8,PC9，我们用到了通道1和通道2，所以对应引脚为
	 */

	GPIO_InitTypeDef	GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef	TIM_OCInitStructure;


	RCC_APB1PeriphClockCmd( RCC_APB1Periph_TIM3, ENABLE );                          /* 使能定时器3时钟 */
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB |RCC_APB2Periph_AFIO, ENABLE );   /* 使能GPIO外设和AFIO复用功能模块时钟 */


                            /* Timer3 完全重映射 */


	/* 设置PC6、PC7、PC8、PC9为复用输出，输出4路PWM */
	GPIO_InitStructure.GPIO_Speed	= GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode	= GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin	= GPIO_Pin_6 | GPIO_Pin_7 ;
	GPIO_Init( GPIOA, &GPIO_InitStructure );

GPIO_InitStructure.GPIO_Speed	= GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode	= GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin	= GPIO_Pin_0 | GPIO_Pin_1 ;
	GPIO_Init( GPIOB, &GPIO_InitStructure );

	/* 初始化TIM3 */
	TIM_TimeBaseStructure.TIM_Period	= arr;                          /* 设置在下一个更新事件装入活动的自动重装载寄存器周期的值 */
	TIM_TimeBaseStructure.TIM_Prescaler	= psc;                          /* 设置用来作为TIMx时钟频率除数的预分频值 */
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;                            /* 设置时钟分割:TDTS = Tck_tim */
	TIM_TimeBaseStructure.TIM_CounterMode	= TIM_CounterMode_Up;           /* TIM向上计数模式 */
	TIM_TimeBaseInit( TIM3, &TIM_TimeBaseStructure );                       /* 根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位 */


	/* 初始化TIM3 Channel 1 PWM模式 */
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


void TIM2_Int_Init( u16 arr, u16 psc )
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef	NVIC_InitStructure;

	RCC_APB1PeriphClockCmd( RCC_APB1Periph_TIM2, ENABLE );                  /* 时钟使能 */

	/* 定时器TIM2初始化 */
	TIM_TimeBaseStructure.TIM_Period	= arr;                          /* 设置在下一个更新事件装入活动的自动重装载寄存器周期的值 */
	TIM_TimeBaseStructure.TIM_Prescaler	= psc;                          /* 设置用来作为TIMx时钟频率除数的预分频值 */
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;                 /* 设置时钟分割:TDTS = Tck_tim */
	TIM_TimeBaseStructure.TIM_CounterMode	= TIM_CounterMode_Up;           /* TIM向上计数模式 */
	TIM_TimeBaseInit( TIM2, &TIM_TimeBaseStructure );                       /* 根据指定的参数初始化TIMx的时间基数单位 */

	TIM_ITConfig( TIM2, TIM_IT_Update, ENABLE );
	/* 使能指定的TIM2中断,允许更新中断 */

	/* 中断优先级NVIC设置 */
	NVIC_InitStructure.NVIC_IRQChannel			= TIM2_IRQn;    /* TIM2中断 */
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority	= 0;            /* 先占优先级0级 */
	NVIC_InitStructure.NVIC_IRQChannelSubPriority		= 3;            /* 从优先级3级 */
	NVIC_InitStructure.NVIC_IRQChannelCmd			= ENABLE;       /* IRQ通道被使能 */
	NVIC_Init( &NVIC_InitStructure );                                       /* 初始化NVIC寄存器 */


	 TIM_Cmd(TIM2, ENABLE);  //使能TIMx 
}




void TIM4_Int_Init( u16 arr, u16 psc )
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef	NVIC_InitStructure;

	RCC_APB1PeriphClockCmd( RCC_APB1Periph_TIM4, ENABLE );                  /* 时钟使能 */

	/* 定时器TIM4初始化 */
	TIM_TimeBaseStructure.TIM_Period	= arr;                          /* 设置在下一个更新事件装入活动的自动重装载寄存器周期的值 */
	TIM_TimeBaseStructure.TIM_Prescaler	= psc;                          /* 设置用来作为TIMx时钟频率除数的预分频值 */
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;                 /* 设置时钟分割:TDTS = Tck_tim */
	TIM_TimeBaseStructure.TIM_CounterMode	= TIM_CounterMode_Up;           /* TIM向上计数模式 */
	TIM_TimeBaseInit( TIM4, &TIM_TimeBaseStructure );                       /* 根据指定的参数初始化TIMx的时间基数单位 */

	TIM_ITConfig( TIM4, TIM_IT_Update, ENABLE );
	/* 使能指定的TIM4中断,允许更新中断 */

	/* 中断优先级NVIC设置 */
	NVIC_InitStructure.NVIC_IRQChannel			= TIM4_IRQn;    /* TIM4中断 */
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority	= 1;            /* 先占优先级0级 */
	NVIC_InitStructure.NVIC_IRQChannelSubPriority		= 2;            /* 从优先级3级 */
	NVIC_InitStructure.NVIC_IRQChannelCmd			= ENABLE;       /* IRQ通道被使能 */
	NVIC_Init( &NVIC_InitStructure );                                       /* 初始化NVIC寄存器 */


	 TIM_Cmd(TIM4, ENABLE);  //使能TIMx 
}


void TIM5_Int_Init( u16 arr, u16 psc )
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef	NVIC_InitStructure;

	RCC_APB1PeriphClockCmd( RCC_APB1Periph_TIM5, ENABLE );                  /* 时钟使能 */

	/* 定时器TIM5初始化 */
	TIM_TimeBaseStructure.TIM_Period	= arr;                          /* 设置在下一个更新事件装入活动的自动重装载寄存器周期的值 */
	TIM_TimeBaseStructure.TIM_Prescaler	= psc;                          /* 设置用来作为TIMx时钟频率除数的预分频值 */
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;                 /* 设置时钟分割:TDTS = Tck_tim */
	TIM_TimeBaseStructure.TIM_CounterMode	= TIM_CounterMode_Up;           /* TIM向上计数模式 */
	TIM_TimeBaseInit( TIM5, &TIM_TimeBaseStructure );                       /* 根据指定的参数初始化TIMx的时间基数单位 */

	TIM_ITConfig( TIM5, TIM_IT_Update, ENABLE );
	/* 使能指定的TIM5中断,允许更新中断 */

	/* 中断优先级NVIC设置 */
	NVIC_InitStructure.NVIC_IRQChannel			= TIM5_IRQn;    /* TIM5中断 */
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority	= 0;            /* 先占优先级0级 */
	NVIC_InitStructure.NVIC_IRQChannelSubPriority		= 3;            /* 从优先级3级 */
	NVIC_InitStructure.NVIC_IRQChannelCmd			= ENABLE;       /* IRQ通道被使能 */
	NVIC_Init( &NVIC_InitStructure );                                       /* 初始化NVIC寄存器 */


	 TIM_Cmd(TIM5, ENABLE);  //使能TIMx 
}

