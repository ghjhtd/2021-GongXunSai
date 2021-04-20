#ifndef __PARAMETER_H
#define __PARAMETER_H

#include "delay.h"
#include "sys.h"
#include "lcd.h"
#include "mpuiic.h"
#include "MPU6050.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"


#define Accel_G          9.8  //�����������ٶ�

#define Accel_Fsr        2    //���ٶȼ�����

#define Gyro_Fsr         2000 //���ٶ�����




void Show_EulerAngle(u8 x,u8 y,u8 size,u16 color);//��ʾ���ٶȺ��¶�
void Show_Gyroscope(u8 x,u8 y,u8 size,u16 color);//��ʾ���ٶ�
void Show_Acceleration(u8 x,u8 y,u8 size,u16 color);//��ʾ���ٶ�
void Show_Temperture(u8 x,u8 y,u8 size,u16 color);//��ȡ�¶�
u8 Gyroscope_Adjust1(void);//���ٶ�У׼
u8 Acceleration_Adjust1(void);//���ٶ�У׼
void Connect_Check(void);//��ʼ��MPU6050�Լ����MPU6050�Ƿ����ӳɹ�
void Acceleration_Adjust(void);//���ٶ�У׼����
void Gyroscope_Adjust(void);//���ٶ�У׼����
#endif




