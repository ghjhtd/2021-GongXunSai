#ifndef __PARAMETER_H
#define __PARAMETER_H

#include "delay.h"
#include "sys.h"
#include "lcd.h"
#include "mpuiic.h"
#include "MPU6050.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"


#define Accel_G          9.8  //当地重力加速度

#define Accel_Fsr        2    //加速度计量程

#define Gyro_Fsr         2000 //角速度量程




void Show_EulerAngle(u8 x,u8 y,u8 size,u16 color);//显示角速度和温度
void Show_Gyroscope(u8 x,u8 y,u8 size,u16 color);//显示角速度
void Show_Acceleration(u8 x,u8 y,u8 size,u16 color);//显示加速度
void Show_Temperture(u8 x,u8 y,u8 size,u16 color);//读取温度
u8 Gyroscope_Adjust1(void);//角速度校准
u8 Acceleration_Adjust1(void);//加速度校准
void Connect_Check(void);//初始化MPU6050以及检测MPU6050是否连接成功
void Acceleration_Adjust(void);//加速度校准界面
void Gyroscope_Adjust(void);//角速度校准界面
#endif




