//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//�о�԰����
//���̵�ַ��http://shop73023976.taobao.com
//
//  �� �� ��   : main.c
//  �� �� ��   : v2.0
//  ��    ��   : HuangKai
//  ��������   : 2018-10-31
//  ����޸�   : 
//  ��������   : OLED 4��SPI�ӿ���ʾ����(STM32F103ϵ��)
//              ˵��: 
//              ----------------------------------------------------------------
//***************OLED��ʾ���ӿ�*******************
//              GND  ��Դ��
//              VCC  3.3v��Դ
//              D0   PA0��SCL��
//              D1   PA1��SDA��
//              RES  PA2
//              DC   PA3
//              CS   PA4
//***************MPU6050�ӿ�**********************
//              GND  ��Դ��
//              VCC  3.3v��Դ
//              SCL  PB10
//              SDA  PB11
//              ���಻��
//              ----------------------------------------------------------------
// �޸���ʷ   :
// ��    ��   : 
// ��    ��   : HuangKai
// �޸�����   : �����ļ�
//��Ȩ���У�����ؾ���
//Copyright(C) �о�԰����2018-10-31
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

//�ϵ����Ҫˮƽ����2-3S������У׼
int main(void)
{
	delay_init();//��ʱ������ʼ��
	OLED_Init();//��ʾ����ʼ��
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(9600);//��ʼ������
//	MPU_Init();    //MPU6050��ʼ��
  Connect_Check();//MPU6050��ʼ�������MPU6050�Ƿ����ӳɹ�
	Gyroscope_Adjust();   //���ٶ�У׼
	Acceleration_Adjust();//���ٶ�У׼
	while(1)
	{
		Show_EulerAngle();//��ʾ�¶Ⱥ�ŷ����
//		Show_Gyroscope();//��ʾx,y,z��Ľ��ٶ�
//		Show_Acceleration();//��ʾx,y,z��ļ��ٶ�
//		printf("Pitch=%f Roll=%f Yaw=%f \n",pitch,roll,yaw);//�ڴ���1��ʾŷ����
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

