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
//  功能描述   : OLED 4线SPI接口演示例程(STM32F103系列)
//              说明: 
//              ----------------------------------------------------------------
//***************OLED显示屏接口*******************
//              GND  电源地
//              VCC  3.3v电源
//              D0   PA0（SCL）
//              D1   PA1（SDA）
//              RES  PA2
//              DC   PA3
//              BLK  PA4
//***************MPU6050接口**********************
//              GND  电源地
//              VCC  3.3v电源
//              SCL  PB10
//              SDA  PB11
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
#include "lcd.h"
#include "usart.h"
#include "mpuiic.h"
#include "MPU6050.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"
#include "parameter.h"
#include "bmp.h"

extern float pitch,roll,yaw; 		//欧拉角
extern short gyrox,gyroy,gyroz;	//陀螺仪原始数据
extern short aacx,aacy,aacz;		//加速度传感器原始数据


//上电后需要水平放置2-3S来进行校准
int main(void)
{
	delay_init();//延时函数初始化
	Lcd_Init();//显示屏初始化
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(9600);//初始化串口
//	MPU_Init();    //MPU6050初始化
	BACK_COLOR=WHITE;
//	LCD_Fill(0,0,240,32,BLUE);
	LCD_ShowPicture(0,0,59,59,gImage_1);
	LCD_ShowChinese(60,0,0,32,RED);//中
	LCD_ShowChinese(92,0,1,32,BROWN);//景
	LCD_ShowChinese(124,0,2,32,GREEN);//圆
	LCD_ShowChinese(156,0,3,32,BLUE);//电
	LCD_ShowChinese(188,0,4,32,BLACK);//子
  Connect_Check();//MPU6050初始化并检查MPU6050是否连接成功
	Acceleration_Adjust();//加速度校准
	Gyroscope_Adjust();//角速度校准
	LCD_Fill(0,220,239,239,BLUE);
	while(1)
	{
		LCD_ShowPicture(0,0,59,59,gImage_2);
		Show_Temperture(60,90,16,BLACK);//显示温度
		Show_EulerAngle(60,106,16,BLACK);//显示欧拉角
//		Show_Gyroscope(60,106,16,BLACK);//显示x,y,z轴的角速度
		Show_Acceleration(60,170,16,BLACK);//显示x,y,z轴的加速度
		printf("Pitch=%f Roll=%f Yaw=%f \n",pitch,roll,yaw);//在串口1显示欧拉角
		LCD_ShowPicture(0,0,59,59,gImage_1);
	}
}

