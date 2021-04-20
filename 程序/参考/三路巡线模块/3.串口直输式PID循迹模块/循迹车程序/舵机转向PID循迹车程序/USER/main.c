/**
  ******************************************************************************
  * @文件名 main.c
  * @文件说明：本文件为PID舵机转向循迹车主程序函数文件
  * @编写人：Dinvent
  * @版本：V1.1.0
  * @日期：2020-12-12 
  * @魔石科技
  * @淘宝店铺链接：https://shop418595371.taobao.com
  *  或者直接淘宝搜索店铺魔石电子科技工作室
  ******************************************************************************/
#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "beep.h" 
#include "led.h"
#include "motor.h"
#include "servor.h"
#include "LQ12864.h"
#include "encoder.h"   
#include "timer.h"
#include "common.h"
#include "control.h"
#include "adc.h"
#include "track.h"
#include "24l01.h"
#include "key.h"
#include "stmflash.h"
#include "datastore.h"
#include "task.h"


int main(void)
{
	delay_init();//延时函数初始化
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	uart_init(115200);	//串口初始化 波特率115200
	Track_Init();		//循迹传感器参数函数
	OLED_Init();		//OLED初始化函数
	KEY_Init();			//按键初始化函数
	LED_Init();	 		//初始化与LED连接的硬件接口
	Beep_Init(); 		//蜂鸣器初始化函数		 
	Motor_Init();		//电机初始化函数
	NRF24L01_Init();	//NRF24L01初始化
	NRF24L01_TX_Mode();	//配置NRF24L01成发送模式
	Encoder_Init();		//编码器初始化	
	Servor_Init();		//舵机初始化函数
	Show_CH(20,0);		//在OLED上显示中文标题	
	TIM2_Int_Init(7200-1,10-1);//定时时间1ms
	while(1)
	{		
		TraceTask();//循迹任务
		TraceConfigTask();//循迹传感器配置任务
		LedTwinkleTask();//LED闪烁任务
		KeyTask();//按键扫描任务
		OledShowTask();//OLED显示任务
	}
}


	

