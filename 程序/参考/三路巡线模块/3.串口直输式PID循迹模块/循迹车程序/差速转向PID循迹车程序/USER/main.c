/**
  ******************************************************************************
  * @�ļ��� main.c
  * @�ļ�˵�������ļ�ΪPIDѭ�������������ļ�
  * @��д�ˣ�Dinvent
  * @�汾��V1.1.0
  * @���ڣ�2020-12-12 
  * @ħʯ�Ƽ�
  * @�Ա��������ӣ�https://shop418595371.taobao.com
  *  ����ֱ���Ա���������ħʯ���ӿƼ�������
  ******************************************************************************/
#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "beep.h" 
#include "led.h"
#include "motor.h"
#include "servor.h"
#include "LQ12864.h"
#include "encoder.h"   
#include "timer.h"
#include "common.h"
#include "control.h"
#include "adc.h"
#include "track.h"
#include "24l01.h"
#include "key.h"
#include "stmflash.h"
#include "datastore.h"





int main(void)
{
//	char buff[100];
	int TraceDate=0;//����ѭ���������������
	u8 key=0;//���尴����������ȡ���µİ���ֵ
	delay_init();//��ʱ������ʼ��
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	//���ڳ�ʼ�� ������115200
	Track_Init();		//ѭ����������������
	OLED_Init();		//OLED��ʼ������
	KEY_Init();			//������ʼ������
	LED_Init();	 		//��ʼ����LED���ӵ�Ӳ���ӿ�
	Beep_Init(); 		//��������ʼ������		 
	Motor_Init();		//�����ʼ������
	NRF24L01_Init();	//24L01��ʼ��
	NRF24L01_TX_Mode();	//���óɷ���ģʽ
	Encoder_Init();		//��������ʼ��	
	Show_CH(20,0);		//��ʾ���ı���	
	Set_Motor_PWM(0);	//���õ��ת��Ϊ���	
	while(1)
	{		
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

		if(SensorCalFlag==1||SensorCalFlag==2)//������ð������������ѭ������������
		{
			GetParament();
			delay_ms(50);
		}
		if(SensorCalFlag==0)//�ж��Ƿ�ѭ����������������ģʽ
		{
			if(TrackFlag==1)//�Ƿ���ѭ������
			{
				TraceDate=GetTraceDate();//��ȡPID����ѭ������������
//				printf("TraceDate:%d\r\n",TraceDate);				
				if(TraceDate==30000)//���������30000��ʾ��������
				{
					TrackFlag=0;
					MotorStop();
				}
				else //�������������ʱ��������ѭ��
				{
					TraceMove(TraceDate,0.1);//����ѭ�����������ݿ���С�������趨�ٶ�ѭ��
//					MoveDis(Encode_Left_ALL,Encode_Right_ALL,0.5,0.5);//����ѭ�����������ݿ���С�������趨����ѭ��
				}	
				delay_ms(5);//PID����ʱ����ʱ									   
			}	
		}
		Show_Battary_Vol();//����ʾ������ʾ��ص�ѹ
	}
}

 
 
 
	

