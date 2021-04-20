/**
  ******************************************************************************
  * @文件名 adc.c
  * @文件说明：本文件包含小车参数配置以及公用函数文件
  ******************************************************************************/
#include "common.h" 
#include "led.h"
#include "delay.h"
#include "LQ12864.h"
#include "adc.h"
#include "stdio.h"



/*@brief: 显示电池电压函数
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






