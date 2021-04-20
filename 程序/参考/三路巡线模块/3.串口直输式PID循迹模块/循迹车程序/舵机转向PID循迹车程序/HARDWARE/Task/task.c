/**
  ******************************************************************************
  * @文件名 task.c
  * @文件说明：本文件为关于任务分配相关函数
  ******************************************************************************/
#include "task.h"
#include "led.h"
#include "key.h"
#include "encoder.h"
#include "control.h"
#include "servor.h"
#include "track.h"
#include "motor.h"
#include "common.h"
#include "usart.h"
#include "LQ12864.h"

u16 LedTaskCount=0;//定义Led闪烁任务计数变量
u16 KeyTaskCount=0;//定义按键扫描计数变量
u16 EncoderTaskCount=0;//定义编码器计数变量
u16 TrackTaskCount=0;//定义循迹任务计数变量
u16 TrackConfigTaskCount=0;//循迹传感器配置任务计数变量
u16 OledShowTaskCount=0;//OLED显示任务计数变量

//全局变量声明
u8 TrackFlag=0;//定义循迹标志位变量


/*@brief: LED闪烁任务,任务定时时间500ms
 * @param: None
 * @return: None
 */
void LedTwinkleTask(void)
{
	if(LedTaskCount>500)
	{
		LedTaskCount=0;
		if((SensorCalFlag==0)&&(TrackFlag==1))//在传感器没有配置的情况下LED灯不闪烁
		{
			LED=!LED;	
		}	
	}
}


/*@brief: 按键扫描任务函数，任务定时时间50ms
 * @param: None
 * @return: None
 */
void KeyTask(void)
{
	u8 key;
	if(KeyTaskCount>50)
	{
		KeyTaskCount=0;
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
	}
}

/*@brief: 循迹任务，任务定时时间5ms
 * @param: None
 * @return: None
 */
void TraceTask(void)
{
	int TraceDate=0;//储存循迹传感器输出变量
	if(TrackTaskCount>5)
	{
		TrackTaskCount=0;
		if(TrackFlag==1)//是否开启循迹功能
		{
			TraceDate=GetTraceDate();//读取PID红外循迹传感器读数
//			printf("TraceDate:%d\r\n",TraceDate);							
			if(TraceDate==30000)//传感器输出30000表示遇到黑线
			{
				TrackFlag=0;
				MotorStop();
			}
			else //传感器正常输出时根据数据循迹
			{
				TraceMove(TraceDate,0.3);//根据循迹传感器数据控制小车按照设定速度循迹
//				MoveDis(Encode_Left_ALL,Encode_Right_ALL,0.5,0.5);//根据循迹传感器数据控制小车按照设定距离循迹
			}
		}	
	}
}


/*@brief: 循迹传感器配置任务，任务定时时间50ms
 * @param: None
 * @return: None
 */
void TraceConfigTask(void)
{
	if(TrackConfigTaskCount>50)
	{
		TrackConfigTaskCount=0;
		if(SensorCalFlag==1||SensorCalFlag==2)//如果配置按键按下则进行循迹传感器配置
		{
			GetParament();
		}	
	}	
}	

/*@brief: OLED屏显示任务，任务定时时间200ms
 * @param: None
 * @return: None
 */	
void OledShowTask(void)
{
	char buff[50];
	int trackdate=0;
	if(OledShowTaskCount>200)
	{
		OledShowTaskCount=0;
		Show_Battary_Vol();//在显示屏上显示电池电压
		trackdate=GetTraceDate();//获取循迹传感器数据
		sprintf(buff,"trackdate:%d    ",trackdate);//编码器读数在定时器4中断中获取
		OLED_P6x8Str(1,4,(u8 *)buff);//显示循迹传感器读数
		printf("Encode_Left_ALL:%d\r\n",Encode_Left_ALL);
	}
	
}	

/*@brief: 定时器2中断更新函数，定时器2作为任务分配定时器，定时时间1ms
 * @param:None
 * @return: None
 */
void TIM2_IRQHandler(void)
{ 		    		  			    
	if(TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)  //检查TIM3更新中断发生与否
	{
		LedTaskCount++;
		KeyTaskCount++;
		EncoderTaskCount++;	
		TrackTaskCount++;
		TrackConfigTaskCount++;
		OledShowTaskCount++;
		/******需要及时处理的任务******/
		if(EncoderTaskCount>=5)//编码器读取任务，读取时间5ms
		{
			EncoderTaskCount=0;
			Encode_Left=-Read_Encoder(3);//读取左轮编码器数据
			Encode_Left_ALL+=Encode_Left;//左轮累计值	
			Encode_Speed=Encode_Left;//前进速度
		}	
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);  //清除TIMx更新中断标志
	}    
}



