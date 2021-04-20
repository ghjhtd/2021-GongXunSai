


#include "sys.h"
#include "vl53l0x.h"
#include "24cxx.h" 
#include "oled.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*����      �ĸ����� */
u8 key = 0, problem = 0;

//int PS2_LX,PS2_LY,PS2_RX,PS2_RY,PS2_KEY;
/* ������ʾ */
char OLED_sprintf_str[20];
int CGQ[8],go=1;
int mode=0,step=0,flag,go_flag=0;
/* -------------PID Para */
float	Bias		= 0;
float	Last_Bias	= 0, Delta_Bias = 0, Delta_Delta_Bias = 0, Pre_Delta_Bias = 0;
int	balance		= 0.0;
/* 10 5  1 */
int RC_Velocity=10,A_AIM,B_AIM,C_AIM,D_AIM,X_AIM,Y_AIM,L_AIM,R_AIM;
int Encoder_A,Encoder_B,Encoder_C,Encoder_D;   
float	Position_KP,Position_KI,Position_KD;
float Velocity_KP=10,Velocity_KI=20;
float Goal_value=0;//��Ҫ��Ŀ��Ƕ�
float angle_dangqian=0.0;//��ǰ���ĽǶ�
int num[8],num_cnt,cishu_flag;
extern vu16 Distance_data;
int send_flag=0,color,color_num=3,COLOR[3];
int x,PWMA,PWMB,PWMC,PWMD;
	int step_flag=0;
int main( void )
{
	u8 problem_temp = 0;                                    /* ��ʱ���� K1�޸� K0ȷ����ֵ��ȫ��problem */
  cishu_flag=0;
	
  Stm32_Clock_Init(9);                           //ϵͳʱ��72M
	delay_init(72);	                              //��ʱ��ʼ��
	NVIC_PriorityGroupConfig( NVIC_PriorityGroup_2 );       /* ����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ� */
	uart1_init( 115200 );     //�����ͨѶ                                /* ���ڳ�ʼ��Ϊ115200 */
  uart2_init(115200);  //openmv
	//uart3_init(115200);  //˫��ͨѶ
	 CGQ_Init();
	
	Motor_Init();
  exti_init();  //GPIOA_4
	TIM2_PWM_Init( 7199,199); //GPIOB GPIO_Pin_10  50hz,20ms
	TIM8_PWM_Init( 7199, 9 ); //GPIOC GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;
	LED_Init();                                             /* LED�˿ڳ�ʼ�� */
	KEY_Init();                                             /* key init */
  TIM_SetCompare3( TIM2, 540); 
	OLED_Init();
 
	                 //=====��ʱ�ȴ���ʼ���ȶ�
							//=====ps2���ó�ʼ��,���á����̵�ģʽ������ѡ���Ƿ�����޸�
	delay_ms(1000);

	LED0	= 0;
	LED1	= 0;
 
	OLED_Clear();
	OLED_ShowString( 0, 0, "NCEPU", 40 );     /* 6*12 ��ABC�� */
	
	OLED_Refresh();
	delay_ms( 500 );
	//OLED_Clear();
	
 // TIM6_Int_Init( 49, 7199 ); 
	
 
	OLED_Refresh();
	Encoder_Init_TIM1();              //ZUOQIAN  e9,11   //���ֱ�����
   Encoder_Init_TIM3();              //YOUQIAN  a6,7
   Encoder_Init_TIM5();              //ZUOHOU    a0,1
   Encoder_Init_TIM4();              //YOUHOU   b6��7
	/* PWM */
	//GPIO_SetBits(GPIOC,GPIO_Pin_0); //��ǰ c0,1
	//GPIO_SetBits(GPIOE,GPIO_Pin_6); //��ǰ e6,7
 //GPIO_SetBits(GPIOB,GPIO_Pin_0);	//���	b0,1
 //GPIO_SetBits(GPIOE,GPIO_Pin_0); // �Һ� e0.1

	
	
	
              /* PWMƵ��=72000000/7200=10Khz */
    // TIM_SetCompare1( TIM8, 500 );           //����pwm��ǰ c6
		//TIM_SetCompare4( TIM8, 500 );            //��ǰ              9
   //	TIM_SetCompare2( TIM8, 500 );           //���           7
	//TIM_SetCompare3( TIM8, 500 );            //�Һ�          8



//	/* ��ʱ���ж� */
//	TIM1_Int_Init( 4900, 7199 );
	   /* 10Khz�ļ���Ƶ�ʣ�������49Ϊ5ms */
//	TIM7_Int_Init( 4999, 7199 );    /* 10Khz�ļ���Ƶ�ʣ�������49 is 5ms */


	while ( 1 )
	{
	 key=KEY_Scan(0);
		
		if ( key == 1 )
		{
			/* K1 ��Ŀ�޸� */
			USART_SendData(USART2, 'q');
				LED0 = !LED0;
			TIM6_Int_Init( 49, 7199 ); 	
			TIM7_Int_Init( 99, 7199 );
			
	
	}
	
  


	
//		VL53L0X_GetRangingMeasurementData(&vl53l0x_dev,&RangingMeasurementData);
	 lcd_show();
	//printf("%d%d%d%d%d%d%d\n",CGQ[0],CGQ[1],CGQ[2],CGQ[3],CGQ[4],CGQ[5],CGQ[6]);
		
	delay_ms(100);


}
}
///* ��ʱ��5�жϷ������ */


/* ��ʱ��6�жϷ������ */
void TIM6_IRQHandler( void )                                                    /* TIM6�ж� */
{
	
	if ( TIM_GetITStatus( TIM6, TIM_IT_Update ) != RESET )                  /* ���ָ����TIM�жϷ������:TIM �ж�Դ */
	{
	
	 Read_CGQ();
	//	printf("%d%d%d%d%d%d%d\n",CGQ[0],CGQ[1],CGQ[2],CGQ[3],CGQ[4],CGQ[5],CGQ[6]);
////		
//			X_AIM=0;
//			
//		  Y_AIM=6;
//     if(CGQ[0]==1&&CGQ[1]==0)
//			 R_AIM=3;
//			if(CGQ[0]==0&&CGQ[1]==1)
//			 R_AIM=-3;
//			if(CGQ[0]==0&&CGQ[1]==0)
//			 R_AIM=0;
		   //R_AIM=(PS2_LX-128)/128.0*36.0		;
	
   
		
		
			
			
		    A_AIM=Y_AIM-X_AIM-R_AIM; //1
			  B_AIM=Y_AIM+X_AIM+R_AIM; //2 
			  D_AIM=Y_AIM+X_AIM-R_AIM;//3
			  C_AIM=Y_AIM-X_AIM+R_AIM; //4
			
			if(A_AIM<2&&A_AIM>-2)
				A_AIM=0;
			if(B_AIM<2&&B_AIM>-2)
				B_AIM=0;
			if(C_AIM<2&&C_AIM>-2)
				C_AIM=0;
			if(D_AIM<2&&D_AIM>-2)
				D_AIM=0;
			
		Encoder_A=Read_Encoder(1);                                         		 //===��ȡ��������ֵ
			                                                //===���ֵõ��ٶ�   
		Encoder_B=Read_Encoder(3);                                         		 //===��ȡ��������ֵ
			                                                //===���ֵõ��ٶ�   
		Encoder_C=Read_Encoder(4);                                         		//===��ȡ��������ֵ
			                                            //===���ֵõ��ٶ�   
		Encoder_D=Read_Encoder(5);   

     PWMA=Incremental_PI_A ( Encoder_A,A_AIM);		
		 PWMB=Incremental_PI_B ( Encoder_B,B_AIM);	
		 PWMC=Incremental_PI_C ( Encoder_C,C_AIM);	
		 PWMD=Incremental_PI_D ( Encoder_D,D_AIM);	
		if(PWMA>0)
		{
			 GPIO_SetBits(GPIOC,GPIO_Pin_0);
			 GPIO_ResetBits(GPIOC,GPIO_Pin_1);
			 TIM_SetCompare1( TIM8, PWMA );
		}
		else
		{
			GPIO_SetBits(GPIOC,GPIO_Pin_1);
			 GPIO_ResetBits(GPIOC,GPIO_Pin_0);
			 TIM_SetCompare1( TIM8, -PWMA );
		}
		if(PWMB>0)
		{
			 GPIO_SetBits(GPIOE,GPIO_Pin_6);
			 GPIO_ResetBits(GPIOE,GPIO_Pin_7);
			 TIM_SetCompare4( TIM8, PWMB );
		}
		else
		{
			GPIO_SetBits(GPIOE,GPIO_Pin_7);
			 GPIO_ResetBits(GPIOE,GPIO_Pin_6);
			 TIM_SetCompare4( TIM8, -PWMB );
		}
		if(PWMC>0)
		{
			 GPIO_SetBits(GPIOB,GPIO_Pin_0);
			 GPIO_ResetBits(GPIOB,GPIO_Pin_1);
			 TIM_SetCompare3( TIM8, PWMC );
		}
		else
		{
			GPIO_SetBits(GPIOB,GPIO_Pin_1);
			 GPIO_ResetBits(GPIOB,GPIO_Pin_0);
			 TIM_SetCompare3( TIM8, -PWMC );
		}
			if(PWMD>0)
		{
			 GPIO_SetBits(GPIOE,GPIO_Pin_0);
			 GPIO_ResetBits(GPIOE,GPIO_Pin_1);
			 TIM_SetCompare2( TIM8, PWMD );
		}
		else
		{
			GPIO_SetBits(GPIOE,GPIO_Pin_1);
			 GPIO_ResetBits(GPIOE,GPIO_Pin_0);
			 TIM_SetCompare2( TIM8, -PWMD );
		}
		 
		TIM_ClearITPendingBit( TIM6, TIM_IT_Update );                   /* ���TIMx���жϴ�����λ:TIM �ж�Դ */
		LED1 = !LED1;
	}
}

/* ��ʱ��7�жϷ������ */
void TIM7_IRQHandler( void )                                                    /* TIM7�ж� */
{

	if ( TIM_GetITStatus( TIM7, TIM_IT_Update ) != RESET )                  /* ���ָ����TIM�жϷ������:TIM �ж�Դ */
	{
		switch(mode)
		{
			case 0:      //��ʼ ����
				X_AIM=0;
		    Y_AIM=-6;
     if(CGQ[5]==1)
		 {
			 step=0;
			 mode=1;
		 }
			break;
			case 1:    //���� 
			X_AIM=6;
			Y_AIM=0;
     if(CGQ[2]==1&&CGQ[5]==1&&CGQ[3]==0)
			 R_AIM=2;
			if(CGQ[3]==1&&CGQ[5]==1&&CGQ[2]==0)
			 R_AIM=-2;
			if((CGQ[2]==0&&CGQ[5]==0&&CGQ[3]==0)||(CGQ[2]==1&&CGQ[5]==1&&CGQ[3]==1))
			 R_AIM=0;
			STEP(2);
			
			if(step==6)
			{
				mode=2;
				step=0;
				 R_AIM=0;
				 X_AIM=0;
				 Y_AIM=0;
			
					while(num[0]==0) ;//ɨ��
				
				 X_AIM=4;
				 
				
				delay_ms(300);
				delay_ms(300);
				delay_ms(300);
		
			}
			break;       
			case 2:       // ����
			X_AIM=-6;
			Y_AIM=0;
     if(CGQ[6]==1&&CGQ[4]==0)
		 {R_AIM=2;
			}
			if(CGQ[6]==0&&CGQ[4]==1)
			{ R_AIM=-2;
			// Y_AIM=2;
			}
			if((CGQ[6]==0&&CGQ[4]==0)||(CGQ[6]==1&&CGQ[4]==1))
			 R_AIM=0;
			STEP(2);
			if(step>=2&&CGQ[1]==1)
			{
				mode=3;
				step=0;
				delay_ms(100);
			}	
			break;
			case 3:         //���������
							X_AIM=0;
				      Y_AIM=-4;
      if(CGQ[0]==1&&CGQ[1]==0)
			{
				 X_AIM=2;
			  R_AIM=-2;}
			
			if(CGQ[0]==0&&CGQ[1]==1)
			{
				 X_AIM=-2;
			R_AIM=2;}
			if(CGQ[0]==0&&CGQ[1]==0)
			 R_AIM=0;
				if(CGQ[0]==1&&CGQ[1]==1)
				{ R_AIM=0;
					Y_AIM=0;
				  mode=4;}
						break;
					
				case 4:           //������
						X_AIM=0;
				    Y_AIM=0;
				    R_AIM=0;
				    color_num=1;
			
				USART_SendData(USART2, 'c');
			
				
				
				TIM_SetCompare3( TIM2, 640 );
				delay_ms(250);
				
					delay_ms(250);
				color_num=0;
				USART_SendData(USART2, 'c');
				while(color_num!=3);
				
				TIM_SetCompare3( TIM2, 440 );
				delay_ms(250);
				
				delay_ms(250);
				color_num=2;
				USART_SendData(USART2, 'c');
				while(color_num!=3);
						
        
				TIM_SetCompare3( TIM2, 540 );
				mode=5;
				delay_ms(250);
				
			break;
			case 5:            //�ö���
						X_AIM=0;
				  Y_AIM=0;
				R_AIM=0;
			color_num=3;
				if(num[cishu_flag+1]==COLOR[1])
					TIM_SetCompare3( TIM2, 540 );
				if(num[cishu_flag+1]==COLOR[0])
					TIM_SetCompare3( TIM2, 640 );
				if(num[cishu_flag+1]==COLOR[2])
					TIM_SetCompare3( TIM2, 440 );
						if(send_flag==0)
			{
				if(num[cishu_flag+1]==COLOR[1])
				USART_SendData(USART1, 1);
				if(num[cishu_flag+1]==COLOR[0]||num[cishu_flag+1]==COLOR[2])
					USART_SendData(USART1, 3);
				send_flag=1;
			step=0;
			}
			break;
				case 6:    //ץ���� ����
					send_flag=0;
					X_AIM=0;
				  Y_AIM=-10;
      if(CGQ[0]==1&&CGQ[1]==0)
			{
				 X_AIM=2;
			  R_AIM=-2;}
			
			if(CGQ[0]==0&&CGQ[1]==1)
			{
				 X_AIM=-2;
			   R_AIM=2;
			}
			if(CGQ[0]==0&&CGQ[1]==0)
			     R_AIM=0;
					STEP(4);
				if((step>=(4+2*(4-num[cishu_flag+1])))&&CGQ[4]==1)  
				{
					step=0;
					mode=7;
				}	
				break;
				case 7:   //��you ȥ��
				
				X_AIM=-7;
			Y_AIM=0;
     if(CGQ[6]==1&&CGQ[4]==0)
		 {R_AIM=1;
			}
			if(CGQ[6]==0&&CGQ[4]==1)
			{ R_AIM=-1;
			// Y_AIM=2;
			}
			if((CGQ[6]==0&&CGQ[4]==0)||(CGQ[6]==1&&CGQ[4]==1))
			 R_AIM=0;
		
			 
				if(CGQ[6]==1&&CGQ[4]==1)
				{
					if(CGQ[4]==1&&CGQ[6]==1&&step_flag==0)
					step++;
					step_flag=1;
				}
				else
				step_flag=0;
			
			if(step==3)
			{
				mode=8;
				step=0;
				X_AIM=0;
				  Y_AIM=0;
				TIM_SetCompare3( TIM2, 290 );
				delay_ms(300);
				delay_ms(300);
				delay_ms(300);
						USART_SendData(USART1, 2);
			}
				break;

				case 8:     	// ��
        	X_AIM=0;
				  Y_AIM=0;
					break; 
				case 9:	  //������ ��zuo
      X_AIM=7;
			Y_AIM=0;
     if(CGQ[2]==1&&CGQ[5]==1&&CGQ[3]==0)
			 R_AIM=2;
			if(CGQ[3]==1&&CGQ[5]==1&&CGQ[2]==0)
			 R_AIM=-2;
			if((CGQ[2]==0&&CGQ[5]==0&&CGQ[3]==0)||(CGQ[2]==1&&CGQ[5]==1&&CGQ[3]==1))
			 R_AIM=0;
			STEP(2);
			if(step==3)
			{
				mode=10;
				step=0;
				delay_ms(100);
			}	
					break; 
			case 10:	            //����
        	X_AIM=0;
				  Y_AIM=10;
      if(CGQ[0]==1&&CGQ[1]==0)
			{
				
			  R_AIM=2;}
			
			if(CGQ[0]==0&&CGQ[1]==1)
			{
				
			   R_AIM=-2;
			}
			if(CGQ[0]==0&&CGQ[1]==0)
			     R_AIM=0;
					STEP(1);
				if((step>(2*(4-num[cishu_flag+1])-2))&&CGQ[2]==1)
				{
					step=0;
					mode=11;
					cishu_flag++;
					TIM_SetCompare3( TIM2, 540 );
					delay_ms(300);
					delay_ms(300);
					delay_ms(300);
				}	
				if(cishu_flag==3)
					{
						cishu_flag=4;
						mode=13;
						//TIM_SetCompare3( TIM2, 540 );
					}
					break; 
			case 11:    //ȥ�� ����
			X_AIM=0;
				  Y_AIM=8;
      if(CGQ[0]==1&&CGQ[1]==0)
			{
				
			  R_AIM=3;}
			
			if(CGQ[0]==0&&CGQ[1]==1)
			{
				
			   R_AIM=-3;
			}
			if(CGQ[0]==0&&CGQ[1]==0)
			     R_AIM=0;
					STEP(1);
				if(step>=5&&CGQ[2]==1)
				{
					step=0;
					mode=12;
					
				}	
				break;
			case 12:       //���������
						X_AIM=0;
				  Y_AIM=-4;
      if(CGQ[0]==1&&CGQ[1]==0)
			{
				 X_AIM=2;
			  R_AIM=-2;}
			
			if(CGQ[0]==0&&CGQ[1]==1)
			{
				 X_AIM=-2;
			R_AIM=2;}
			if(CGQ[0]==0&&CGQ[1]==0)
			 R_AIM=0;
				if(CGQ[0]==1&&CGQ[1]==1)
				{ R_AIM=0;
					Y_AIM=0;
				  mode=5;}     //��ץ
						break;
			case 13: //��ʼת��
						X_AIM=0;
				  Y_AIM=-10;
      if(CGQ[0]==1&&CGQ[1]==0)
			{
				 X_AIM=2;
			  R_AIM=-2;}
			
			if(CGQ[0]==0&&CGQ[1]==1)
			{
				 X_AIM=-2;
			R_AIM=2;}
			if(CGQ[0]==0&&CGQ[1]==0)
			 R_AIM=0;
			STEP(4);
				if((step>=(2*(4-num[cishu_flag+1])))&&CGQ[4]==1)
				{ R_AIM=0;
					Y_AIM=0;
					step=0;
				  mode=14;}
						break;
			case 14:               ////��you
					X_AIM=-6;
			Y_AIM=0;
     if(CGQ[6]==1&&CGQ[4]==0)
		 {R_AIM=1;
			}
			if(CGQ[6]==0&&CGQ[4]==1)
			{ R_AIM=-1;
			// Y_AIM=2;
			}
			if((CGQ[6]==0&&CGQ[4]==0)||(CGQ[6]==1&&CGQ[4]==1))
			 R_AIM=0;
			 
				if(CGQ[4]==1&&CGQ[6]==1)
				{
					if(CGQ[4]==1&&CGQ[6]==1&&step_flag==0)
					step++;
					step_flag=1;
				}
				else
				step_flag=0;
			if(step==1&&go_flag==0)
			{	TIM_SetCompare3( TIM2, 290 );
			    USART_SendData(USART1, 6);
				go_flag=1;
			}

				if(step==3)
			{
				mode=15;
				step=0;
				X_AIM=0;
				  Y_AIM=0;
			
				delay_ms(300);
				delay_ms(300);
				delay_ms(300);
			//
				USART_SendData(USART1, 4); //ץ
				delay_ms(300);
				delay_ms(300);
				delay_ms(300);
					delay_ms(300);
				delay_ms(300);
					delay_ms(300);
			
			}
			
				break;
			case 15:	   //ץ����
				go_flag=0;
       
			
			 X_AIM=6;
			Y_AIM=0;
     if(CGQ[2]==1&&CGQ[5]==1&&CGQ[3]==0)
			 R_AIM=3;
			if(CGQ[3]==1&&CGQ[5]==1&&CGQ[2]==0)
			 R_AIM=-3;
			if((CGQ[2]==0&&CGQ[5]==0&&CGQ[3]==0)||(CGQ[2]==1&&CGQ[5]==1&&CGQ[3]==1))
			 R_AIM=0;
			STEP(2);
		
			if(step>2&&CGQ[0]==1)
			{
				mode=16;
				step=0;
				TIM_SetCompare3( TIM2, 540 );
				
			}	
					break; 
			case 16:
				
				if(num[cishu_flag+1]==3)  //���
				{			 X_AIM=0;
				       Y_AIM=-8;
              if(CGQ[0]==1&&CGQ[1]==0)
			        {
				        X_AIM=2;
			          R_AIM=-2;
							}
			
			       if(CGQ[0]==0&&CGQ[1]==1)
	             		{
		     		  X_AIM=-2;
		        	R_AIM=2;}
		      	if(CGQ[0]==0&&CGQ[1]==0)
			      R_AIM=0;
							STEP(3);
				    if((step>4)&&CGQ[3]==1)
				    { R_AIM=0;
					    Y_AIM=0;
							step=0;
				      mode=17;}
			      	}
				if(num[cishu_flag+1]==2)
				{
					mode=17;
				}
				if(num[cishu_flag+1]==1) //��ǰ
			    	{
					X_AIM=0;
				  Y_AIM=8;
          if(CGQ[0]==1&&CGQ[1]==0)
		    	{
				
			    R_AIM=1;}
			
			if(CGQ[0]==0&&CGQ[1]==1)
			{
				
			   R_AIM=-1;
			}
			if(CGQ[0]==0&&CGQ[1]==0)
			     R_AIM=0;
					STEP(1);
				if(step>4&&CGQ[2]==1)
				{
					step=0;
					mode=17;
					
				}	
				}
			    break;
				
				//
			case 17:   //��zuo ȥ��
				 X_AIM=6;
			Y_AIM=0;
     if(CGQ[2]==1&&CGQ[5]==1&&CGQ[3]==0)
			 R_AIM=3;
			if(CGQ[3]==1&&CGQ[5]==1&&CGQ[2]==0)
			 R_AIM=-3;
			if((CGQ[2]==0&&CGQ[5]==0&&CGQ[3]==0)||(CGQ[2]==1&&CGQ[5]==1&&CGQ[3]==1))
			 R_AIM=0;
		if(CGQ[2]==1&&CGQ[5]==1&&CGQ[3]==1)
				{
					if(CGQ[2]==1&&CGQ[5]==1&&CGQ[3]==1&&step_flag==0)
					step++;
					step_flag=1;
				}
				else
				step_flag=0;
				if(step>=2)
					 X_AIM=4;
			if(step>=3)
			{
				 X_AIM=0;
			  Y_AIM=0;
				 R_AIM=0;
				mode=18;
				step=0;
		
					TIM_SetCompare3( TIM2, 810 );
				delay_ms(300);
				delay_ms(300);
				delay_ms(300);
						USART_SendData(USART1, 5);
				cishu_flag++;
			}	
				break;
			case 18:  //fang
					X_AIM=0;
				  Y_AIM=0;
					break; 
			case 19:   //��you
				if(cishu_flag==7)
					mode=21;
				else
					{
			X_AIM=-6;
			Y_AIM=0;
     if(CGQ[6]==1&&CGQ[4]==0)
		 {R_AIM=1;
			}
			if(CGQ[6]==0&&CGQ[4]==1)
			{ R_AIM=-1;
			// Y_AIM=2;
			}
			if((CGQ[6]==0&&CGQ[4]==0)||(CGQ[6]==1&&CGQ[4]==1))
			 R_AIM=0;
			 
				if(CGQ[4]==1&&CGQ[6]==1)
				{
					if(CGQ[4]==1&&CGQ[6]==1&&step_flag==0)
					step++;
					step_flag=1;
				}
				else
				step_flag=0;
			
			if(step>=3&&CGQ[1]==1)
			{
				mode=20;
				step=0;
				X_AIM=0;
				  Y_AIM=0;
				
			}
					}
			break;
			case 20: //��ǰ
				  X_AIM=0;
				  Y_AIM=8;
      if(CGQ[0]==1&&CGQ[1]==0)
			{
			  R_AIM=2;
			}
			
			if(CGQ[0]==0&&CGQ[1]==1)
			{
			   R_AIM=-2;
			}
			if(CGQ[0]==0&&CGQ[1]==0)
			     R_AIM=0;
					STEP(1);
				if((step>2*(num[cishu_flag]-1))&&CGQ[2]==1)
				{
					step=0;
					
					if(cishu_flag<7)
					{mode=13;
						Y_AIM=5;}
					else
						mode=21;
					delay_ms(300);
					delay_ms(300);
					delay_ms(300);
						TIM_SetCompare3( TIM2, 540 );
				}	
				break;
			case 21:
			  	X_AIM=-6;
			Y_AIM=0;
     if(CGQ[6]==1&&CGQ[4]==0)
		 {R_AIM=1;
			}
			if(CGQ[6]==0&&CGQ[4]==1)
			{ R_AIM=-1;
			// Y_AIM=2;
			}
			if((CGQ[6]==0&&CGQ[4]==0)||(CGQ[6]==1&&CGQ[4]==1))
			 R_AIM=0;
			 
				if(CGQ[4]==1&&CGQ[6]==1)
				{
					if(CGQ[4]==1&&CGQ[6]==1&&step_flag==0)
					step++;
					step_flag=1;
				}
				else
				step_flag=0;
			
			if(step>=5&&CGQ[1]==1)
			{
				mode=22;
					TIM_SetCompare3( TIM2, 540 );
				step=0;
				X_AIM=0;
				  Y_AIM=0;
				
			}
			break;
			case 22:
				 X_AIM=0;
				  Y_AIM=10;
      if(CGQ[0]==1&&CGQ[1]==0)
			{
			  R_AIM=2;
			}
			
			if(CGQ[0]==0&&CGQ[1]==1)
			{
			   R_AIM=-2;
			}
			if(CGQ[0]==0&&CGQ[1]==0)
			     R_AIM=0;
					STEP(4);
				if((step>=5+2*num[7])&&CGQ[2]==1)
				{
					step=0;
						mode=23;	
				}	
				break;
			case 23:
				 X_AIM=-6;
			  Y_AIM=0;
     if(CGQ[6]==1&&CGQ[4]==0)
		 {R_AIM=1;
			}
			if(CGQ[6]==0&&CGQ[4]==1)
			{ R_AIM=-1;
			// Y_AIM=2;
			}
			if((CGQ[6]==0&&CGQ[4]==0)||(CGQ[6]==1&&CGQ[4]==1))
			 R_AIM=0;
			STEP(2);
			if((step>=2)&&CGQ[2]==1&&CGQ[5]==1&&CGQ[3]==1)
			{
				mode=24;
				step=0;
		
					
				delay_ms(280);
			
				
				
			}	
			break;
			case 24:
				 X_AIM=0;
			  Y_AIM=4;
     
				mode=25;
				step=0;
		
					
				delay_ms(300);
				delay_ms(300);
				delay_ms(300);
				delay_ms(200);
					delay_ms(200);
				
			
				break;
			
			case 25:
				 Y_AIM=0;
			   R_AIM=0;
			   X_AIM=0;
			break;
//			x=380;
//			flag=0;
//			while(1)
//			{
//				 TIM_SetCompare3( TIM2, x );
//				if(flag==0)
//					x+=20;
//				else
//					x-=20;
//				if(x>700)
//					flag=1;
//				if(x<380)
//					flag=0;
//				
//				delay_ms(200);
//				
//			}
			
		   //R_AIM=(PS2_LX-128)/128.0*36.0		;
				
		}
	
		 
		TIM_ClearITPendingBit( TIM7, TIM_IT_Update );                   /* ���TIMx���жϴ�����λ:TIM �ж�Դ */
		LED1 = !LED1;
	}
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


