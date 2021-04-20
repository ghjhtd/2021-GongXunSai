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


/*按键      哪个问题 */
int key = 0, program = 0;
u8 key_bsp = 0;
int Encoder1,Encoder2,Encoder3,Encoder4;

volatile u8 Adc_Key = 0;   //adc矩阵键盘键值
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
int x,y,r,length,biaoju,baju,yaim=80;
int pwm1,pwm2,pwm3,pwm4;
int a;
float pitch,roll,yaw; 
int Mode=0;
int AIM_1,AIM_2,AIM_3,AIM_4;//四轮速度目标值
int AIM_max=6.8;//速度挡位
int PS2_LX,PS2_LY,PS2_RX,PS2_RY,PS2_KEY,PS2_KEY2,TURN;
char YOU[30];
char ZUO[30];
char QIAN[30];
int sum;
u8 j;
float ADC_Value[3];//??????????????
u8 state,uart_show='0';
int servo_num=1, servo_angle;

int volatile qian,zuo,you,Xunxian,Pinxin,Juli,Chuizhi;  //  三个串口循迹模块量,与线固定距离,左右轮与线平行,与线距离,寻垂直的线
int X,Y;   //小车在地图上的定位坐标，地图左下角的坐标是0，0

int threshold = 211;   //巡线阈值
int bias,temp_Dot = 0,tempY1=0,temp_Turn=73,temp_Sudu,count_Jishu,count_Biaozhi,count_JishuY,count_BiaozhiY,temp_DotY = 0,tempY2=0,count_Tiaozheng=0;   //巡线参数
int num[8],num_cnt,cishu_flag;

//extern int GetTrackString2IntData(u8 *str);  //循迹模块数据转换函数
int xianFu_125(int x);
int Tiaozheng(int x,int state);
int clear(void);
void Send_data(USART_TypeDef * USARTx,u8 *s);
int main( void )
{
	u8 problem_temp = 0;                                    /* 临时变量 K1修改 K0确定后赋值给全局problem */
	int a;
  Stm32_Clock_Init(9);                           //系统时钟72M
	delay_init(72);	                              //延时初始化
	NVIC_PriorityGroupConfig( NVIC_PriorityGroup_2 );       /* 设置NVIC中断分组2:2位抢占优先级，2位响应优先级 */
  //PC3_Init();
	uart1_init(115200 );                                    /* 串口初始化为115200 */
  uart2_init(115200);
	
	delay_ms(100);
	PS2_Init();											//=====ps2驱动端口初始化
	
	
	Encoder_Init_TIM1();
	Encoder_Init_TIM3();
	Encoder_Init_TIM4();
	Encoder_Init_TIM5();
  
	Motor_Init();
	LED_Init();                                             /* LED端口初始化 */
	KEY_Init();                                             /* key init */
	OLED_Init();
	delay_ms(100);
	PS2_SetInit();		 							//=====ps2配置初始化,配置“红绿灯模式”，并选择是否可以修改

  //IIC_Init();

	PS2_Vibration(0X40,0);
	OLED_ShowString( 0, 12, "--NCEPU--", 16,1);    /* 8*16 “ABC” */
	OLED_ShowString( 0, 28, "CIE510", 24,1);    /* 12*24 “ABC” */
	OLED_Refresh();
	delay_ms(500);
  OLED_Clear();
	
  TIM8_PWM_Init( 7199, 9 );  	/* PWM频率=1k */
	
	
	uart3_init(115200);     //前循迹模块
	uart4_init(115200);     //左循迹模块
	uart5_init(115200);			//右循迹模块
	
	

//  OLED_ShowString(0,12,"y 00",12);        //
//	OLED_ShowString(0,24,"r 00",12);
//	OLED_ShowString(30,12,"a000 PA0000",12);
//	OLED_ShowString(30,24,"A000 PB0000",12);
//	OLED_ShowString(0,48,"P00 I000 D000",12);
	//OLED_Refresh();
	/* PWM */
	//TIM3_PWM_Init( 7199, 199 );  


	
	
//	TIM_SetCompare1( TIM8, 600 ); 	//c6789    //四轮pwm
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

	/* 定时器中断 */
	//TIM1_Int_Init( 4900, 7199 );
//	TIM6_Int_Init( 49, 7199 );    /* 10Khz的计数频率，计数到49为5ms */
	//TIM7_Int_Init( 499, 7199 );    /* 10Khz的计数频率，计数到49 is 50ms */
 
 		delay_ms(300);
		
		Adc_Init();     //ADC与DMA初始化
		DMA_ADC_Init();
		ADC_SoftwareStartConvCmd(ADC1, ENABLE);//ADC软件触发启动			

		printf("S%d%d\r\n",0, 0);
		delay_ms(300);
		printf("S%d%d\r\n",1, 80);
		delay_ms(300);
		printf("S%d%d\r\n",2, 8);
		delay_ms(300);
		printf("S%d%d\r\n",3, -30);
		delay_ms(300);
		printf("S%d%d\r\n",4, 0);
		delay_ms(300);
		PS2_Vibration(0,0X40)	 ;
		while(1)
		{
			OLED_ShowString( 0, 0, "Which Program?(1-6)", 12,1); 
			OLED_Refresh();		
			while(program==0||(key_bsp != 2 && key != 5 && PS2_KEY != 13))	
				{
					key = ADC_Key(ADCConvertedValue[0][2],0);
					PS2_KEY=PS2_Keyscan(0);
					key_bsp = KEY_Scan(0);
					if(key_bsp == 1 ||key == 2|| PS2_KEY == 1)
						{	
							program++;
							if(program>=7)
							program=1;		
						}	
					if(key == 1)
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
				case 1:  //采用手柄遥控
					TIM6_Int_Init( 49, 7199 );    //电机控制
				  PS2_Vibration(0,0X40)	 ;
		      while ( 1 )
		      	{	
		      		//xy_show();
              //xunji_show();
							usart_show();
		      		delay_ms(5);
							key = ADC_Key(ADCConvertedValue[0][2],0);
//		      		PS2_LX=127-PS2_AnologData(PSS_LX);    
//		      		PS2_LY=127-PS2_AnologData(PSS_LY);
//		      		PS2_RX=127-PS2_AnologData(PSS_RX);
//		      		PS2_RY=127-PS2_AnologData(PSS_RY);
//		      		if(PS2_LX==-128&&PS2_LY==-128&&PS2_RX==-128&&PS2_RY==-128)
//		      		PS2_LX=0,PS2_LY=0,PS2_RX=0,PS2_RY=0;
							key_bsp = KEY_Scan(0);
		      		PS2_KEY=PS2_Keyscan(1); //连按
							PS2_KEY2=PS2_Keyscan2(0);//不连按
		      		if(PS2_KEY==PSB_L2 )	
		      			{
		      				if(AIM_max==10)
		      				AIM_max=5;
		      				else
		      				AIM_max=10;	
		      			}		
//		      		if(PS2_KEY==PSB_R2)
//		      			PCout(3)=1;
//		      		else
//		      		PCout(3)=0;
		      		if(PS2_KEY==PSB_L1)
		      			TURN=128;
		      		else 
		      				if(PS2_KEY==PSB_R1)
		      					TURN=-128;
		      				else
		      					TURN=0;
							if(PS2_KEY2==PSB_RED|| key == 7)
							{
							  servo_angle=5;
								printf("M%d%d\r\n",0, servo_angle);
							}
							if(PS2_KEY2==PSB_PINK|| key == 8)
							{
								servo_angle=-5;
								printf("M%d%d\r\n",0, servo_angle);
							}
						
							if(PS2_KEY2==PSB_PAD_UP|| key == 1)
							{
								servo_num++; 
								if(servo_num>4)
									servo_num=4; 
								//printf("M%d%d\r\n",servo_num, 0);
								printf("M%d%d\r\n",servo_num, 0);
							}
							if(PS2_KEY2==PSB_PAD_DOWN|| key == 4)
							{
								servo_num--; 
								if(servo_num<1)
									servo_num=1; 
								printf("M%d%d\r\n",servo_num, 0);
							}
							
//							//pid Test*********************
//							if(PS2_KEY2==PSB_PAD_UP)
//							{
//								Velocity_KP++; 
//							}
//							if(PS2_KEY2==PSB_PAD_DOWN)
//							{
//								Velocity_KP--; 
//							}
//							if(PS2_KEY2==PSB_PAD_RIGHT)
//							{
//								Velocity_KI++; 
//							}
//							if(PS2_KEY2==PSB_PAD_LEFT)
//							{
//								Velocity_KI--;
//							}
//							//*****************************
							
							
							if(PS2_KEY2==PSB_BLUE|| key == 5)
							{
								servo_angle=-5;
								printf("M%d%d\r\n",servo_num, servo_angle);
							}
							if(PS2_KEY2==PSB_GREEN|| key == 2)
							{
								servo_angle=5;
								printf("M%d%d\r\n",servo_num, servo_angle);
							}
							if(PS2_KEY2==PSB_R2|| key == 3)
							{
								servo_angle=0;
								printf("S%d%d\r\n",4, servo_angle);
							}
							if(PS2_KEY2==PSB_L2|| key == 6)
							{
								servo_angle=35;
								printf("S%d%d\r\n",4, servo_angle);
								
							}
							
//		      		printf("%d     PS2_LX:",PS2_LX);
//		      		printf("%d     PS2_LY:",PS2_LY);
//		      		printf("%d     PS2_RX:",PS2_RX);
//		      		printf("%d     PS2_RY:",PS2_RY);
//		      		printf("%d \r\nPS2_KEY:",PS2_KEY);
          
		      		if(key_bsp == 1 )      //按键0返回主菜单|| PS2_Keyscan(1)==PSB_SELECT
		      			{	
		      				OLED_Clear();
		      				program=0;
		      				break;
		      			}
		      		}
					break;
							
				case 2:    //循迹调试
//					OLED_Clear();
//					OLED_ShowString(0, 0, "Press Key1 to start", 12,1);
//					OLED_ShowString(0, 16, "Press Key0 to return", 12,1); 
//					OLED_Refresh();
//						PS2_LX = 0;
//						PS2_LY = -80;
//						delay_ms(4000);
//						PS2_LX = 100;
//						PS2_LY = 0;
//						delay_ms(5000);
						Mode = 1;
						TIM6_Int_Init( 49, 7199 );    //电机控制
						TIM7_Int_Init( 99, 7199 );	
					while ( 1 )
						{
							xunji_show();
							delay_ms(100);						
							if(key == 1)      //按键0返回主菜单
								{	
									OLED_Clear();
									program=0;
									break;
								}
						}
					break;
					
				case 3:   //Test
					while(1){
						key = ADC_Key(ADCConvertedValue[0][2],1);
						if(key == 1)
							{
								printf("D%d\r\n",0);
							}
						if(key == 2)
							{
								printf("D%d\r\n",1);
							}
						if(key == 3)
							{
								printf("D%d\r\n",2);
							}
						if(key == 4)
							{
								printf("D%d\r\n",3);
							}
						if(key == 5)
							{
								printf("D%d\r\n",8);
							}
						delay_ms(5);
						if(ADC_Key(ADCConvertedValue[0][2],1) == 8)      //按键3返回主菜单
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
							if(ADC_Key(ADCConvertedValue[0][2],1) == 3 || PS2_Keyscan(1)==PSB_BLUE)      //按键3返回主菜单
		      			{	
		      				OLED_Clear();
		      				program=0;
		      				break;
		      			}

					}
					break;
					
				case 5:    //
					TIM6_Int_Init( 49, 7199 );    //电机控制
					while(1){
						MoveX(temp_Sudu,3);        //在x轴上以速度x移动count格
						//MoveX_T(temp_Sudu,3);
						PS2_KEY=PS2_Keyscan(0);
						if(PS2_KEY==PSB_PAD_UP)
							{
								temp_Turn++; 
							}
							if(PS2_KEY==PSB_PAD_DOWN)
							{
								temp_Turn--; 
							}
							if(PS2_KEY==PSB_BLUE)
							{
								temp_Sudu--; 
							}
							if(PS2_KEY==PSB_GREEN)
							{
								temp_Sudu++; 
							}
						//delay_ms(5);
						xunji_show();
					}
					break;
						
				case 6:   //串口循迹模块测试
					Mode = 0;
					
					//TIM7_Int_Init( 99, 7199 ); 
					
					TIM6_Int_Init( 49, 7199 );	
					PS2_LY = -100;
					delay_ms(5000);
					PS2_LX = 100;
				PS2_LY = 0;
					delay_ms(5000);
					PS2_LX = 0;
					while(1){
						xunji_show();
  	      	MoveX_T(0,0);
					}						
					break;
				}
			}			
}
/* 定时器6中断服务程序 */
  void TIM6_IRQHandler( void )                                                    /* TIM6中断 */
	{
		
		int t,len,tempQ=0,tempY=0;
		if (TIM_GetITStatus(TIM6, TIM_IT_Update) != RESET) //检查指定的TIM中断发生与否:TIM 中断源 
		{
			PS2_LX = xianFu_125(PS2_LX);
			PS2_LY = xianFu_125(PS2_LY);
			TURN = xianFu_125(TURN);
			AIM_1=(-PS2_LY-PS2_LX+TURN)/128.0*AIM_max;
			AIM_2=(-PS2_LY+PS2_LX-TURN)/128.0*AIM_max;
			AIM_3=(-PS2_LY-PS2_LX-TURN)/128.0*AIM_max;
			AIM_4=(-PS2_LY+PS2_LX+TURN)/128.0*AIM_max;
					
//			//过线判断程序
//			if(myabs(qian) == 30000) {tempQ = 1;}
//		  if(tempQ == 1 && myabs(qian) != 30000 && PS2_LY < 0) {Y++;tempQ = 0;}
//			if(tempQ == 1 && myabs(qian) != 30000 && PS2_LY > 0) {Y--;tempQ = 0;}
////		  if(tempQ == 1 && qian > 600) {Y++;tempQ = 0;}
////			if(tempQ == 1 && qian < 600) {Y--;tempQ = 0;}
//			if(myabs(zuo) == 30000) {tempY = 1;}
//		  if(tempY == 1 && myabs(zuo) != 30000 && PS2_LX > 0) {X++;tempY = 0;}
//		  if(tempY == 1 && myabs(zuo) != 30000 && PS2_LX < 0) {X--;tempY = 0;}
////		  if(tempY == 1 && you > 600) {X++;tempY = 0;}
////		  if(tempY == 1 && you < -600) {X--;tempY = 0;}			
		
			if(USART5_RX_STA&0x8000) //串口5循迹接收程序
		{					   
			len=USART5_RX_STA&0x3fff;//得到此次接收到的数据长度
		
			for(t=0;t<len;t++)
			{
				 YOU[t]=USART5_RX_BUF[t];				
			}
			YOU[t+1]='\0';
			USART5_RX_STA=0;
			you = -atoi(YOU);//将获取到的字符串数据转化为整形数据
		}
		
		//串口4循迹接收程序
		if(USART4_RX_STA&0x8000)//可以放在定时器中断里执行
		{
			len=USART4_RX_STA&0x3fff;//得到此次接收到的数据长度
		
			for(t=0;t<len;t++)
			{
				 ZUO[t]=USART4_RX_BUF[t];				
			}
			ZUO[t+1]='\0';
			USART4_RX_STA=0;
		  zuo = atoi(ZUO);//将获取到的字符串数据转化为整形数据
		}
		
		if(USART3_RX_STA&0x8000)//可以放在定时器中断里执行
		{
			len=USART3_RX_STA&0x3fff;//得到此次接收到的数据长度
		
			for(t=0;t<len;t++)
			{
				 QIAN[t]=USART3_RX_BUF[t];				
			}
			QIAN[t+1]='\0';
			USART3_RX_STA=0;
		  qian = atoi(QIAN);//将获取到的字符串数据转化为整形数据
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
		
		TIM_ClearITPendingBit( TIM6, TIM_IT_Update );                   /* 清除TIMx的中断待处理位:TIM 中断源 */
		//LED1 = !LED1;
	}


/* 定时器7中断服务程序 */
void TIM7_IRQHandler( void )                                                    /* TIM7中断 */
{
	if ( TIM_GetITStatus( TIM7, TIM_IT_Update ) != RESET )                  /* 检查指定的TIM中断发生与否:TIM 中断源 */
	{
		
		switch(Mode){
			case 0:					
				PS2_LX = 100;
				PS2_LY = 100;
        delay_ms(300);
				delay_ms(300);	
				PS2_LY = 0;
        delay_ms(300);	
				delay_ms(300);
        delay_ms(300);	
				clear();
				Mode = 2;
//			LED0 = !LED0;
//			delay_ms(8000);		
			break;
				
			case 1:
				PS2_LX = 0;
				PS2_LY = -98;
				if(myabs(zuo)<100 && myabs(you)<666 ){				
					PS2_LX = 100;
					PS2_LY = 0;
					Mode = 0;
				}
			
			break;
			
			case 2:
				state = MoveX_T(100,3);
				if(state == 0){
					PS2_LX = 100;
					PS2_LY = 0;
					delay_ms(300);
					delay_ms(300);
					delay_ms(300);	
					delay_ms(300);
					clear();
					Mode = 3;
					while(num[0]==0) ;		  
				}
									
			break;
			
			case 3:
				state = MoveY(-100,2);
			  if(state == 0){
			  		Mode = 4;
			  	  clear();
			  	   }	
			break;		
			case 4:
				state = MoveX(100,4);
			  if(state == 0){
			  		Mode = 5;
			  	  clear();  
			  	   }	
			break;
			
			case 5:
				Tiaozheng(100,0);  //x轴上调整100次
				Tiaozheng(100,1);  //y轴上调整100次
			break;
			
			case 6:

			break;
			
			case 7:
				
			break;
			
			case 8:
				
			break;
			
			case 9:
				
			break;
			
		}
		TIM_ClearITPendingBit( TIM7, TIM_IT_Update );                   /* 清除TIMx的中断待处理位:TIM 中断源 */
		LED1 = !LED1;
		
	}
}

/**
  * @brief  获取循迹模块String转Int类型数据，可通过此数据直接配置循迹车循迹
  * @param  *str:串口获取的字符串数据
  * @return dat：返回Int类型的数据
  */
int xianFu_125(int x)
{
	int temp;
	temp = x;
	if(x>125)temp=125;
	if(x<-125)temp=-125;
	return temp;
}
int Tiaozheng(int x,int state)  //调整x次,state=0,调整x,state=1,调整y
{
	while(x!=0){
		x--;
		if(state == 0){MoveX(0,0);}
		if(state == 1){MoveY(0,0);}
	}
	return 0;
}

int clear(void)  
{
	PS2_LX = 0;
	PS2_LY = 0;
	TURN = 0;
	count_JishuY = 0;
	temp_DotY = 0;
	temp_Dot = 0;
	count_Biaozhi = 0;
	tempY1=0;
	tempY2 = 0;
	state = 1;
	return 0;
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


