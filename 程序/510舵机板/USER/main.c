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
int main(void)
{
	u8 t;
	delay_init();
	NVIC_Configuration();
	servo_init(3);
	OLED_Init();
	OLED_ColorTurn(0);//0正常显示，1 反色显示
  OLED_DisplayTurn(0);//0正常显示 1 屏幕翻转显示
//	OLED_DrawPoint(0,0);
//	OLED_DrawLine(20,0,50,60);
//	OLED_DrawCircle(64,32,20);
	OLED_Refresh();
	t=' ';
	servo_control(0,45,1000);
	servo_control(1,0,1000);
	servo_control(2,0,1000);
	servo_control(3,0,1000);
	servo_control(4,0,1000);
	servo_control(5,0,1000);
	
//	delay_ms(1000);
//	servo_control(0,90,500);
//	servo_control(1,90,1500);
//	delay_ms(1000);
//	servo_control(0,-90,1000);
//	delay_ms(1000);
//	servo_control(0,-60,2000);
//	servo_control(1,-90,2000);
	while(1)
	{
    lcd_show();
	}
}

