#ifndef __MSTRACK_H
#define __MSTRACK_H	 
#include "sys.h"  
	   

/****************ѭ��ģ�����Ƶ�ʲ���******************/
#define Fre10HZ 10
#define Fre50HZ 50
#define Fre100HZ 100
#define Fre200HZ 200
#define Fre300HZ 300


/****************ѭ��ģ�����Ƶ�ʲ���******************/
extern void MsTrack_Init(void);//ѭ��ģ���ʼ������
extern void MsTrackStartDataOut(void);//����ģ���������
extern void MsTrackStopDataOut(void);//ֹͣģ���������
extern u8 SetOutTrackFre(int fre);;//����ģ���������Ƶ��
extern int GetTrackString2IntData(u8 *str);//��ȡѭ��ģ��StringתInt�������ݣ���ͨ��������ֱ������ѭ����ѭ��

#endif













