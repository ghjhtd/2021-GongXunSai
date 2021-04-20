/**
  ******************************************************************************
  * @文件名 mstrack.c
  * @文件说明：本函数为串口直输式循迹模块驱动函数文件
  ******************************************************************************/
#include "delay.h"
#include "usart3.h"
#include "mstrack.h"
#include "string.h"
#include <stdlib.h>
#include "usart.h"	


/**
  * @brief  循迹模块初始化函数
  * @param  None
  * @return None
  */
void MsTrack_Init(void)
{
   usart3_init(115200);//循迹模块串口初始化 波特率115200
}

/**
  * @brief  循迹模块开始数据输出
  * @param  None
  * @return None
  */
void MsTrackStartDataOut(void)
{
   u3_printf("Start\r\n");  
}



/**
  * @brief  循迹模块停止数据输出
  * @param  None
  * @return None
  */
void MsTrackStopDataOut(void)
{
   u3_printf("Stop\r\n");  
}





/**
  * @brief  设置循迹模块输出频率
  * @param  fre:循迹模块设置的输出频率
			取值范围->	#define Fre10HZ 10
						#define Fre50HZ 50
						#define Fre100HZ 100
						#define Fre200HZ 200
						#define Fre300HZ 300
  * @return 设置成功返回1，失败返回0
  */
u8 SetOutTrackFre(int fre)
{
	MsTrackStopDataOut();//设置前先停止模块数据输出
	switch (fre)
	{
		case Fre10HZ:
			u3_printf("SetFre_10HZ\r\n");  
			printf("SetFre_10HZ\r\n");  
		break;
		case Fre50HZ:
			u3_printf("SetFre_50HZ\r\n");
		break;
		case Fre100HZ:
			u3_printf("SetFre_100HZ\r\n");
		break;
		case Fre200HZ:
			u3_printf("SetFre_200HZ\r\n");
		break;
		case Fre300HZ:
			u3_printf("SetFre_300HZ\r\n");
		break;
	}
	delay_ms(10);
	if(USART3_RX_STA&0x8000)
	{
		USART3_RX_STA=0;
		if(strcmp((char *)USART3_RX_BUF,"ok")==0)
		{
			return 1;
		}
	}
	MsTrackStartDataOut();//开启模块数据输出
	return 0;
}



/**
  * @brief  获取循迹模块String转Int类型数据，可通过此数据直接配置循迹车循迹
  * @param  *str:串口获取的字符串数据
  * @return dat：返回Int类型的数据
  */
int GetTrackString2IntData(u8 *str)
{
	int dat;
	dat=atoi((char *)str);
	return dat;
}












