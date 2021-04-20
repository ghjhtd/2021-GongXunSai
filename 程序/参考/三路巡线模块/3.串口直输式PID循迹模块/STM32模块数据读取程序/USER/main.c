/**
  ******************************************************************************
  * @�ļ��� main.c
  * @�ļ�˵����������Ϊħʯ����ֱ��ʽѭ��ģ�����ݶ�ȡ����ͨ������3��ȡѰ��ģ�����ݣ�
	ͨ������1����ȡ��Ѱ��ģ�����ݷ��͵������ϣ�ͨ��PC13 LEDָʾ����˸ָʾ�Ƿ��յ�����
  * @��д�ˣ�Dinvent
  * @ħʯ�Ƽ�
  * @�Ա��������ӣ�
  ******************************************************************************/
#include "sys.h"
#include "delay.h"
#include "usart3.h"
#include "led.h"
#include "usart.h"	  
#include "mstrack.h"


 int main(void)
 {
	int TrackDate;
	delay_init();//��ʱ������ʼ��
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	//���ڳ�ʼ�� ������115200
	MsTrack_Init();
	LED_Init();	 		//��ʼ����LED���ӵ�Ӳ���ӿ�
	while(1)
	{		
		if(USART3_RX_STA&0x8000)//���Է��ڶ�ʱ���ж���ִ��
		{
			LED=!LED;//���յ�һ֡���ݺ�LED״̬�仯һ��
			USART3_RX_STA=0;
			
			TrackDate=GetTrackString2IntData(USART3_RX_BUF);//����ȡ�����ַ�������ת��Ϊ��������
			printf("TrackDate:%d\r\n",TrackDate);
			memset(USART3_RX_BUF, 0, sizeof(USART3_RX_BUF));//����ȡ��������������
		}
	}
 }

 
	
 
 
 

