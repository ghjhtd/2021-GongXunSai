//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//中景园电子
//店铺地址：http://shop73023976.taobao.com
//
//  文 件 名   : main.c
//  版 本 号   : v2.0
//  作    者   : HuangKai
//  生成日期   : 2018-10-31
//  最近修改   : 
//  功能描述   : OLED I2C接口演示例程(STM32F103系列)
//              说明: 
//              ----------------------------------------------------------------
//              GND  电源地
//              VCC  3.3v电源
//              D0   PA5（SCL）
//              D1   PA7（SDA）              
//              ----------------------------------------------------------------
// 修改历史   :
// 日    期   : 
// 作    者   : HuangKai
// 修改内容   : 创建文件
//版权所有，盗版必究。
//Copyright(C) 中景园电子2018-10-31
//All rights reserved
//******************************************************************************/
#include "delay.h"
#include "sys.h"
#include "oled.h"
#include "bmp.h"
float servo[8][5]={0};

int len,t;
int num[8],num_cnt,cishu_flag;
char COMMAND[20],OPENMV[20];
void Send_data(USART_TypeDef * USARTx,u8 *s);
int send_flag=0,color,color_num=3,COLOR[3];
int test=0,test_usart=0,witch;
int main(void)
{
	u8 t;
	delay_init();
	NVIC_Configuration();
	servo_init(3);
	uart1_init(115200);  //板间通讯
	uart3_init(115200);		//openmv
	
	OLED_Init();
	OLED_ColorTurn(0);//0正常显示，1 反色显示
  OLED_DisplayTurn(0);//0正常显示 1 屏幕翻转显示
//	OLED_DrawPoint(0,0);
//	OLED_DrawLine(20,0,50,60);
//	OLED_DrawCircle(64,32,20);
	OLED_Refresh();
	t=' ';
	servo_control(0,0,1000);
	servo_control(1,80,1000);
	servo_control(2,-10,1000);
	servo_control(3,-30,1000);
	servo_control(4,0,1000);
	servo_control(5,0,1000);
//	delay_ms(1000);
//	servo_move(0,10,1000); //正为向左转
//	servo_move(1,10,1000); //正为向上转
//	servo_move(2,0,1000); //正为向上
//	servo_move(3,20,1000); //正为向下转
//	servo_move(4,20,1000); //正为向下转
//	servo_move(5,20,1000); //正为向里夹
//	servo_control(0,90,500);
//	servo_control(1,90,1500);
//	delay_ms(1000);
//	servo_control(0,-90,1000);
//	delay_ms(1000);
//	servo_control(0,-60,2000);
//	servo_control(1,-90,2000);

	while(1)
	{
		if(USART1_RX_STA&0x8000)//可以放在定时器中断里执行
		{
			len=(USART1_RX_STA&0x3fff);//得到此次接收到的数据长度
		
			for(t=0;t<len;t++)
			{
				 COMMAND[t]=USART1_RX_BUF[t];				
			}
			COMMAND[t]='\0';
			USART1_RX_STA=0;
			if(COMMAND[0]=='S')
			{
				servo_control(COMMAND[1]-'0',atoi(&COMMAND[2]),100);
			}
		  if(COMMAND[0]=='M')
			{
				servo_move(COMMAND[1]-'0',atoi(&COMMAND[2]),100);
			}
			if(COMMAND[0]=='V')  //向openmv发送数据
			{
				USART_SendData(USART3,COMMAND[1]);
			}
			if(COMMAND[0]=='D')  //让舵机做相应的动作
			{
				witch = COMMAND[1]-'0';
				switch(witch){
					case 0:   //原料区上层
						servo_control(0,0,100);
						delay_ms(600);
						servo_control(1,35,100);
						delay_ms(600);
						servo_control(2,-12,100);
						delay_ms(600);
						servo_control(3,25,100);
						delay_ms(600);
						servo_control(4,35,100);
						delay_ms(600);
						break;
					case 1: //原料区下层
						servo_control(0,0,100);
						delay_ms(600);
						servo_control(1,-25,100);
						delay_ms(600);
						servo_control(2,13,100);
						delay_ms(600);
						servo_control(3,55,100);
						delay_ms(600);
						servo_control(4,0,100);
						delay_ms(600);
						break;
					case 2:  //粗加工 绿
						servo_control(0,-30,100);
						delay_ms(600);
						servo_control(1,-40,100);
						delay_ms(600);
						servo_control(2,28,100);
						delay_ms(600);
						servo_control(3,50,100);
						delay_ms(600);
						servo_control(4,0,100);
						delay_ms(600);
						break;
					case 3: //粗加工 蓝
						servo_control(0,35,100);
						delay_ms(600);
						servo_control(1,-40,100);
						delay_ms(600);
						servo_control(2,28,100);
						delay_ms(600);
						servo_control(3,50,100);
						delay_ms(600);
						servo_control(4,0,100);
						delay_ms(600);
						break;
					case 4: //粗加工 红
						servo_control(0,5,100);
						delay_ms(600);
						servo_control(1,-40,100);
						delay_ms(600);
						servo_control(2,23,100);
						delay_ms(600);
						servo_control(3,60,100);
						delay_ms(600);
						servo_control(4,35,100);
						delay_ms(600);
						break;
					case 5: //精加工 蓝
						servo_control(0,-25,100);
						delay_ms(600);
						servo_control(1,-20,100);
						delay_ms(600);
						servo_control(2,13,100);
						delay_ms(600);
						servo_control(3,45,100);
						delay_ms(600);
						servo_control(4,35,100);
						delay_ms(600);
						break;
					case 6: //精加工 绿
						servo_control(0,35,100);
						delay_ms(600);
						servo_control(1,-20,100);
						delay_ms(600);
						servo_control(2,13,100);
						delay_ms(600);
						servo_control(3,40,100);
						delay_ms(600);
						servo_control(4,0,100);
						delay_ms(600);
						break;
					case 7: //精加工 红
						servo_control(0,0,100);
						delay_ms(600);
						servo_control(1,-25,100);
						delay_ms(600);
						servo_control(2,23,100);
						delay_ms(600);
						servo_control(3,40,100);
						delay_ms(600);
						servo_control(4,0,100);
						delay_ms(600);
						break;
					case 8: //默认位置
						servo_control(0,0,100);
						delay_ms(600);
						servo_control(1,80,100);
						delay_ms(600);
						servo_control(2,8,100);
						delay_ms(600);
						servo_control(3,-30,100);
						delay_ms(600);
						servo_control(4,0,100);
						delay_ms(600);
						break;
				}
			}
		}	
    lcd_show();
		//openmv();
		//Send_data(USART3,"q");
		//USART_SendData(USART1,test);
//		test++;
//		if(test>200) test =0;
		delay_ms(100);
	}
}


void Send_data(USART_TypeDef * USARTx,u8 *s)
{
 while(*s!='\0')
 { 
  while(USART_GetFlagStatus(USARTx,USART_FLAG_TC )==RESET); 
  USART_SendData(USARTx,*s);
  s++;
 }
}
