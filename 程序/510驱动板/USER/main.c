#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"
#include "timer.h"
#include "oled.h"
#include "control.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*����      �ĸ����� */
int key = 0, program = 0;
int Encoder1,Encoder2,Encoder3,Encoder4;

volatile u8 Adc_Key = 0;   //adc������̼�ֵ
/* ������ʾ */
char OLED_sprintf_str[20];

int usart_flag=1,usart_flag2;
/* -------------PID Para */
float	Bias		= 0;
float	Last_Bias	= 0, Delta_Bias = 0, Delta_Delta_Bias = 0, Pre_Delta_Bias = 0;

/* 10 5  1 */
float	Balance_KP		= 3.5, Balance_Ki = 0.3, Balance_KD = 10.0;
int KL,angle_1_flag,ii,iii=0,iiii;           //�������
float Goal_value=0;//��Ҫ��Ŀ��Ƕ�
float angle_1=0.0,angle_2=30,angle_3;//��ǰ���ĽǶ�
u8 RX_BUF[15],RX_CNT;  //����ͷ����ͨѶ����洢
int x,y,r,length,biaoju,baju,yaim=80;
int pwm1,pwm2,pwm3,pwm4;
int a;
float pitch,roll,yaw; 
int mode=2;
int AIM_1,AIM_2,AIM_3,AIM_4;//�����ٶ�Ŀ��ֵ
int AIM_max=6;//�ٶȵ�λ
int PS2_LX,PS2_LY,PS2_RX,PS2_RY,PS2_KEY,TURN;

char YOU[30];
char ZUO[30];
char QIAN[30];
int sum;
u8 j;
float ADC_Value[3];//??????????????

int volatile qian,zuo,you,Xunxian,Pinxin,Juli,Chuizhi;  //  ��������ѭ��ģ���� ����ƽ��ʹ��
int X,Y;   //С���ڵ�ͼ�ϵĶ�λ���꣬��ͼ���½ǵ�������0��0

extern int GetTrackString2IntData(u8 *str);  //ѭ��ģ������ת������

int main( void )
{
	u8 problem_temp = 0;                                    /* ��ʱ���� K1�޸� K0ȷ����ֵ��ȫ��problem */

  Stm32_Clock_Init(9);                           //ϵͳʱ��72M
	delay_init(72);	                              //��ʱ��ʼ��
	NVIC_PriorityGroupConfig( NVIC_PriorityGroup_2 );       /* ����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ� */
  PC3_Init();
	uart_init( 72,115200 );                                    /* ���ڳ�ʼ��Ϊ115200 */
  uart2_init(115200);
	
	
	PS2_Init();											//=====ps2�����˿ڳ�ʼ��
	
	
	Encoder_Init_TIM1();
	Encoder_Init_TIM3();
	Encoder_Init_TIM4();
	Encoder_Init_TIM5();
  
	Motor_Init();
	LED_Init();                                             /* LED�˿ڳ�ʼ�� */
	KEY_Init();                                             /* key init */
	OLED_Init();
	PS2_SetInit();		 							//=====ps2���ó�ʼ��,���á����̵�ģʽ������ѡ���Ƿ�����޸�

  //IIC_Init();

	PS2_Vibration(0X40,0);
	OLED_ShowString( 0, 12, "--NCEPU--", 16,1);    /* 8*16 ��ABC�� */
	OLED_ShowString( 0, 28, "CIE510", 24,1);    /* 12*24 ��ABC�� */
	OLED_Refresh();
	delay_ms(500);
  OLED_Clear();
	
	
	
  TIM8_PWM_Init( 7199, 9 );  	/* PWMƵ��=1k */
	
	
	uart3_init(115200);     //ǰѭ��ģ��
	uart4_init(115200);     //��ѭ��ģ��
	uart5_init(115200);			//��ѭ��ģ��
	
	

//  OLED_ShowString(0,12,"y 00",12);        //
//	OLED_ShowString(0,24,"r 00",12);
//	OLED_ShowString(30,12,"a000 PA0000",12);
//	OLED_ShowString(30,24,"A000 PB0000",12);
//	OLED_ShowString(0,48,"P00 I000 D000",12);
	//OLED_Refresh();
	/* PWM */
	//TIM3_PWM_Init( 7199, 199 );  


	
	
//	TIM_SetCompare1( TIM8, 600 ); 	//c6789    //����pwm
//	GPIO_SetBits(GPIOC,GPIO_Pin_0);	
//	GPIO_ResetBits(GPIOC,GPIO_Pin_1);
//	
//	TIM_SetCompare2( TIM8, 600 );
//	GPIO_SetBits(GPIOE,GPIO_Pin_7);	
//	GPIO_ResetBits(GPIOE,GPIO_Pin_6);	
//	
//	TIM_SetCompare3( TIM8, 600 );
//	GPIO_SetBits(GPIOB,GPIO_Pin_1);	
//	GPIO_ResetBits(GPIOB,GPIO_Pin_0);
//	
//	
//	TIM_SetCompare4( TIM8, 540 );
//	GPIO_SetBits(GPIOE,GPIO_Pin_0);	
//	GPIO_ResetBits(GPIOE,GPIO_Pin_1);	

	/* ��ʱ���ж� */
	//TIM1_Int_Init( 4900, 7199 );
//	TIM6_Int_Init( 49, 7199 );    /* 10Khz�ļ���Ƶ�ʣ�������49Ϊ5ms */
	//TIM7_Int_Init( 499, 7199 );    /* 10Khz�ļ���Ƶ�ʣ�������49 is 5ms */
 
 		delay_ms(50);
		
		Adc_Init();     //ADC��DMA��ʼ��
		DMA_ADC_Init();
		ADC_SoftwareStartConvCmd(ADC1, ENABLE);//ADC�����������			
		
		while(1)
		{
			OLED_ShowString( 0, 0, "Which Program?(1-6)", 12,1); 
			OLED_Refresh();		
			while(program==0||(key != 5 && PS2_KEY != 13))	
				{
					key = ADC_Key(ADCConvertedValue[0][2],0);
					PS2_KEY=PS2_Keyscan(0);
					if(key == 8 || PS2_KEY == 1)
						{	
							program++;
							if(program>=7)
							program=1;		
						}	
					if(key == 2)
						{	
							program--;
							if(program<=0)
							program=6;							
						}
					OLED_Clear();
					OLED_ShowString( 0, 0, "Which Program?(1-6)", 12,1); 
					OLED_ShowNum(0,16,program,1,12,0);
					switch( program ){
						case 1:
							OLED_ShowString(8, 16, "-PS2_remote control", 12,1); 
							break;
						case 2:
							OLED_ShowString(8, 16, "-Auto Run of chusai", 12,1); 
							
							break;
						case 3:
							OLED_ShowString(8, 16, "-run Test", 12,1); 
							break;
						case 4:
							OLED_ShowString(8, 16, "-Key Test", 12,1); 
							break;
						case 5:
							OLED_ShowString(8, 16, "-XunjiTest", 12,1); 
							break;
						case 6:
							OLED_ShowString(8, 16, "-None", 12,1); 
							break;				
					}
					OLED_Refresh();	
					delay_ms(50);
				}
		
		OLED_Clear();
		OLED_ShowNum(0,0,program,1,12,0);
    OLED_ShowString(12, 0, "Program", 12,1); 
		OLED_Refresh();	
		delay_ms(500);
		OLED_Clear();		
    switch (program)
			{
				case 1:  //�����ֱ�ң��
					TIM6_Int_Init( 49, 7199 );    //�������
				  PS2_Vibration(0,0X40)	 ;
		      while ( 1 )
		      	{	
		      		xunji_show();
						//	lcd_show;
		      		delay_ms(5);
		      
		      		PS2_LX=127-PS2_AnologData(PSS_LX);    
		      		PS2_LY=127-PS2_AnologData(PSS_LY);
		      		PS2_RX=127-PS2_AnologData(PSS_RX);
		      		PS2_RY=127-PS2_AnologData(PSS_RY);
		      		if(PS2_LX==-128&&PS2_LY==-128&&PS2_RX==-128&&PS2_RY==-128)
		      		PS2_LX=0,PS2_LY=0,PS2_RX=0,PS2_RY=0;
		      		PS2_KEY=PS2_Keyscan(1);
		      		if(PS2_KEY==PSB_L2)	
		      			{
		      				if(AIM_max==10)
		      				AIM_max=5;
		      				else
		      				AIM_max=10;	
		      			}		
		      		if(PS2_KEY==PSB_R2)
		      			PCout(3)=1;
		      		else
		      		PCout(3)=0;
		      		if(PS2_KEY==PSB_L1)
		      			TURN=128;
		      		else 
		      				if(PS2_KEY==PSB_R1)
		      					TURN=-128;
		      				else
		      					TURN=0;
//		      		printf("%d     PS2_LX:",PS2_LX);
//		      		printf("%d     PS2_LY:",PS2_LY);
//		      		printf("%d     PS2_RX:",PS2_RX);
//		      		printf("%d     PS2_RY:",PS2_RY);
//		      		printf("%d \r\nPS2_KEY:",PS2_KEY);
          
		      		if(ADC_Key(ADCConvertedValue[0][2],1) == 3 || PS2_Keyscan(1)==PSB_BLUE)      //����0�������˵�
		      			{	
		      				OLED_Clear();
		      				program=0;
		      				break;
		      			}
		      		}
					break;
							
				case 2:    //ѭ������
					TIM6_Int_Init( 49, 7199 );    //�������
					OLED_Clear();
					OLED_ShowString(0, 0, "Press Key1 to start", 12,1);
					OLED_ShowString(0, 16, "Press Key0 to return", 12,1); 
					OLED_Refresh();	
					while ( 1 )
						{
							key=KEY_Scan(0);								
							if ( key == 2 )   ////����1��ʼ����
								{
								/* K1 ��Ŀ�޸� */
								USART_SendData(USART2, 'q');
								LED0 = !LED0;
								TIM6_Int_Init( 49, 7199 );    //�������
								TIM7_Int_Init( 99, 7199 );														
								}
							if(key == 1)      //����0�������˵�
								{	
									OLED_Clear();
									program=0;
									break;
								}
						}
					break;
					
				case 3:   //Test
					TIM6_Int_Init( 49, 7199 );
					while(1){
						PS2_LX = 50;
						PS2_LY = 0;
						delay_ms(1000);
						PS2_LY = 50;
						PS2_LX = 0;
						delay_ms(1000);
						PS2_LX = -50;
						PS2_LY = 0;
						delay_ms(1000);
						PS2_LY = -50;
						PS2_LX = 0;
						delay_ms(1000);
						if(ADC_Key(ADCConvertedValue[0][2],1) == 3 || PS2_Keyscan(1)==PSB_BLUE)      //����3�������˵�
		      			{	
		      				OLED_Clear();
		      				program=0;
		      				break;
		      			}
					}
					break;
					
				case 4:  //adc Test
								
					while(1)
					{
							sum=0;
							for(j=0;j<10;j++)
							{
								sum+=ADCConvertedValue[j][2];
							}
							ADC_Value[2]=(float)sum/(10*4096)*3.3;//???????????
							//OLED_Clear();
							OLED_ShowString(0, 20, "chushi  ", 12,1);
					    OLED_ShowNum(50,20,ADCConvertedValue[0][2],6,12,1);
					    OLED_ShowString(0, 0, "dianya  ", 12,1);
					    OLED_ShowNum(50,0,ADC_Value[2],6,12,1); 
					    OLED_ShowNum(0,30,ADC_Key(ADCConvertedValue[0][2],1),1,12,1);  		
					    OLED_Refresh();	
							if(ADC_Key(ADCConvertedValue[0][2],1) == 3 || PS2_Keyscan(1)==PSB_BLUE)      //����3�������˵�
		      			{	
		      				OLED_Clear();
		      				program=0;
		      				break;
		      			}

					}
					break;
					
				case 5:    //����������
					while(1){
						Encoder1=-Read_Encoder(1);
						Encoder2= Read_Encoder(3);
						Encoder3= Read_Encoder(5);
						Encoder4=-Read_Encoder(4);
						OLED_ShowNum(0,0,Encoder1,6,12,1);
						OLED_ShowNum(0,50,Encoder2,6,12,1);
						OLED_ShowNum(50,0,Encoder3,6,12,1);
						OLED_ShowNum(50,50,Encoder4,6,12,1);
						OLED_Refresh();	
						delay_ms(10);
					}
					break;
						
				case 6:   //����ѭ��ģ�����
					
					break;
				}
			}			
}
/* ��ʱ��6�жϷ������ */
  void TIM6_IRQHandler( void )                                                    /* TIM6�ж� */
	{
		
	 int t,len,tempQ,tempY;
		//xunji_show();
		if (TIM_GetITStatus(TIM6, TIM_IT_Update) != RESET) //���ָ����TIM�жϷ������:TIM �ж�Դ 
		{
			
			paral(zuo,you,Juli,Pinxin,Chuizhi,Xunxian); //Xunxian=1ʱ��������ƽ�й��ܣ�ֻ���������ƶ�
			
			//�����жϳ���
			if(qian < 50) tempQ = 1;
		  if(tempQ == 1 && qian > 100) {X++;tempQ = 0;}
		  if(tempQ == 1 && qian < -100) {X--;tempQ = 0;}
			if(you < 50) tempY = 1;
		  if(tempY == 1 && you > 100) {Y++;tempY = 0;}
		  if(tempY == 1 && you < -100) {Y--;tempY = 0;}
			
			AIM_1=(PS2_LY+PS2_LX+TURN)/128.0*AIM_max;
			AIM_2=(PS2_LY-PS2_LX-TURN)/128.0*AIM_max;
			AIM_3=(PS2_LY+PS2_LX-TURN)/128.0*AIM_max;
			AIM_4=(PS2_LY-PS2_LX+TURN)/128.0*AIM_max;
			
		
			if(USART5_RX_STA&0x8000) //����5ѭ�����ճ���
		{					   
			len=USART5_RX_STA&0x3fff;//�õ��˴ν��յ������ݳ���
		
			for(t=0;t<len;t++)
			{
				 YOU[t]=USART5_RX_BUF[t];				
			}
			YOU[t+1]='\0';
			USART5_RX_STA=0;
			you =atoi(YOU);//����ȡ�����ַ�������ת��Ϊ��������
		}
		
		//����4ѭ�����ճ���
		if(USART4_RX_STA&0x8000)//���Է��ڶ�ʱ���ж���ִ��
		{
			len=USART4_RX_STA&0x3fff;//�õ��˴ν��յ������ݳ���
		
			for(t=0;t<len;t++)
			{
				 ZUO[t]=USART4_RX_BUF[t];				
			}
			ZUO[t+1]='\0';
			USART4_RX_STA=0;
		  zuo = atoi(ZUO);//����ȡ�����ַ�������ת��Ϊ��������
		}
		
		if(USART3_RX_STA&0x8000)//���Է��ڶ�ʱ���ж���ִ��
		{
			len=USART3_RX_STA&0x3fff;//�õ��˴ν��յ������ݳ���
		
			for(t=0;t<len;t++)
			{
				 QIAN[t]=USART3_RX_BUF[t];				
			}
			QIAN[t+1]='\0';
			USART3_RX_STA=0;
		  qian = atoi(QIAN);//����ȡ�����ַ�������ת��Ϊ��������
		}

		
			Encoder1=-Read_Encoder(1);
			Encoder2= Read_Encoder(3);
			Encoder3= Read_Encoder(5);
			Encoder4=-Read_Encoder(4);
			 
			
      pwm1=Incremental_PI_A (Encoder1,AIM_1);
			pwm2=Incremental_PI_B (Encoder2,AIM_2);
			pwm3=Incremental_PI_C (Encoder3,AIM_3);
			pwm4=Incremental_PI_D (Encoder4,AIM_4);
			
		
			 Set_Pwm(1,pwm1) ;
			 Set_Pwm(2,pwm2) ;
			 Set_Pwm(3,pwm3) ;
			 Set_Pwm(4,pwm4) ;
			
			 
		}
		
		TIM_ClearITPendingBit( TIM6, TIM_IT_Update );                   /* ���TIMx���жϴ�����λ:TIM �ж�Դ */
		LED1 = !LED1;
	}


/* ��ʱ��7�жϷ������ */
void TIM7_IRQHandler( void )                                                    /* TIM7�ж� */
{
	if ( TIM_GetITStatus( TIM7, TIM_IT_Update ) != RESET )                  /* ���ָ����TIM�жϷ������:TIM �ж�Դ */
	{
	
		TIM_ClearITPendingBit( TIM7, TIM_IT_Update );                   /* ���TIMx���жϴ�����λ:TIM �ж�Դ */
		LED1 = !LED1;
	}
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


/* ��ʱ��2�жϷ������ */
//void TIM2_IRQHandler( void )
//{
//	if ( TIM_GetITStatus( TIM2, TIM_IT_Update ) != RESET )  /* ���TIM2�����жϷ������ */
//	{
//		TIM_ClearITPendingBit( TIM2, TIM_IT_Update );   /* ���TIMx�����жϱ�־ */

//		/* LED0 = !LED0; */

//		Bias			= Goal_value - angle_dangqian;
//		Delta_Bias		= Bias - Last_Bias;
//		Delta_Delta_Bias	= Delta_Bias - Pre_Delta_Bias;
//		balance = balance+Balance_KP*Delta_Bias+Balance_Ki*Bias+Balance_KD*Delta_Delta_Bias; 
//		
//		
////		if ( Bias > 13 )
////			alpha = 2.0f;
////		else
////			alpha = 1.0f;
//		//balance = balance + Balance_KP * Delta_Bias + alpha * Balance_Ki * Bias + Balance_KD * Delta_Delta_Bias;
//		
//		
//		Last_Bias	= Bias;
//		Pre_Delta_Bias	= Delta_Bias;

//		if ( balance > 4800 )
//			balance = 4800;                         /* limit the pwm value */
//		else if ( balance < 0 )
//			balance = 0;

//		TIM_SetCompare2( TIM3, balance );               /* set pwm value  */
//		
//		
//		
//		
//	}
//}


///* ��ʱ��4�жϷ������ */
//void TIM4_IRQHandler( void )                                    /* TIM4�ж� */
//{
//	if ( TIM_GetITStatus( TIM4, TIM_IT_Update ) != RESET )  /* ���TIM4�����жϷ������ */
//	{
//		TIM_ClearITPendingBit( TIM4, TIM_IT_Update );   /* ���TIMx�����жϱ�־ */

//		/* LED1 = !LED1; */
//	}
//}


///* ��ʱ��5�жϷ������ */
//void TIM5_IRQHandler( void )
//{
//	if ( TIM_GetITStatus( TIM5, TIM_IT_Update ) != RESET )  /* ���TIM5�����жϷ������ */
//	{
//		TIM_ClearITPendingBit( TIM5, TIM_IT_Update );   /* ���TIMx�����жϱ�־ */


//		LED1 = !LED1;
//	}
//}


