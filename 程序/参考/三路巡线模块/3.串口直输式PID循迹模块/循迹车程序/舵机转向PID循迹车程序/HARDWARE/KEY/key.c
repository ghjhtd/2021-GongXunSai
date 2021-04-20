#include "stm32f10x.h"
#include "key.h"
#include "sys.h" 
#include "delay.h"
								    
//������ʼ������
void KEY_Init(void) //IO��ʼ��
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//ʹ��PORTA,PORTEʱ��

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_12;//KEY0-KEY2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
 	GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOE2,3,4
}



/*@brief: �˺���Ϊ����ɨ�躯��
 * @param: None
 * @return: �������µĽ���������̰�ʱ����KEY0_PRES,���³���ʱ�����1Sʱ����KEY0_LONG_PRES
 */
u8 KEY_Scan(void)
{	 
	static u8 key_up=1;//�������ɿ���־������ʱΪ1���ɿ�ʱΪ0
	static u16 keytimecount=0;	  
	if(key_up&&(KEY0==0))
	{
		delay_ms(10);//ȥ���� 
		if(KEY0==0) key_up=0;
	}
	else if(KEY0==1)
	{
		if(key_up==0)
		{
			key_up=1; 			
			if(keytimecount<40)
			{
				keytimecount=0;
				return KEY0_PRES;
			}
			keytimecount=0;
		}
	}
	if(key_up==0)//�������������10msʱ���ʱ
	{
		delay_ms(10);
		keytimecount++;
		if(keytimecount==40)//�������ʱ�����1s�򷵻ذ�������
		{
			return KEY0_LONG_PRES;
		}	
	}
	return 0;// �ް�������
}




