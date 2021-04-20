#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"
#include "timer.h"
#include "oled.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*按键      哪个问题 */
u8 key = 0, problem = 0;

/* 数组显示 */
char OLED_sprintf_str[20];

int usart_flag=1,usart_flag2;
/* -------------PID Para */
float	Bias		= 0;
float	Last_Bias	= 0, Delta_Bias = 0, Delta_Delta_Bias = 0, Pre_Delta_Bias = 0;

/* 10 5  1 */
float	Balance_KP		= 3.5, Balance_Ki = 0.3, Balance_KD = 10.0;
int KL,angle_1_flag,ii,iii=0,iiii;           //距离比例
float Goal_value=0;//想要的目标角度
float angle_1=0.0,angle_2=30,angle_3;//当前检测的角度
u8 RX_BUF[15],RX_CNT;  //摄像头串口通讯坐标存储
int x,y,r,length,biaoju,baju,yaim=80,ii;
int PWMA,PWMB,PWMC;

float pitch,roll,yaw; 
int mode=0;

int main( void )
{
	u8 problem_temp = 0;                                    /* 临时变量 K1修改 K0确定后赋值给全局problem */

  Stm32_Clock_Init(9);                           //系统时钟72M
	delay_init(72);	                              //延时初始化
	NVIC_PriorityGroupConfig( NVIC_PriorityGroup_2 );       /* 设置NVIC中断分组2:2位抢占优先级，2位响应优先级 */
 	uart_init( 72,115200 );                                    /* 串口初始化为115200 */

    uart3_init(115200);
	
	
	LED_Init();                                             /* LED端口初始化 */
	KEY_Init();                                             /* key init */

  

	
	
	




//  OLED_ShowString(0,12,"y 00",12);        //
//	OLED_ShowString(0,24,"r 00",12);
//	OLED_ShowString(30,12,"a000 PA0000",12);
//	OLED_ShowString(30,24,"A000 PB0000",12);
//	OLED_ShowString(0,36,"AGL000",12);
//	OLED_ShowString(0,48,"P00 I000 D000",12);
	//OLED_Refresh();
	/* PWM */
	TIM3_PWM_Init( 7199, 199 );  
	TIM2_PWM_Init( 7199, 199 );  	/* PWM频率=72000000/16000=4.5Khz */
//	TIM_SetCompare2( TIM2, 500 );       //c6789    //四轮pwm
//	TIM_SetCompare3( TIM3, 540 );
//	TIM_SetCompare4( TIM3, 540 );
////	TIM_SetCompare4( TIM8, 540 );
//	TIM_SetCompare2( TIM3, 400	);
//  TIM_SetCompare1( TIM3, 800 );      //a6
	/* 定时器中断 */
	//TIM1_Int_Init( 4900, 7199 );
	//TIM6_Int_Init( 4999, 7199 );    /* 10Khz的计数频率，计数到49为5ms */
	//TIM7_Int_Init( 499, 7199 );    /* 10Khz的计数频率，计数到49 is 5ms */
 
 		delay_ms(500);
		OLED_Clear();
	while ( 1 )
	{
	  switch (mode)
		{
			case 0:
//		   TIM_SetCompare2( TIM2,580 );
		
				TIM_SetCompare1( TIM3,800);       //400、、、、c6789    //四轮pwm
        TIM_SetCompare2( TIM3, 400 );
	      TIM_SetCompare3( TIM3, 600 );
	      TIM_SetCompare4( TIM3, 350 );
        TIM_SetCompare2( TIM2, 580 ); 
       break;			
			case 1:
				  	TIM_SetCompare2( TIM2,360 );
				TIM_SetCompare1( TIM3, 		560 );
			TIM_SetCompare2( TIM3, 400 );
		
	      TIM_SetCompare3( TIM3, 480 );
	      TIM_SetCompare4( TIM3, 320 );
					//c6789    //四轮pwm
      	//TIM_SetCompare2( TIM8,540			);
	     // TIM_SetCompare3( TIM8, 450 );
			delay_ms(500);
			
							TIM_SetCompare1( TIM3, 		520 );
			TIM_SetCompare2( TIM3, 420 );
				 TIM_SetCompare3( TIM3, 310 );
			  TIM_SetCompare4( TIM3, 400 );
			
			
			delay_ms(500);
			  
			   TIM_SetCompare2( TIM2,580 );
				delay_ms(500);
//		   	TIM_SetCompare2( TIM3, 400 );
//		
//	      TIM_SetCompare3( TIM3, 500 );
//	      TIM_SetCompare4( TIM3, 350 );
		
   
	
//       delay_ms(200);
//			delay_ms(200);
//			delay_ms(200);
//				TIM_SetCompare2( TIM2,580 );
//			delay_ms(200);
//			 TIM_SetCompare3( TIM3, 540 );
    USART_SendData(USART3, 1);
	   mode=0;
			break;
			case 2:	

					
				
			  
			TIM_SetCompare4( TIM3, 430 );
				TIM_SetCompare2( TIM3, 540 );
					TIM_SetCompare1( TIM3, 		600 );
				TIM_SetCompare2( TIM2,590 ); 
			TIM_SetCompare3( TIM3, 280 );
			 delay_ms(500);
			ii=600;
			while(ii>380)
			{
				ii-=20;
				TIM_SetCompare1( TIM3, ii );
				delay_ms(150);
			}
				 		TIM_SetCompare4( TIM3, 430 );
		  delay_ms(500);
			TIM_SetCompare2( TIM2,360 );
			delay_ms(500);
			    USART_SendData(USART3, 2);
				 delay_ms(500);
					delay_ms(500);
			mode=0;
					//c6789    //四轮pwm
      	//TIM_SetCompare2( TIM8,540			);
	     // TIM_SetCompare3( TIM8, 450 );
			break;
			case 3:
			  TIM_SetCompare1( TIM3, 540 );
		  	TIM_SetCompare3( TIM3, 340 );
			  TIM_SetCompare4( TIM3, 420 );
			  TIM_SetCompare2( TIM2, 360 );
			  TIM_SetCompare2( TIM3, 440 );
					//c6789    //四轮pwm
      	//TIM_SetCompare2( TIM8,540			);
	     // TIM_SetCompare3( TIM8, 450 );
			delay_ms(500);
			delay_ms(500);
			TIM_SetCompare1( TIM3, 480 );
		  	TIM_SetCompare3( TIM3, 280 );
			  TIM_SetCompare4( TIM3, 420 );
			  TIM_SetCompare2( TIM2, 580 );
			  TIM_SetCompare2( TIM3, 480 );
				delay_ms(500);
//		   	TIM_SetCompare2( TIM3, 400 );
//		
//	      TIM_SetCompare3( TIM3, 500 );
//	      TIM_SetCompare4( TIM3, 350 );
		
   
	
//       delay_ms(200);
//			delay_ms(200);
//			delay_ms(200);
//				TIM_SetCompare2( TIM2,580 );
//			delay_ms(200);
//			 TIM_SetCompare3( TIM3, 540 );
    USART_SendData(USART3, 1);
	 mode=0;
		 break;
				
					case 4:
//				TIM_SetCompare2( TIM2,360 );
//			
//				TIM_SetCompare1( TIM3, 		400 );
//			TIM_SetCompare2( TIM3, 540 );
//		
//	      TIM_SetCompare3( TIM3, 380 );
//	     delay_ms(500);
		
				TIM_SetCompare1( TIM3, 		380 );
			TIM_SetCompare2( TIM3, 540 );
	      TIM_SetCompare3( TIM3, 250 );
				TIM_SetCompare4( TIM3, 460 );
					
		
			delay_ms(500);
		
			TIM_SetCompare2( TIM2,580 );
			delay_ms(300);  
			delay_ms(300);
			delay_ms(300);
			delay_ms(300);
	delay_ms(300);
			delay_ms(300);			
					USART_SendData(USART3, 3);
			mode=0;
			
//		   	TIM_SetCompare2( TIM3, 400 );
//		
//	      TIM_SetCompare3( TIM3, 500 );
//	      TIM_SetCompare4( TIM3, 350 );
		
   
	
//       delay_ms(200);
//			delay_ms(200);
//			delay_ms(200);
//				TIM_SetCompare2( TIM2,580 );
//			delay_ms(200);
//			 TIM_SetCompare3( TIM3, 540 );
  
		 break;
		 	case 5:
			
				//TIM_SetCompare1( TIM3, 		280 );
		
	      TIM_SetCompare3( TIM3, 250 );
				TIM_SetCompare4( TIM3, 460 );
			
				TIM_SetCompare2( TIM2,580 );
				TIM_SetCompare1( TIM3, 		600 );
			TIM_SetCompare2( TIM3, 540 );
	      TIM_SetCompare3( TIM3, 250 );
			ii=600;
			while(ii>380)
			{
				ii-=20;
					TIM_SetCompare1( TIM3,ii);
				delay_ms(150);
			}
			
	
					
			 
			TIM_SetCompare4( TIM3, 460 );
			delay_ms(500);
		  delay_ms(500);
			TIM_SetCompare2( TIM2,360 );
			delay_ms(500);
			
			    USART_SendData(USART3, 4);
				 delay_ms(500);
					delay_ms(500);
			mode=0;
					//c6789    //四轮pwm
      	//TIM_SetCompare2( TIM8,540			);
	     // TIM_SetCompare3( TIM8, 450 );
			break;
			
					case 6:
				TIM_SetCompare2( TIM2,360 );
			
				TIM_SetCompare1( TIM3, 		450 );
			TIM_SetCompare2( TIM3, 540 );
		  
	      TIM_SetCompare3( TIM3, 380 );
	     delay_ms(500);
			 delay_ms(500);
					mode=7;
		break;
					case 7:
				TIM_SetCompare2( TIM2,360 );
			
				TIM_SetCompare1( TIM3, 		400 );
			TIM_SetCompare2( TIM3, 540 );
		  
	      TIM_SetCompare3( TIM3, 380 );
	     delay_ms(500);
					
		break;
//			  
//			
//			
////		   	TIM_SetCompare2( TIM3, 400 );
////		
////	      TIM_SetCompare3( TIM3, 500 );
////	      TIM_SetCompare4( TIM3, 350 );
//		
//   
//	
////       delay_ms(200);
////			delay_ms(200);
////			delay_ms(200);
////				TIM_SetCompare2( TIM2,580 );
////			delay_ms(200);
////			 TIM_SetCompare3( TIM3, 540 );
//  
//		 break;
		}
		delay_ms(300);
		}
	}
/* 定时器6中断服务程序 */
  void TIM6_IRQHandler( void )                                                    /* TIM6中断 */
	{
	if ( TIM_GetITStatus( TIM6, TIM_IT_Update ) != RESET )                  /* 检查指定的TIM中断发生与否:TIM 中断源 */
	{
		//lcd_show();
		if (TIM_GetITStatus(TIM6, TIM_IT_Update) != RESET) //检查指定的TIM中断发生与否:TIM 中断源 
		{
				
							 
			
		if(usart_flag2==usart_flag)
			{
				x=0;
				y=0;
				r=0;
			}
	
					OLED_ShowNum(0,48,x,3,12);
					
					OLED_ShowNum(24,48,r,4,12);
//			    usart_flag2=usart_flag;
	 //     angle_dangqian=pitch;
	       OLED_Refresh();
//			if(delay_flag==1)
//			 {
//				 if(++delay_50==10)	 delay_50=0,delay_flag=0;          //===给主函数提供50ms的精准延时
//			 }	
      

		}
		
		TIM_ClearITPendingBit( TIM6, TIM_IT_Update );                   /* 清除TIMx的中断待处理位:TIM 中断源 */
		LED1 = !LED1;
	}
}

/* 定时器7中断服务程序 */
void TIM7_IRQHandler( void )                                                    /* TIM7中断 */
{
	if ( TIM_GetITStatus( TIM7, TIM_IT_Update ) != RESET )                  /* 检查指定的TIM中断发生与否:TIM 中断源 */
	{
	//		PWM1= PositionX_PID ( y, yaim);
			 ///PWM2= PositionY_PID ( angle_dangqian,angle_aim);
			 
		//	mpu_dmp_get_data(&pitch,&roll,&yaw);
			angle_3=pitch;
			if(angle_3<0)
			{
				OLED_ShowString(18,36,"-",12);
					OLED_ShowNum(24,36,-pitch,2,12);
			}
			else
			{
				OLED_ShowString(18,36," ",12);
					OLED_ShowNum(24,36,pitch,2,12);
			}
							
		//	OLED_Refresh();
		//		TIM_SetCompare1(TIM3,PWMB);	
			//  TIM_SetCompare2(TIM3,750);	
	    
		TIM_ClearITPendingBit( TIM7, TIM_IT_Update );                   /* 清除TIMx的中断待处理位:TIM 中断源 */
		LED1 = !LED1;
	}
}
/* 定时器2中断服务程序 */
//void TIM2_IRQHandler( void )
//{
//	if ( TIM_GetITStatus( TIM2, TIM_IT_Update ) != RESET )  /* 检查TIM2更新中断发生与否 */
//	{
//		TIM_ClearITPendingBit( TIM2, TIM_IT_Update );   /* 清除TIMx更新中断标志 */

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


///* 定时器4中断服务程序 */
//void TIM4_IRQHandler( void )                                    /* TIM4中断 */
//{
//	if ( TIM_GetITStatus( TIM4, TIM_IT_Update ) != RESET )  /* 检查TIM4更新中断发生与否 */
//	{
//		TIM_ClearITPendingBit( TIM4, TIM_IT_Update );   /* 清除TIMx更新中断标志 */

//		/* LED1 = !LED1; */
//	}
//}


///* 定时器5中断服务程序 */
//void TIM5_IRQHandler( void )
//{
//	if ( TIM_GetITStatus( TIM5, TIM_IT_Update ) != RESET )  /* 检查TIM5更新中断发生与否 */
//	{
//		TIM_ClearITPendingBit( TIM5, TIM_IT_Update );   /* 清除TIMx更新中断标志 */


//		LED1 = !LED1;
//	}
//}


