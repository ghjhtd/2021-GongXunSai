#ifndef __COMMON_H_
#define	__COMMON_H_

#include "sys.h"



/***************关于车子的参数****************/
#define WheelDiameter 0.066f //定义小车轮子直径,6.6cm
#define CarWidth 0.194f		//定义小车两个轮子间距，19.4cm



/***************关于赛道的参数****************/
#define Rode_L 1000		//定义轨道长度，单位厘米
#define Rode_Cilcle 47  //定义小车走完一趟所用的圈数


/*****************外部变量声明****************/
extern u8 TrackFlag;

/*****************外部函数声明****************/
void Show_Battary_Vol(void);



#endif



