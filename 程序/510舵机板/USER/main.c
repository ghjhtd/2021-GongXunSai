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
//  ��������   : OLED I2C�ӿ���ʾ����(STM32F103ϵ��)
//              ˵��: 
//              ----------------------------------------------------------------
//              GND  ��Դ��
//              VCC  3.3v��Դ
//              D0   PA5��SCL��
//              D1   PA7��SDA��              
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
float servo[8][5]={0};
int main(void)
{
	u8 t;
	delay_init();
	NVIC_Configuration();
	servo_init(3);
	OLED_Init();
	OLED_ColorTurn(0);//0������ʾ��1 ��ɫ��ʾ
  OLED_DisplayTurn(0);//0������ʾ 1 ��Ļ��ת��ʾ
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

