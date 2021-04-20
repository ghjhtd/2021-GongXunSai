#ifndef __PARAMETER_H
#define __PARAMETER_H

#include "spi.h"
#include "mpuiic.h"
#include "mpu6050.h"


#define Accel_G          9.8  //�����������ٶ�

#define Accel_Fsr        2    //���ٶȼ�����

#define Gyro_Fsr         2000 //���ٶ�����




void Show_EulerAngle(void);//��ʾ���ٶȺ��¶�
void Show_Acceleration(void);//��ʾ���ٶ�
void Show_Temperture(u8 x,u8 y,u8 size1);//��ȡ�¶�
u8 Gyroscope_Adjust1(void);//���ٶ�У׼
u8 Acceleration_Adjust1(void);//���ٶ�У׼
void Connect_Check(void);//��ʼ��MPU6050�Լ����MPU6050�Ƿ����ӳɹ�

#endif




