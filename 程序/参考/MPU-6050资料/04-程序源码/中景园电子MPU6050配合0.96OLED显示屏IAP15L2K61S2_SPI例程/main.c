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
//  功能描述   : OLED 4接口演示例程(51系列)
//              说明: 
//-----------------OLED接口--------------------------------------
//              GND    电源地
//              VCC  3.3v电源
//              D0   P1^0（SCL）
//              D1   P1^1（SDA）
//              RES  P1^2
//              DC   P1^3
//              CS   P1^4 
//----------------MPU6050接口------------------------------------
//              GND  电源地
//              VCC  3.3v
//              DC   P0^1
//              CS   P0^2 
//---------------------------------------------------------------
// 修改历史   :
// 日    期   : 
// 作    者   : HuangKai
// 修改内容   : 创建文件
//版权所有，盗版必究。
//Copyright(C) 中景园电子2018-10-31
//All rights reserved
//******************************************************************************/
#include "REG51.h"
#include "led.h"
#include "spi.h"
#include "parameter.h"
#include "MPU6050.h"
#include "mpuiic.h"


int main(void)
{
	OLED_Init();
//	MPU_Init();
  Connect_Check();//初始化MPU6050，并检查MPU6050是否连接成功
	Gyroscope_Adjust();   //角速度校准 
	Acceleration_Adjust();//加速度校准
	OLED_Clear();
	while(1)
	{
		Show_Temperture(0,0,16);
		Show_Acceleration();//显示x,y,z轴加速度
//		Show_Gyroscope();//显示x,y,z轴角速度

	}
}








