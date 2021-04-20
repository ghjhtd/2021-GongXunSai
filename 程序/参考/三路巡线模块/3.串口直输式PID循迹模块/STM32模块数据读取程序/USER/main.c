/**
  ******************************************************************************
  * @文件名 main.c
  * @文件说明：本程序为魔石串口直输式循迹模块数据读取程序，通过串口3读取寻迹模块数据，
	通过串口1将读取的寻迹模块数据发送到电脑上，通过PC13 LED指示灯闪烁指示是否收到数据
  * @编写人：Dinvent
  * @魔石科技
  * @淘宝店铺链接：
  ******************************************************************************/
#include "sys.h"
#include "delay.h"
#include "usart3.h"
#include "led.h"
#include "usart.h"	  
#include "mstrack.h"


 int main(void)
 {
	int TrackDate;
	delay_init();//延时函数初始化
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	uart_init(115200);	//串口初始化 波特率115200
	MsTrack_Init();
	LED_Init();	 		//初始化与LED连接的硬件接口
	while(1)
	{		
		if(USART3_RX_STA&0x8000)//可以放在定时器中断里执行
		{
			LED=!LED;//接收到一帧数据后LED状态变化一次
			USART3_RX_STA=0;
			
			TrackDate=GetTrackString2IntData(USART3_RX_BUF);//将获取到的字符串数据转化为整形数据
			printf("TrackDate:%d\r\n",TrackDate);
			memset(USART3_RX_BUF, 0, sizeof(USART3_RX_BUF));//将获取到数组数据清零
		}
	}
 }

 
	
 
 
 

