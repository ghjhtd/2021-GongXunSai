#ifndef _CONTROL_H_
#define _CONTROL_H_

#include "sys.h"


/***************外部变量声明***************/
extern long int Temp_POS;//定义小车目标位置变量
extern int ReadEncode;
extern u16 adc1,adc2,adc_m;
extern u8 END_FLAG;


/***************外部函数声明***************/
extern void MoveSpeed(int NowEncodeSpdL,int NowEncodeSpdR,float TarSpdL,float TarSpdR);//控制小车根据目标速度PID调节当前速度
extern void MoveDis(int NowEncodeLALL,int NowEncodeRALL,float TarDisL,float TarDisR);//控制小车根据目标距离PID调节当前速度
extern void TraceMove(int TraceDate,float TarSpeed);//控制小车循迹函数
extern void TraceMoveWithDis(int TraceDate,float TarDis);//根据目标距离循迹行驶，当行驶目标距离后停止循迹
#endif

