#include "stm32f10x.h"
#include "key.h"
#include "sys.h" 
#include "delay.h"
								    
//按键初始化函数
void KEY_Init(void) //IO初始化
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//使能PORTA,PORTE时钟

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_12;//KEY0-KEY2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
 	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOE2,3,4
}



/*@brief: 此函数为按键扫描函数
 * @param: None
 * @return: 按键按下的结果，按键短按时返回KEY0_PRES,按下长按时间大于1S时返回KEY0_LONG_PRES
 */
u8 KEY_Scan(void)
{	 
	static u8 key_up=1;//按键按松开标志，按下时为1，松开时为0
	static u16 keytimecount=0;	  
	if(key_up&&(KEY0==0))
	{
		delay_ms(10);//去抖动 
		if(KEY0==0) key_up=0;
	}
	else if(KEY0==1)
	{
		if(key_up==0)
		{
			key_up=1; 			
			if(keytimecount<40)
			{
				keytimecount=0;
				return KEY0_PRES;
			}
			keytimecount=0;
		}
	}
	if(key_up==0)//如果按键按下则按10ms时间计时
	{
		delay_ms(10);
		keytimecount++;
		if(keytimecount==40)//如果长按时间大于1s则返回按键长按
		{
			return KEY0_LONG_PRES;
		}	
	}
	return 0;// 无按键按下
}




