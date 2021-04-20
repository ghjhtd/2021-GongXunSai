/**
  ******************************************************************************
  * @�ļ��� adc.c
  * @�ļ�˵�������ļ�����С�����������Լ����ú����ļ�
  ******************************************************************************/
#include "common.h" 
#include "led.h"
#include "delay.h"
#include "LQ12864.h"
#include "adc.h"
#include "stdio.h"


u8 TrackFlag=0;//����ѭ����־λ��Ϊ0ֹͣѭ����Ϊ1��ʼѭ��


/*@brief: ��ʾ��ص�ѹ����
 * @param: None
 * @return: None
 */
void Show_Battary_Vol(void)
{
	float vol=0;
	char buff[20];
	vol = (Get_Adc(8)/4096.0)*11*3.3;
	sprintf(buff,"Bat Vol:%.1f",vol);
	OLED_P6x8Str(0,6,(u8 *)buff);
}






