#ifndef __MSTRACK_H
#define __MSTRACK_H	 
#include "sys.h"  
	   

/****************循迹模块输出频率参数******************/
#define Fre10HZ 10
#define Fre50HZ 50
#define Fre100HZ 100
#define Fre200HZ 200
#define Fre300HZ 300


/****************循迹模块输出频率参数******************/
extern void MsTrack_Init(void);//循迹模块初始化函数
extern void MsTrackStartDataOut(void);//开启模块数据输出
extern void MsTrackStopDataOut(void);//停止模块数据输出
extern u8 SetOutTrackFre(int fre);;//设置模块数据输出频率
extern int GetTrackString2IntData(u8 *str);//获取循迹模块String转Int类型数据，可通过此数据直接配置循迹车循迹

#endif













