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
//              CS   PA4
//***************MPU6050接口**********************
//              GND  电源地
//              VCC  3.3v电源
//              SCL  PB10
//              SDA  PB11
//              其余不接
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
#include "usart.h"
#include "mpuiic.h"
#include "MPU6050.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"
#include "parameter.h"

//上电后需要水平放置2-3S来进行校准
int main(void)
{
	delay_init();//延时函数初始化
	OLED_Init();//显示屏初始化
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(9600);//初始化串口
//	MPU_Init();    //MPU6050初始化
  Connect_Check();//MPU6050初始化并检查MPU6050是否连接成功
	Gyroscope_Adjust();   //角速度校准
	Acceleration_Adjust();//加速度校准
	while(1)
	{
		Show_EulerAngle();//显示温度和欧拉角
//		Show_Gyroscope();//显示x,y,z轴的角速度
//		Show_Acceleration();//显示x,y,z轴的加速度
//		printf("Pitch=%f Roll=%f Yaw=%f \n",pitch,roll,yaw);//在串口1显示欧拉角
//		if(MPU_Get_Gyroscope(&gyrox,&gyroy,&gyroz)==0)
//	{ 
//		OLED_ShowNum(64,0,gyrox,5,16);
//		OLED_ShowNum(64,16,gyroy,5,16);
//		OLED_ShowNum(64,32,gyroz,5,16);
//	}
//	OLED_ShowNum(0,0,gyrox_offset,5,16);
//	OLED_ShowNum(0,16,gyroy_offset,5,16);
//	OLED_ShowNum(0,32,gyroz_offset,5,16);
//	OLED_Refresh();
	}
}

