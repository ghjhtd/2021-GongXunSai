/**
  ******************************************************************************
  * @文件名 servor.c
  * @文件说明：本文件为关于编码器控制相关函数文件
  ******************************************************************************/
#include "encoder.h"
#include "led.h"
#include "timer.h"

extern int Encoder_A_EXTI;


int Encode_Left=0;			//定义左轮编码器读取值变量，更改会导致错误
int Encode_Right=0;			//定义右轮编码器读取值变量，更改会导致错误
int Encode_Left_ALL=0;		//定义左轮编码器累加值
int Encode_Right_ALL=0;		//定义右轮编码器累加值
int	Encode_Speed=0;			//定义通过编码器获取的小车前进速度,大于0前进速度，小于0后退速度
int	Encode_Spin_Speed=0;	//通过编码器获取的小车旋转速度，大于右转速度，小于0左转速度


/*@brief: 编码器初始化函数
 * @param: None
 * @return: None
 */
void Encoder_Init(void)
{
	Encoder_Init_TIM2();//左电机初始化函数
	Encoder_Init_TIM3();//右电机初始化函数
	TIM1_Int_Init(5000-1,72-1);//初始化定时1，定时时间5ms，在其中读取编码器数据
}



/* @brief: 单位时间读取编码器计数
 * @param: 
 *			[in] TIMX 读取编码器计数值定位器编号，范围2-4
 * @return: 读取的编码器计数值，与定时器读取时间有关
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



