#ifndef _CONTROL_H_
#define _CONTROL_H_

#include "sys.h"


/***************�ⲿ��������***************/
extern long int Temp_POS;//����С��Ŀ��λ�ñ���
extern int ReadEncode;
extern u16 adc1,adc2,adc_m;
extern u8 END_FLAG;


/***************�ⲿ��������***************/
extern void MoveSpeed(int NowEncodeSpdL,int NowEncodeSpdR,float TarSpdL,float TarSpdR);//����С������Ŀ���ٶ�PID���ڵ�ǰ�ٶ�
extern void MoveDis(int NowEncodeLALL,int NowEncodeRALL,float TarDisL,float TarDisR);//����С������Ŀ�����PID���ڵ�ǰ�ٶ�
extern void TraceMove(int TraceDate,float TarSpeed);//����С��ѭ������
extern void TraceMoveWithDis(int TraceDate,float TarDis);//����Ŀ�����ѭ����ʻ������ʻĿ������ֹͣѭ��
#endif

