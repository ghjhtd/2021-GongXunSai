#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"	 


//#define KEY0 PEin(4)   	//PE4
//#define KEY1 PEin(3)	//PE3 
//#define KEY2 PEin(2)	//PE2
//#define WK_UP PAin(0)	//PA0  WK_UP

#define KEY0  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_12)//读取按键0


#define KEY0_PRES 	1		//KEY0按下
#define KEY0_LONG_PRES 	2	//KEY0长按，长按时间大于1s

/****************************外部函数声明********************************/
extern void KEY_Init(void);//IO初始化
extern u8 KEY_Scan(void);				    
#endif
