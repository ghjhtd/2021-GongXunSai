/**
  ******************************************************************************
  * @�ļ��� task.c
  * @�ļ�˵�������ļ�Ϊ�������������غ���
  ******************************************************************************/
#include "task.h"
#include "led.h"
#include "key.h"
#include "encoder.h"
#include "control.h"
#include "servor.h"
#include "track.h"
#include "motor.h"
#include "common.h"
#include "usart.h"
#include "LQ12864.h"

u16 LedTaskCount=0;//����Led��˸�����������
u16 KeyTaskCount=0;//���尴��ɨ���������
u16 EncoderTaskCount=0;//�����������������
u16 TrackTaskCount=0;//����ѭ�������������
u16 TrackConfigTaskCount=0;//ѭ�����������������������
u16 OledShowTaskCount=0;//OLED��ʾ�����������

//ȫ�ֱ�������
u8 TrackFlag=0;//����ѭ����־λ����


/*@brief: LED��˸����,����ʱʱ��500ms
 * @param: None
 * @return: None
 */
void LedTwinkleTask(void)
{
	if(LedTaskCount>500)
	{
		LedTaskCount=0;
		if((SensorCalFlag==0)&&(TrackFlag==1))//�ڴ�����û�����õ������LED�Ʋ���˸
		{
			LED=!LED;	
		}	
	}
}


/*@brief: ����ɨ��������������ʱʱ��50ms
 * @param: None
 * @return: None
 */
void KeyTask(void)
{
	u8 key;
	if(KeyTaskCount>50)
	{
		KeyTaskCount=0;
		key=KEY_Scan();//��ȡ���µİ���ֵ
		if(key==KEY0_PRES)
		{
			if(SensorCalFlag==0)
			{
				if(TrackFlag==0)	TrackFlag=1;
				else if(TrackFlag==1)	TrackFlag=0;			
			}
			else if(SensorCalFlag==1) //������ģʽ�г�������������ɲ��˳�����ģʽ
			{
				SensorCalFlag=2;
			}
		}		
		else if(key==KEY0_LONG_PRES)//�������
		{
			if(SensorCalFlag==0)	
			{
				SensorCalFlag=1;
				LED=0;//LED���������������ģʽ	
			}
		}
	}
}

/*@brief: ѭ����������ʱʱ��5ms
 * @param: None
 * @return: None
 */
void TraceTask(void)
{
	int TraceDate=0;//����ѭ���������������
	if(TrackTaskCount>5)
	{
		TrackTaskCount=0;
		if(TrackFlag==1)//�Ƿ���ѭ������
		{
			TraceDate=GetTraceDate();//��ȡPID����ѭ������������
//			printf("TraceDate:%d\r\n",TraceDate);							
			if(TraceDate==30000)//���������30000��ʾ��������
			{
				TrackFlag=0;
				MotorStop();
			}
			else //�������������ʱ��������ѭ��
			{
				TraceMove(TraceDate,0.3);//����ѭ�����������ݿ���С�������趨�ٶ�ѭ��
//				MoveDis(Encode_Left_ALL,Encode_Right_ALL,0.5,0.5);//����ѭ�����������ݿ���С�������趨����ѭ��
			}
		}	
	}
}


/*@brief: ѭ��������������������ʱʱ��50ms
 * @param: None
 * @return: None
 */
void TraceConfigTask(void)
{
	if(TrackConfigTaskCount>50)
	{
		TrackConfigTaskCount=0;
		if(SensorCalFlag==1||SensorCalFlag==2)//������ð������������ѭ������������
		{
			GetParament();
		}	
	}	
}	

/*@brief: OLED����ʾ��������ʱʱ��200ms
 * @param: None
 * @return: None
 */	
void OledShowTask(void)
{
	char buff[50];
	int trackdate=0;
	if(OledShowTaskCount>200)
	{
		OledShowTaskCount=0;
		Show_Battary_Vol();//����ʾ������ʾ��ص�ѹ
		trackdate=GetTraceDate();//��ȡѭ������������
		sprintf(buff,"trackdate:%d    ",trackdate);//�����������ڶ�ʱ��4�ж��л�ȡ
		OLED_P6x8Str(1,4,(u8 *)buff);//��ʾѭ������������
		printf("Encode_Left_ALL:%d\r\n",Encode_Left_ALL);
	}
	
}	

/*@brief: ��ʱ��2�жϸ��º�������ʱ��2��Ϊ������䶨ʱ������ʱʱ��1ms
 * @param:None
 * @return: None
 */
void TIM2_IRQHandler(void)
{ 		    		  			    
	if(TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)  //���TIM3�����жϷ������
	{
		LedTaskCount++;
		KeyTaskCount++;
		EncoderTaskCount++;	
		TrackTaskCount++;
		TrackConfigTaskCount++;
		OledShowTaskCount++;
		/******��Ҫ��ʱ���������******/
		if(EncoderTaskCount>=5)//��������ȡ���񣬶�ȡʱ��5ms
		{
			EncoderTaskCount=0;
			Encode_Left=-Read_Encoder(3);//��ȡ���ֱ���������
			Encode_Left_ALL+=Encode_Left;//�����ۼ�ֵ	
			Encode_Speed=Encode_Left;//ǰ���ٶ�
		}	
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);  //���TIMx�����жϱ�־
	}    
}



