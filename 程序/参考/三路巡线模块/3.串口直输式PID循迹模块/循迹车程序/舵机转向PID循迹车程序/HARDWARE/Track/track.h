#ifndef _TRACK_H__
#define _TRACK_H__


/****************�ⲿ��������*****************/
extern int D_AD_VALUE; 		//ȷ�����Ҵ�������ֵ
extern int LEFT_MAX;   	    //�󴫸�����ֵ
extern int MID_MAX;  		//�м䴫������ֵ
extern int RIGHT_MAX;  	    //�Ҵ�������ֵ
extern int LEFT_THERSH;	    //�󴫸�����ֵ
extern int RIGHT_THERSH;	//�Ҵ�������ֵ
extern int LEFT_SPAN;		//�����������ƶ���Ծ��ֵ   
extern int RIGHT_SPAN;	    //�����������ƶ���Ծ��ֵ


extern int SensorCalFlag;//����ȫ�ֱ���������У׼��־λ��Ϊ1��ʼУ׼��Ϊ2У׼��ɣ�Ϊ0У׼���� 

/******************��������*******************/
extern void Track_Init(void);
extern int GetTraceDate(void);
extern void GetParament(void);

#endif

