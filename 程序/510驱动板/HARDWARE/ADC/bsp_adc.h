#ifndef __BSP_ADC_H
#define __BSP_ADC_H
#include "delay.h"
#include "sys.h"


 /**************************************************************************
针对510驱动板写的adc驱动函数，可实现ADC按键和pid循迹模块检测
**************************************************************************/

void DMA_ADC_Init(void);  //DMA初始化，将ADC连续转换后的值直接保存在变量里
void Adc_Init(void);      //ADC初始化，通过软件触发
u8 ADC_Key(u16 adc,u8 mode);      //adc矩阵键盘检测，mode=0不支持连按
#endif


