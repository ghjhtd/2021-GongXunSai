#ifndef __LED_H
#define __LED_H	 
#include "sys.h"


#define LED PCout(13)// PA5



/*******************外部函数声明***************************/
extern void LED_Init(void);//初始化
extern void LED_test(void);
		 				    
#endif
