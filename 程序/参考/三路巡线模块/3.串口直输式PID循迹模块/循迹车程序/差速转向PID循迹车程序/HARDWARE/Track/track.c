/**
  ******************************************************************************
  * @�ļ��� ��track.c
  * @�ļ�˵�������ļ�Ϊ���ں���ѭ�������������У׼�ĺ���
  * @�汾��V1.2.1
  * @���ڣ�2020-12-12 
  * @ħʯ�Ƽ�@
  * @�Ա��������ӣ�https://shop418595371.taobao.com
  *  ����ֱ���Ա���������ħʯ���ӿƼ�������
  ******************************************************************************/
#include "track.h"
#include "adc.h"
#include "stdio.h"
#include "stdlib.h"
#include "led.h"
#include "datastore.h"
#include "led.h"
#include "delay.h"

int SensorCalFlag=0;//����ȫ�ֱ���������У׼��־λ��Ϊ1��ʼУ׼��Ϊ2У׼��ɣ�Ϊ0У׼����  


static int PosFlagValue;//������ֵ����


int D_AD_VALUE=-400; 	//ȷ�����Ҵ�������ֵ
int LEFT_MAX=2927;   	//�󴫸�����ֵ
int RIGHT_MAX=2868;  	//�Ҵ�������ֵ
int MID_MAX=2868;  		//�м䴫������ֵ
int LEFT_THERSH=954;	//�󴫸�����ֵ
int RIGHT_THERSH=1258;	//�Ҵ�������ֵ
int LEFT_SPAN=3763;		//�����������ƶ���Ծ��ֵ   //790
int RIGHT_SPAN=-2831;	//�����������ƶ���Ծ��ֵ   //1023int SensorCalFlag=0;//����ȫ�ֱ���������У׼��־λ��Ϊ1��ʼУ׼��Ϊ2У׼��ɣ�Ϊ0У׼����  


/**
  * @brief  ����ѭ����������ʼ������
  * @param  None
  * @return None
  */
void Track_Init(void)
{
	Adc_Init();			//�ڲ�ADC��ʼ������	
	if(CheckData())		//����Ƿ�FLASH�д洢�����ݣ������������������
    {
		ReadTrackData();
    }
	PosFlagValue=(int)((LEFT_MAX+RIGHT_MAX-LEFT_THERSH-RIGHT_THERSH)/3.0f);
}


/*@brief: ��ȡѭ���������������
 * @param: None
 * @return: int���ͣ���Χѭ�����������ݣ����ݴ�ֵ������С������Ƕ�,
 *			һ�����ѭ���������-10000��10000֮�䣬���30000��ʾ����
 *          ֹͣ�ߣ�����ŵĺ���
 */
int GetTraceDate(void)
{
	int Data_Out;//���������������
	int Left_AD,Right_AD,Mid_AD;//���������д�����ADֵ����
	static char PosFlag=0;//���崫����λ�ñ�־λ��0��Ϊ�������ں���ƫ��λ�ã�1��ΪС���ڴ�����ƫ��λ��
	 	
	Right_AD=Get_Adc(2);	//�󴫸�����ȡ��ADֵ
	Mid_AD=Get_Adc(3);		//�м䴫������ȡ��ADֵ
	Left_AD=Get_Adc(4);		//�Ҵ�������ȡ��ADֵ
	
	if((Left_AD>=(LEFT_MAX*1.0f))&&(Mid_AD>=(MID_MAX*1.0f))&&(Right_AD>=(RIGHT_MAX*1.0f)))
	return 30000;
//	printf("L:%d M:%d R:%d\r\n",Left_AD,Mid_AD,Right_AD);
	Data_Out=(Left_AD-Right_AD+D_AD_VALUE);
//	printf("Data_Out��%d\r\n",Data_Out);
	if(Data_Out>PosFlagValue)
	{
		PosFlag=1;
	}
	else if(Data_Out<-PosFlagValue)
	{
		PosFlag=0;
	}
	if(Mid_AD<LEFT_THERSH)
	{	
		if(Data_Out>PosFlagValue)
		{
			Data_Out=(2*LEFT_MAX-Left_AD)*2-LEFT_SPAN;
		}
		else if((Data_Out<PosFlagValue)&&(PosFlag==1))
		{
			Data_Out=abs((2*LEFT_MAX-Left_AD)*2-LEFT_SPAN);
		}
		
	} 
	
	if(Mid_AD<RIGHT_THERSH)
	{	
		if(Data_Out<-PosFlagValue)
		{
			Data_Out=(Right_AD-2*RIGHT_MAX)*2-RIGHT_SPAN;
		}
		else if((Data_Out>-PosFlagValue)&&(PosFlag==0))
		{
			Data_Out=-abs((Right_AD-2*RIGHT_MAX)*2-RIGHT_SPAN);
		}
	}
	
	return Data_Out;
}


/*@brief: �˺���Ϊѭ��������У׼����
 * @param: None
 * @return: None
 */
void GetParament(void)
{
	int DValue=0;
	int Left_AD,Right_AD,Mid_AD;//���������д�����ADֵ����
	
	static int LeftMax=0;
	static int RightMax=0;
	static int MidMax=0;
	static int Left_Thersh=0;
	static int Right_Thersh=0;
	static int Left_Span=0;
	static int Right_Span=0;
	
	Right_AD=Get_Adc(2); 	//�Ҵ�������ȡ��ADֵ
	Mid_AD=Get_Adc(3);		//�м䴫������ȡ��ADֵ
	Left_AD=Get_Adc(4);		//�󴫸�����ȡ��ADֵ
	
	if(Left_AD>LeftMax)	
	{
		LeftMax=Left_AD;
		Left_Thersh=Mid_AD;
		Left_Span=(2*LeftMax-Left_AD)*2-(Left_AD-Right_AD+D_AD_VALUE);
		
	}
	if(Right_AD>RightMax)
	{
		RightMax=Right_AD;
		Right_Thersh=Mid_AD;
		Right_Span=(Right_AD-2*RightMax)*2-(Left_AD-Right_AD+D_AD_VALUE);	
	}	

	if(Mid_AD>MidMax)
	{
		MidMax=Mid_AD;
	}		
	DValue=Right_AD-Left_AD;//��ֵ���Ҵ��������󴫸���
	
	if(SensorCalFlag==2)//�������У׼��ɰ�������У׼�����ݴ��浽EEROM�в�ʹ����У׼������
    {
		D_AD_VALUE=DValue;
		LEFT_MAX=LeftMax;
		RIGHT_MAX=RightMax;
		LEFT_THERSH=Left_Thersh;
		RIGHT_THERSH=Right_Thersh;
		LEFT_SPAN=Left_Span;
		RIGHT_SPAN=Right_Span;
		StoreTrackData();  
		LED=1;
		SensorCalFlag=0;     
    }
	printf("Right_AD:%d Mid_AD:%d Left_AD:%d\r\n",Right_AD,Mid_AD,Left_AD);
	printf("D_AD_VALUE:%d LeftMax:%d MidMax:%d RightMax:%d  Left_Thersh:%d Right_Thersh:%d Left_Span:%d Right_Span:%d\r\n",DValue,LeftMax,MidMax,RightMax,Left_Thersh,Right_Thersh,Left_Span,Right_Span);
}




