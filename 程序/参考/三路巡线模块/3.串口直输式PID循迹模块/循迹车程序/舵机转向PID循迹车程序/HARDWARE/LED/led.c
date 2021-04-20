/**
  ******************************************************************************
  * @文件名 led.c
  * @文件说明：本文件为关于LED灯相关函数文件
  ******************************************************************************/
#include "led.h"
#include "delay.h"	   
	    
/*@brief: LED初始化函数
 * @param: None
 * @return: None
 */
void LED_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);//使能PORTB时钟
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //设置为推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOC, &GPIO_InitStructure);//初始化GPIOBA	
	GPIO_SetBits(GPIOC,GPIO_Pin_13);				 //PA4 输出高
}

/*@brief: LED测试函数，间隔500ms闪烁，通过delay_ms()函数实现
 * @param: None
 * @return: None
 */
void LED_test(void)
{
	LED=0;
	delay_ms(500);
	LED=1;
	delay_ms(500);
}
