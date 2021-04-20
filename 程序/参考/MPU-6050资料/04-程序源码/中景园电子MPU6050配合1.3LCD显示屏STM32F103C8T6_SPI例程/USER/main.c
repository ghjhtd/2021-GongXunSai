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
//              BLK  PA4
//***************MPU6050�ӿ�**********************
//              GND  ��Դ��
//              VCC  3.3v��Դ
//              SCL  PB10
//              SDA  PB11
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
#include "lcd.h"
#include "usart.h"
#include "mpuiic.h"
#include "MPU6050.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"
#include "parameter.h"
#include "bmp.h"

extern float pitch,roll,yaw; 		//ŷ����
extern short gyrox,gyroy,gyroz;	//������ԭʼ����
extern short aacx,aacy,aacz;		//���ٶȴ�����ԭʼ����


//�ϵ����Ҫˮƽ����2-3S������У׼
int main(void)
{
	delay_init();//��ʱ������ʼ��
	Lcd_Init();//��ʾ����ʼ��
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(9600);//��ʼ������
//	MPU_Init();    //MPU6050��ʼ��
	BACK_COLOR=WHITE;
//	LCD_Fill(0,0,240,32,BLUE);
	LCD_ShowPicture(0,0,59,59,gImage_1);
	LCD_ShowChinese(60,0,0,32,RED);//��
	LCD_ShowChinese(92,0,1,32,BROWN);//��
	LCD_ShowChinese(124,0,2,32,GREEN);//Բ
	LCD_ShowChinese(156,0,3,32,BLUE);//��
	LCD_ShowChinese(188,0,4,32,BLACK);//��
  Connect_Check();//MPU6050��ʼ�������MPU6050�Ƿ����ӳɹ�
	Acceleration_Adjust();//���ٶ�У׼
	Gyroscope_Adjust();//���ٶ�У׼
	LCD_Fill(0,220,239,239,BLUE);
	while(1)
	{
		LCD_ShowPicture(0,0,59,59,gImage_2);
		Show_Temperture(60,90,16,BLACK);//��ʾ�¶�
		Show_EulerAngle(60,106,16,BLACK);//��ʾŷ����
//		Show_Gyroscope(60,106,16,BLACK);//��ʾx,y,z��Ľ��ٶ�
		Show_Acceleration(60,170,16,BLACK);//��ʾx,y,z��ļ��ٶ�
		printf("Pitch=%f Roll=%f Yaw=%f \n",pitch,roll,yaw);//�ڴ���1��ʾŷ����
		LCD_ShowPicture(0,0,59,59,gImage_1);
	}
}

