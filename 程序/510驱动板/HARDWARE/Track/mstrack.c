/**
  ******************************************************************************
  * @�ļ��� mstrack.c
  * @�ļ�˵����������Ϊ����ֱ��ʽѭ��ģ�����������ļ�
  ******************************************************************************/
#include "delay.h"
#include "usart3.h"
#include "mstrack.h"
#include "string.h"
#include <stdlib.h>
#include "usart.h"	


/**
  * @brief  ѭ��ģ���ʼ������
  * @param  None
  * @return None
  */
void MsTrack_Init(void)
{
   usart3_init(115200);//ѭ��ģ�鴮�ڳ�ʼ�� ������115200
}

/**
  * @brief  ѭ��ģ�鿪ʼ�������
  * @param  None
  * @return None
  */
void MsTrackStartDataOut(void)
{
   u3_printf("Start\r\n");  
}



/**
  * @brief  ѭ��ģ��ֹͣ�������
  * @param  None
  * @return None
  */
void MsTrackStopDataOut(void)
{
   u3_printf("Stop\r\n");  
}





/**
  * @brief  ����ѭ��ģ�����Ƶ��
  * @param  fre:ѭ��ģ�����õ����Ƶ��
			ȡֵ��Χ->	#define Fre10HZ 10
						#define Fre50HZ 50
						#define Fre100HZ 100
						#define Fre200HZ 200
						#define Fre300HZ 300
  * @return ���óɹ�����1��ʧ�ܷ���0
  */
u8 SetOutTrackFre(int fre)
{
	MsTrackStopDataOut();//����ǰ��ֹͣģ���������
	switch (fre)
	{
		case Fre10HZ:
			u3_printf("SetFre_10HZ\r\n");  
			printf("SetFre_10HZ\r\n");  
		break;
		case Fre50HZ:
			u3_printf("SetFre_50HZ\r\n");
		break;
		case Fre100HZ:
			u3_printf("SetFre_100HZ\r\n");
		break;
		case Fre200HZ:
			u3_printf("SetFre_200HZ\r\n");
		break;
		case Fre300HZ:
			u3_printf("SetFre_300HZ\r\n");
		break;
	}
	delay_ms(10);
	if(USART3_RX_STA&0x8000)
	{
		USART3_RX_STA=0;
		if(strcmp((char *)USART3_RX_BUF,"ok")==0)
		{
			return 1;
		}
	}
	MsTrackStartDataOut();//����ģ���������
	return 0;
}



/**
  * @brief  ��ȡѭ��ģ��StringתInt�������ݣ���ͨ��������ֱ������ѭ����ѭ��
  * @param  *str:���ڻ�ȡ���ַ�������
  * @return dat������Int���͵�����
  */
int GetTrackString2IntData(u8 *str)
{
	int dat;
	dat=atoi((char *)str);
	return dat;
}












