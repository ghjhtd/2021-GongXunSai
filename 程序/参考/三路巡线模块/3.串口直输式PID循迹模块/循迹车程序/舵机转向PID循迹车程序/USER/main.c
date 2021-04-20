/**
  ******************************************************************************
  * @�ļ��� main.c
  * @�ļ�˵�������ļ�ΪPID���ת��ѭ�������������ļ�
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
#include "task.h"


int main(void)
{
	delay_init();//��ʱ������ʼ��
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	//���ڳ�ʼ�� ������115200
	Track_Init();		//ѭ����������������
	OLED_Init();		//OLED��ʼ������
	KEY_Init();			//������ʼ������
	LED_Init();	 		//��ʼ����LED���ӵ�Ӳ���ӿ�
	Beep_Init(); 		//��������ʼ������		 
	Motor_Init();		//�����ʼ������
	NRF24L01_Init();	//NRF24L01��ʼ��
	NRF24L01_TX_Mode();	//����NRF24L01�ɷ���ģʽ
	Encoder_Init();		//��������ʼ��	
	Servor_Init();		//�����ʼ������
	Show_CH(20,0);		//��OLED����ʾ���ı���	
	TIM2_Int_Init(7200-1,10-1);//��ʱʱ��1ms
	while(1)
	{		
		TraceTask();//ѭ������
		TraceConfigTask();//ѭ����������������
		LedTwinkleTask();//LED��˸����
		KeyTask();//����ɨ������
		OledShowTask();//OLED��ʾ����
	}
}


	

