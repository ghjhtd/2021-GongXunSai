/**
  ******************************************************************************
  * @文件名 beep.c
  * @文件说明：本文件为蜂鸣器驱动相关函数文件
  ******************************************************************************/
#include "beep.h"
#include "delay.h"

/*@brief: 蜂鸣器初始化函数
 * @param: None
 * @return: None
 */
void Beep_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;    
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_5;//PA2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //设置为推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA8	
	GPIO_SetBits(GPIOA,GPIO_Pin_5);				 //PA8 输出高
}

/*@brief: 让蜂鸣器响N声
 * @param: [in] n的次数
 * @return: None
 */
void N_Beep(char n)
{
	u32 i=0,j=0;
	for(i=n;i>0;i--)
	{
		for(j=500;j>0;j--)
		{
		  Beep=~Beep;      
		  delay_us(300);      
		}
	}
	for(i=n;i>0;i--)
	{
		for(j=500;j>0;j--)
		{     
		  delay_us(300);      
		}
	}
}


