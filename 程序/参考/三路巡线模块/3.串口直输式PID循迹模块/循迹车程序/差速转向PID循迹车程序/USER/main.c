/**
  ******************************************************************************
  * @文件名 main.c
  * @文件说明：本文件为PID循迹车主程序函数文件
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





int main(void)
{
//	char buff[100];
	int TraceDate=0;//储存循迹传感器输出变量
	u8 key=0;//定义按键变量，获取按下的按键值
	delay_init();//延时函数初始化
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	uart_init(115200);	//串口初始化 波特率115200
	Track_Init();		//循迹传感器参数函数
	OLED_Init();		//OLED初始化函数
	KEY_Init();			//按键初始化函数
	LED_Init();	 		//初始化与LED连接的硬件接口
	Beep_Init(); 		//蜂鸣器初始化函数		 
	Motor_Init();		//电机初始化函数
	NRF24L01_Init();	//24L01初始化
	NRF24L01_TX_Mode();	//配置成发送模式
	Encoder_Init();		//编码器初始化	
	Show_CH(20,0);		//显示中文标题	
	Set_Motor_PWM(0);	//设置电机转速为最大	
	while(1)
	{		
		key=KEY_Scan();//获取按下的按键值
		if(key==KEY0_PRES)
		{
			if(SensorCalFlag==0)
			{
				if(TrackFlag==0)	TrackFlag=1;
				else if(TrackFlag==1)	TrackFlag=0;			
			}
			else if(SensorCalFlag==1) //在配置模式中长按代表配置完成并退出配置模式
			{
				SensorCalFlag=2;
			}
		}		
		else if(key==KEY0_LONG_PRES)//如果长按
		{
			if(SensorCalFlag==0)	
			{
				SensorCalFlag=1;
				LED=0;//LED常亮代表进入配置模式	
			}
		}

		if(SensorCalFlag==1||SensorCalFlag==2)//如果配置按键按下则进行循迹传感器配置
		{
			GetParament();
			delay_ms(50);
		}
		if(SensorCalFlag==0)//判断是否循迹传感器处于配置模式
		{
			if(TrackFlag==1)//是否开启循迹功能
			{
				TraceDate=GetTraceDate();//读取PID红外循迹传感器读数
//				printf("TraceDate:%d\r\n",TraceDate);				
				if(TraceDate==30000)//传感器输出30000表示遇到黑线
				{
					TrackFlag=0;
					MotorStop();
				}
				else //传感器正常输出时根据数据循迹
				{
					TraceMove(TraceDate,0.1);//根据循迹传感器数据控制小车按照设定速度循迹
//					MoveDis(Encode_Left_ALL,Encode_Right_ALL,0.5,0.5);//根据循迹传感器数据控制小车按照设定距离循迹
				}	
				delay_ms(5);//PID控制时间延时									   
			}	
		}
		Show_Battary_Vol();//在显示屏上显示电池电压
	}
}

 
 
 
	

