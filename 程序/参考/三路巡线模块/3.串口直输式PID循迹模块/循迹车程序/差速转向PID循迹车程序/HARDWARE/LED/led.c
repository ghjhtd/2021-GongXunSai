/**
  ******************************************************************************
  * @�ļ��� led.c
  * @�ļ�˵�������ļ�Ϊ����LED����غ����ļ�
  ******************************************************************************/
#include "led.h"
#include "delay.h"	   
	    
/*@brief: LED��ʼ������
 * @param: None
 * @return: None
 */
void LED_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);//ʹ��PORTBʱ��
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //����Ϊ�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOC, &GPIO_InitStructure);//��ʼ��GPIOBA	
	GPIO_SetBits(GPIOC,GPIO_Pin_13);				 //PA4 �����
}

/*@brief: LED���Ժ��������500ms��˸��ͨ��delay_ms()����ʵ��
 * @param: None
 * @return: None
 */
void LED_test(void)
{
	LED=0;
	delay_ms(500);
	LED=1;
	delay_ms(500);
}
