//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//�о�԰����
//���̵�ַ��http://shop73023976.taobao.com
//
//  �� �� ��   : main.c
//  �� �� ��   : v2.0
//  ��    ��   : HuangKai
//  ��������   : 2018-10-31
//  ����޸�   : 
//  ��������   : OLED I2C�ӿ���ʾ����(STM32F103ϵ��)
//              ˵��: 
//              ----------------------------------------------------------------
//              GND  ��Դ��
//              VCC  3.3v��Դ
//              D0   PA5��SCL��
//              D1   PA7��SDA��              
//              ----------------------------------------------------------------
// �޸���ʷ   :
// ��    ��   : 
// ��    ��   : HuangKai
// �޸�����   : �����ļ�
//��Ȩ���У�����ؾ���
//Copyright(C) �о�԰����2018-10-31
//All rights reserved
//******************************************************************************/
#include "delay.h"
#include "sys.h"
#include "oled.h"
#include "bmp.h"
float servo[8][5]={0};

int len,t;
int num[8],num_cnt,cishu_flag;
char COMMAND[20],OPENMV[20];
void Send_data(USART_TypeDef * USARTx,u8 *s);
int send_flag=0,color,color_num=3,COLOR[3];
int test=0,test_usart=0,witch;
int main(void)
{
	u8 t;
	delay_init();
	NVIC_Configuration();
	servo_init(3);
	uart1_init(115200);  //���ͨѶ
	uart3_init(115200);		//openmv
	
	OLED_Init();
	OLED_ColorTurn(0);//0������ʾ��1 ��ɫ��ʾ
  OLED_DisplayTurn(0);//0������ʾ 1 ��Ļ��ת��ʾ
//	OLED_DrawPoint(0,0);
//	OLED_DrawLine(20,0,50,60);
//	OLED_DrawCircle(64,32,20);
	OLED_Refresh();
	t=' ';
	servo_control(0,0,1000);
	servo_control(1,80,1000);
	servo_control(2,-10,1000);
	servo_control(3,-30,1000);
	servo_control(4,0,1000);
	servo_control(5,0,1000);
//	delay_ms(1000);
//	servo_move(0,10,1000); //��Ϊ����ת
//	servo_move(1,10,1000); //��Ϊ����ת
//	servo_move(2,0,1000); //��Ϊ����
//	servo_move(3,20,1000); //��Ϊ����ת
//	servo_move(4,20,1000); //��Ϊ����ת
//	servo_move(5,20,1000); //��Ϊ�����
//	servo_control(0,90,500);
//	servo_control(1,90,1500);
//	delay_ms(1000);
//	servo_control(0,-90,1000);
//	delay_ms(1000);
//	servo_control(0,-60,2000);
//	servo_control(1,-90,2000);

	while(1)
	{
		if(USART1_RX_STA&0x8000)//���Է��ڶ�ʱ���ж���ִ��
		{
			len=(USART1_RX_STA&0x3fff);//�õ��˴ν��յ������ݳ���
		
			for(t=0;t<len;t++)
			{
				 COMMAND[t]=USART1_RX_BUF[t];				
			}
			COMMAND[t]='\0';
			USART1_RX_STA=0;
			if(COMMAND[0]=='S')
			{
				servo_control(COMMAND[1]-'0',atoi(&COMMAND[2]),100);
			}
		  if(COMMAND[0]=='M')
			{
				servo_move(COMMAND[1]-'0',atoi(&COMMAND[2]),100);
			}
			if(COMMAND[0]=='V')  //��openmv��������
			{
				USART_SendData(USART3,COMMAND[1]);
			}
			if(COMMAND[0]=='D')  //�ö������Ӧ�Ķ���
			{
				witch = COMMAND[1]-'0';
				switch(witch){
					case 0:   //ԭ�����ϲ�
						servo_control(0,0,100);
						delay_ms(600);
						servo_control(1,35,100);
						delay_ms(600);
						servo_control(2,-12,100);
						delay_ms(600);
						servo_control(3,25,100);
						delay_ms(600);
						servo_control(4,35,100);
						delay_ms(600);
						break;
					case 1: //ԭ�����²�
						servo_control(0,0,100);
						delay_ms(600);
						servo_control(1,-25,100);
						delay_ms(600);
						servo_control(2,13,100);
						delay_ms(600);
						servo_control(3,55,100);
						delay_ms(600);
						servo_control(4,0,100);
						delay_ms(600);
						break;
					case 2:  //�ּӹ� ��
						servo_control(0,-30,100);
						delay_ms(600);
						servo_control(1,-40,100);
						delay_ms(600);
						servo_control(2,28,100);
						delay_ms(600);
						servo_control(3,50,100);
						delay_ms(600);
						servo_control(4,0,100);
						delay_ms(600);
						break;
					case 3: //�ּӹ� ��
						servo_control(0,35,100);
						delay_ms(600);
						servo_control(1,-40,100);
						delay_ms(600);
						servo_control(2,28,100);
						delay_ms(600);
						servo_control(3,50,100);
						delay_ms(600);
						servo_control(4,0,100);
						delay_ms(600);
						break;
					case 4: //�ּӹ� ��
						servo_control(0,5,100);
						delay_ms(600);
						servo_control(1,-40,100);
						delay_ms(600);
						servo_control(2,23,100);
						delay_ms(600);
						servo_control(3,60,100);
						delay_ms(600);
						servo_control(4,35,100);
						delay_ms(600);
						break;
					case 5: //���ӹ� ��
						servo_control(0,-25,100);
						delay_ms(600);
						servo_control(1,-20,100);
						delay_ms(600);
						servo_control(2,13,100);
						delay_ms(600);
						servo_control(3,45,100);
						delay_ms(600);
						servo_control(4,35,100);
						delay_ms(600);
						break;
					case 6: //���ӹ� ��
						servo_control(0,35,100);
						delay_ms(600);
						servo_control(1,-20,100);
						delay_ms(600);
						servo_control(2,13,100);
						delay_ms(600);
						servo_control(3,40,100);
						delay_ms(600);
						servo_control(4,0,100);
						delay_ms(600);
						break;
					case 7: //���ӹ� ��
						servo_control(0,0,100);
						delay_ms(600);
						servo_control(1,-25,100);
						delay_ms(600);
						servo_control(2,23,100);
						delay_ms(600);
						servo_control(3,40,100);
						delay_ms(600);
						servo_control(4,0,100);
						delay_ms(600);
						break;
					case 8: //Ĭ��λ��
						servo_control(0,0,100);
						delay_ms(600);
						servo_control(1,80,100);
						delay_ms(600);
						servo_control(2,8,100);
						delay_ms(600);
						servo_control(3,-30,100);
						delay_ms(600);
						servo_control(4,0,100);
						delay_ms(600);
						break;
				}
			}
		}	
    lcd_show();
		//openmv();
		//Send_data(USART3,"q");
		//USART_SendData(USART1,test);
//		test++;
//		if(test>200) test =0;
		delay_ms(100);
	}
}


void Send_data(USART_TypeDef * USARTx,u8 *s)
{
 while(*s!='\0')
 { 
  while(USART_GetFlagStatus(USARTx,USART_FLAG_TC )==RESET); 
  USART_SendData(USARTx,*s);
  s++;
 }
}
