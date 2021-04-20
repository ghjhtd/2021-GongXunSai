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

char NUM[30];
char COR[30];


int sum;
u8 j;
float ADC_Value[3];//??????????????
u8 state,uart_show='0',look_count;
int servo_num=1, servo_angle;
int count_saoma=0, count_look=0;

int volatile qian,zuo,you,Xunxian,Pinxin,Juli,Chuizhi;  //  三个串口循迹模块量,与线固定距离,左右轮与线平行,与线距离,寻垂直的线
int X,Y;   //小车在地图上的定位坐标，地图左下角的坐标是0，0

int threshold = 288;   //巡线阈值
int bias,temp_Dot = 0,tempY1=0,temp_Turn=73,temp_Sudu,count_Jishu,jishu_shineng=0,count_Biaozhi,count_JishuY,count_BiaozhiY=1,temp_DotY = 0,tempY2=1,count_Tiaozheng=0;   //巡线参数
int num[8],num_cnt,cishu_flag=0;
int COLOR[];

u8 MOVEX_ENABLE,MOVEY_ENABLE,TURNLEFT_ENABLE,TURNRIGTH_ENABLE;   //延x轴或y轴移动使能，左右转90度使能，由主函数控制，对应的控制函数清零
int X_SUDU,X_COUNT,X_ZHONGZHI;                                   //巡线参数
int Y_SUDU,Y_COUNT,Y_ZHONGZHI;
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
	OLED_ShowString( 0, 12, "--NCEPU--", 12);    /* 8*16 “ABC” */
	OLED_ShowString( 0, 28, "CIE510", 12);    /* 12*24 “ABC” */
	OLED_Refresh();
	delay_ms(500);
  OLED_Clear();
	
  TIM8_PWM_Init( 7199, 9 );  	/* PWM频率=1k */
	
	
	uart3_init(115200);     //前循迹模块
	uart4_init(115200);     //左循迹模块
	uart5_init(115200);			//右循迹模块
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
			OLED_ShowString( 0, 0, "Which Program?(1-6)", 12); 
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
					OLED_ShowString( 0, 0, "Which Program?(1-6)", 12); 
					OLED_ShowNum(0,16,program,1,12);
					switch( program ){
						case 2:
							OLED_ShowString(8, 16, "-PS2_remote control", 12); 
							break;
						case 1:
							OLED_ShowString(8, 16, "-Auto Run of chusai", 12); 
							
							break;
						case 3:
							OLED_ShowString(8, 16, "-run Test", 12); 
							break;
						case 4:
							OLED_ShowString(8, 16, "-Key Test", 12); 
							break;
						case 5:
							OLED_ShowString(8, 16, "-XunjiTest", 12); 
							break;
						case 6:
							OLED_ShowString(8, 16, "-None", 12); 
							break;				
					}
					OLED_Refresh();	
					delay_ms(50);
				}
		
		OLED_Clear();
		OLED_ShowNum(0,0,program,1,12);
    OLED_ShowString(12, 0, "Program", 12); 
		OLED_Refresh();	
		delay_ms(500);
		OLED_Clear();		
		
    switch (program)
			{
				case 2:  //采用手柄遥控
					TIM6_Int_Init( 49, 7199 );    //电机控制
				  PS2_Vibration(0,0X40)	 ;
		      while ( 1 )
		      	{	
		      		//xy_show();
              xunji_show();
							//usart_show();
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
							
		      		if(key_bsp == 1 )      //按键0返回主菜单|| PS2_Keyscan(1)==PSB_SELECT
		      			{	
		      				OLED_Clear();
		      				program=0;
		      				break;
		      			}
		      		}
					break;
							
				case 1:    //自动运行
						Mode = 0;
						TIM6_Int_Init( 49, 7199 );    //电机控制
						TIM7_Int_Init( 99, 7199 );	
						printf("Vq\r\n");
					while ( 1 )
						{	
//							clear();  
//							MOVEX_ENABLE = 1;
//							X_SUDU = 100;
//							X_COUNT = 1;
//							X_ZHONGZHI = 0;
//							MOVEY_ENABLE = 1;
//							Y_SUDU = 100;
//							Y_COUNT = 1;
//							Y_ZHONGZHI = 0;
//							TURNLEFT_ENABLE = 1;
//							TURNRIGTH_ENABLE = 1;
							lcd_show();
							switch(Mode){
											case 0:	
												clear();
												zuo = 1000;
												you = 1000;
												PS2_LX = 0;
												PS2_LY = -100;
												while(myabs(zuo)>422 || myabs(you)>422 );
												PS2_LX = 0;
												PS2_LY = 100;
												delay_ms(600);
												Mode = 1;
												clear();
											break;
												
											case 1:
												PS2_LX = 100;
											PS2_LY = 0;                    //往左走一段时间
												delay_ms(1000);
												delay_ms(1000);
												delay_ms(1000);
												clear();
											
												clear();
												MOVEX_ENABLE = 1;
												X_SUDU = 90;                  //往左走两格
												X_COUNT = 2;
												while(MOVEX_ENABLE == 1);
												clear();
											   
												clear();
												MOVEX_ENABLE = 1;             //调整x轴
												X_SUDU = 0;
												X_COUNT = 0;
												delay_ms(1000);
												clear();
												
												PS2_LX = -100;
												PS2_LY = 0;
												delay_ms(800);
												
												clear();
												delay_ms(1000);              //延时等待扫码
												delay_ms(1000);
												while(num[0] == 0){printf("Vq\r\n");delay_ms(1300);delay_ms(900);lcd_show();count_saoma++;
													if(count_saoma > 5){
														PS2_LX = 0;
														PS2_LY = -100;
														delay_ms(600);
														delay_ms(600);
														clear();
														printf("Vq\r\n");delay_ms(1300);delay_ms(1300);delay_ms(1300);
														PS2_LX = 0;
														PS2_LY = 100;
														delay_ms(600);
														delay_ms(600);
														clear();
														lcd_show();
														count_saoma = 0;
													}
												};
												
												PS2_LX = 100;
												PS2_LY = 0;                //往左走到十字中心
												while(myabs(qian) > 300);
												
												PS2_LX = 0;
												PS2_LY = -100;                    //往后走一段时间
												delay_ms(1200);
												
												clear();
												MOVEY_ENABLE = 1;
												Y_SUDU = -100;            //往后走一格
												Y_COUNT = 1;
												while(MOVEY_ENABLE == 1);
												
												
												clear();
//											
//												PS2_LX = 0;
//												PS2_LY = -100;
//												delay_ms(200);
												
//												clear();
//												MOVEY_ENABLE = 1;
//												Y_SUDU = -100;
//												Y_COUNT = 1;
//												while(MOVEY_ENABLE != 0);
//												clear();

												clear();
												MOVEX_ENABLE = 1;
												X_SUDU = 100;         //往左走两格
												X_COUNT = 3;
												while(MOVEX_ENABLE == 1);
												clear();
												
									
												PS2_LX = 100;
												PS2_LY = 0;              //继续往左走走到十字线中心
												while(myabs(qian) > 300);												
												clear();
												
												clear();
												MOVEX_ENABLE = 1;
												X_SUDU = 0;
												X_COUNT = 0;            //调整x轴
												delay_ms(1000);
												delay_ms(1000);
												clear();
												
												clear();
												MOVEY_ENABLE = 1;
												Y_SUDU = 0;            //调整y轴
												Y_COUNT = 0;
												delay_ms(1000);
												delay_ms(1000);
												
												
												clear();					
												//看物料
												while(look_count < 3){
												count_look++;
														if(count_look >3){
																look_count = 3;
																COLOR[0] = num[0];
																COLOR[1] = num[1];
																COLOR[2] = num[2];
																break;
														}
												printf("S%d%d\r\n",0, -10); //最右边
												delay_ms(1000);
													delay_ms(1000);
												printf("Vc\r\n");
												delay_ms(1000);
												delay_ms(1000);
													delay_ms(1000);
												printf("S%d%d\r\n",0, 0); //中间
												delay_ms(1000);
													delay_ms(1000);
												printf("Vc\r\n");
												delay_ms(1000);
												delay_ms(1000);
													delay_ms(1000);
												printf("S%d%d\r\n",0, 10); //最左边
												delay_ms(1000);
												delay_ms(1000);
												printf("Vc\r\n");
												delay_ms(1000);
												delay_ms(1000);
												delay_ms(1000);
													if(look_count < 2){look_count = 0;}
												}
												printf("D0\r\n");
												delay_ms(300);
												delay_ms(300);
												delay_ms(300);
												
//COLOR[0] = 2;
//COLOR[1] = 1;
//COLOR[2] = 3;
												
												Mode = 2;  //靠近原料区
												clear();
											break;
											
											case 2:  //抓原料区AND回到中心点
												printf("D0\r\n");										
												if(num[cishu_flag] == COLOR[0]){
													
													PS2_LX = -100;
													PS2_LY = 0;         //往右走一点
													delay_ms(600);
													delay_ms(600);
													delay_ms(600);
													clear();
													//抓中间
												clear();
												PS2_LX = 0;
												PS2_LY = 100;         //往前走一点
												delay_ms(1200);
												delay_ms(1200);
												clear();
												MOVEY_ENABLE = 1;
												Y_SUDU = 100;           //往前走一格
												Y_COUNT = 1;
												while(MOVEY_ENABLE == 1);
												clear();
	
clear();
												PS2_LX = 0;
												PS2_LY = 80;         //往前走一点
												delay_ms(1200);													
clear();

												printf("S%d%d\r\n",4, 35);
												delay_ms(300);
												delay_ms(300);
												delay_ms(300);
												printf("D8\r\n");
												delay_ms(300);
												delay_ms(300);
												delay_ms(300);
													//回到原点
												PS2_LX = 100;
												PS2_LY = 0;                //往左走到十字中心
												while(myabs(qian) > 300);
												
												PS2_LX = 0;
												PS2_LY = -100;                    //往后走一段时间
												delay_ms(1200);
												
												
												clear();
												MOVEY_ENABLE = 1;
												Y_SUDU = -100;            //往后走三格
												Y_COUNT = 3;
												while(MOVEY_ENABLE == 1);
												clear();
													cishu_flag++;
													Mode = 3;
												}	
												
												if(num[cishu_flag] == COLOR[1]){
													//抓中间
												clear();
												PS2_LX = 0;
												PS2_LY = 100;         //往前走一点
												delay_ms(1200);
												delay_ms(900);
												clear();
												MOVEY_ENABLE = 1;
												Y_SUDU = 100;           //往前走一格
												Y_COUNT = 1;
												while(MOVEY_ENABLE == 1);
												clear();
													cishu_flag++;
												delay_ms(1000);
clear();
												PS2_LX = 0;
												PS2_LY = 80;         //往前走一点
												delay_ms(1200);													
clear();
												delay_ms(1000);
												delay_ms(1000);	
												printf("S%d%d\r\n",4, 35);
												delay_ms(300);
												delay_ms(300);
												delay_ms(300);
												printf("D8\r\n");
												delay_ms(300);
												delay_ms(300);
												delay_ms(300);	
													
												PS2_LX = 0;
												PS2_LY = -100;                    //往后走一段时间
												delay_ms(1200);
												
												clear();
												MOVEY_ENABLE = 1;
												Y_SUDU = -100;            //往后走三格
												Y_COUNT = 3;
												while(MOVEY_ENABLE == 1);
												clear();
													Mode = 3;
												}
												
												if(num[cishu_flag] == COLOR[2]){
													PS2_LX = 100;
													PS2_LY = 0;         //往右走一点
													delay_ms(600);
													delay_ms(700);
													delay_ms(600);
													clear();
													//抓中间
												clear();
												PS2_LX = 0;
												PS2_LY = 100;         //往前走一点
												delay_ms(1200);
												delay_ms(1200);
												clear();
												MOVEY_ENABLE = 1;
												Y_SUDU = 100;           //往前走一格
												Y_COUNT = 1;
												while(MOVEY_ENABLE == 1);
												clear();
													cishu_flag++;
clear();
												PS2_LX = 0;
												PS2_LY = 80;         //往前走一点
												delay_ms(1200);													
clear();
												delay_ms(1000);	
												
												printf("S%d%d\r\n",4, 35);
												delay_ms(300);
												delay_ms(300);
												delay_ms(300);
												printf("D8\r\n");
												delay_ms(300);
												delay_ms(300);
												delay_ms(300);
													//回到中心
												PS2_LX = -100;
												PS2_LY = 0;                //往右走到十字中心
												while(myabs(qian) > 300);
												
												
												
												PS2_LX = 0;
												PS2_LY = -100;                    //往后走一段时间
												delay_ms(1200);
												
												clear();
												MOVEY_ENABLE = 1;
												Y_SUDU = -100;            //往后走三格
												Y_COUNT = 3;
												while(MOVEY_ENABLE == 1);
												clear();
												Mode = 3;	
												}
											break;
											
											case 3: 
												//往左走两格											
												MOVEX_ENABLE = 1;
												X_SUDU = 100;
												X_COUNT = 1;            //调整x轴,与其平行
												while(MOVEX_ENABLE == 1);
												clear();
												Mode = 4;
											break;		
											
											case 4:   //粗加工区放置物料
												if(num[cishu_flag-1] == 1){  //如果是红色
													PS2_LX = 100;
													PS2_LY = -90;         //往后走一点
													delay_ms(900);
													printf("D2\r\n");   //放
													delay_ms(1000);
													delay_ms(1000);
													delay_ms(1000);
													delay_ms(1000);
													printf("S%d%d\r\n",4, 0);
													delay_ms(1000);
													delay_ms(1000);
													printf("D8\r\n"); 
													delay_ms(1000);
													delay_ms(1000);
													
													clear();
												MOVEY_ENABLE = 1;
												Y_SUDU = 100;           //往前走一格
												Y_COUNT = 1;
												while(MOVEY_ENABLE == 1);
												clear();
												
												PS2_LX = -100;
													PS2_LY = 0;         //往右走一点
													delay_ms(900);
													delay_ms(300);
													clear();
													MOVEX_ENABLE = 1;
												X_SUDU = -100;//往右走三格
												X_COUNT = 1;            
												while(MOVEX_ENABLE == 1);
												
												clear();
												PS2_LX = 100;
												PS2_LY = 0;                //往右走到十字中心
												while(myabs(qian) > 300);
												clear();
												
												clear();
												PS2_LX = 0;
												PS2_LY = 100;         //往前走一点
												delay_ms(900);
												delay_ms(900);
												clear();
												
												clear();
												MOVEY_ENABLE = 1;
												Y_SUDU = 100;           //往前走一格
												Y_COUNT = 2;
												while(MOVEY_ENABLE == 1);
												clear();
												Mode = 2;
												}
												
												
												if(num[cishu_flag-1] == 2){  //如果是蓝色
													PS2_LX = 80;
													PS2_LY = 0;         //往左走一点
													delay_ms(200);
													clear();
													PS2_LX = 0;
													PS2_LY = -90;         //往后走一点
													delay_ms(900);
													clear();
												MOVEY_ENABLE = 1;
												Y_SUDU = -100;           //往后走一格
												Y_COUNT = 1;												
												while(MOVEY_ENABLE == 1);
													
													PS2_LX = 0;
													PS2_LY = 90;         //往前走一点
													delay_ms(300);													
												clear();
													
													printf("D2\r\n");   //放
													delay_ms(1000);
													delay_ms(1000);
													delay_ms(1000);
													delay_ms(1000);
													printf("S%d%d\r\n",4, 0);
													delay_ms(1000);
													delay_ms(1000);
													printf("D8\r\n"); 
													delay_ms(1000);
													delay_ms(1000);
													
													clear();
												MOVEY_ENABLE = 1;
												Y_SUDU = 100;           //往前走一格
												Y_COUNT = 1;
												while(MOVEY_ENABLE == 1);
												clear();
												
												PS2_LX = -100;
													PS2_LY = 0;         //往右走一点
													delay_ms(900);
													delay_ms(300);
													clear();
													MOVEX_ENABLE = 1;
												X_SUDU = -100;//往右走三格
												X_COUNT = 1;            
												while(MOVEX_ENABLE == 1);
												
												clear();
												PS2_LX = 100;
												PS2_LY = 0;                //往右走到十字中心
												while(myabs(qian) > 300);
												clear();
												
												clear();
												PS2_LX = 0;
												PS2_LY = 100;         //往前走一点
												delay_ms(900);
												delay_ms(900);
												clear();
												
												clear();
												MOVEY_ENABLE = 1;
												Y_SUDU = 100;           //往前走一格
												Y_COUNT = 2;
												while(MOVEY_ENABLE == 1);
												clear();
												Mode = 2;
												}
												
												
												if(num[cishu_flag-1] == 3){  //如果是绿色
													PS2_LX = 100;
													PS2_LY = 0;         //往左走一点
													delay_ms(200);
													clear();												
													
													printf("D2\r\n");   //放
													delay_ms(1000);
													delay_ms(1000);
													delay_ms(1000);
													delay_ms(1000);
													printf("S%d%d\r\n",4, 0);
													delay_ms(1000);
													delay_ms(1000);
													printf("D8\r\n"); 
													delay_ms(1000);
													delay_ms(1000);
													
													clear();
												
												PS2_LX = -100;
													PS2_LY = 0;         //往右走一点
													delay_ms(900);
													delay_ms(200);
													clear();
													MOVEX_ENABLE = 1;
												X_SUDU = -100;//往右走三格
												X_COUNT = 1;            
												while(MOVEX_ENABLE == 1);
												
												clear();
												PS2_LX = 100;
												PS2_LY = 0;                //往右走到十字中心
												while(myabs(qian) > 300);
												clear();
												
												clear();
												PS2_LX = 0;
												PS2_LY = 100;         //往前走一点
												delay_ms(900);
												delay_ms(600);
												clear();
												
												clear();
												MOVEY_ENABLE = 1;
												Y_SUDU = 100;           //往前走一格
												Y_COUNT = 2;
												while(MOVEY_ENABLE == 1);
												clear();
												Mode = 2;
												}
											break;
											
											case 5:
												
											break;
											
											case 6:
												
											break;
											
											case 7:
												MOVEX_ENABLE = 1;
												X_SUDU = 0;
												X_COUNT = 0;
												xunji_show();
											break;
											
											case 8:
												clear();
												MOVEY_ENABLE = 1;
												Y_SUDU = 100;
												Y_COUNT = 11;
												while(MOVEY_ENABLE == 1){xunjiY_show();};
												//Mode = 9;
												clear();
											break;
											
											case 9:
												while(1);
											break;
								}
							
							}
										break;
													
				case 3:   //Test
					TIM6_Int_Init( 49, 7199 );
					while(1){
						key = ADC_Key(ADCConvertedValue[0][2],1);
						lcd_show();
						if(key == 1)
							{
								printf("V%c\r\n",'q');
							}
						if(key == 2)
							{
								printf("V%c\r\n",'c');
							}
						if(key == 3)
							{
								printf("D%c\r\n",'0');
							}
						if(key == 4)
							{
								printf("D%c\r\n",'3');
							}
						if(key == 5)
							{
								printf("D%d\r\n",8);
							}
						while(NUM[0] == 0){printf("Vq\r\n");delay_ms(1200);lcd_show();};
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
					printf("D0\r\n");
												delay_ms(300);
												delay_ms(300);
												delay_ms(300);
					TIM6_Int_Init( 49, 7199 );
					PS2_LX = -100;
					PS2_LY = 0;         //往右走一点
					delay_ms(600);
					delay_ms(600);
				delay_ms(600);
				clear();
				PS2_LX = 0;
				PS2_LY = 100;         //往前走一点
				delay_ms(1200);
				delay_ms(600);
				clear();
				MOVEY_ENABLE = 1;
				Y_SUDU = 100;           //往前走一格
				Y_COUNT = 1;
				while(MOVEY_ENABLE == 1);
				clear();
				delay_ms(1000);
				delay_ms(1000);
				delay_ms(1000);	
				printf("S%d%d\r\n",4, 35);
				delay_ms(300);
				delay_ms(300);
				delay_ms(300);
				printf("D8\r\n");
				delay_ms(300);
				delay_ms(300);
												delay_ms(300);	
					while(1);
					
					break;
					
				case 5:    //
					TIM6_Int_Init( 49, 7199 );    //电机控制
					while(1){
						MoveX(temp_Sudu,3,0);        //在x轴上以速度x移动count格
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
  	      	MoveX_T(0,0,0);
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
			
			if(USART2_RX_STA&0x8000)//可以放在定时器中断里执行
		{
			len=USART2_RX_STA&0x3fff;//得到此次接收到的数据长度
			for(t=0;t<len;t++)
			{
				 NUM[t]=USART2_RX_BUF[t];				
			}
			NUM[t+1]='\0';
			USART2_RX_STA=0;
			if(NUM[0] == 'Q'){
				num[0] = NUM[1]-'0';
				num[1] = NUM[2]-'0';
				num[2] = NUM[3]-'0';
				num[3] = NUM[4]-'0';
				num[4] = NUM[5]-'0';
				num[5] = NUM[6]-'0';
			}
			if(NUM[0] == 'C' && COLOR[look_count-1] != (NUM[1]-'3') && look_count < 3){
				COLOR[look_count] = NUM[1]-'3';
				look_count ++;
			}
		}

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
	}

/* 定时器7中断服务程序 */                               //巡线参数
void TIM7_IRQHandler( void )                                                    /* TIM7中断 */
{
	if ( TIM_GetITStatus( TIM7, TIM_IT_Update ) != RESET )                  /* 检查指定的TIM中断发生与否:TIM 中断源 */
	{
		if(MOVEX_ENABLE == 1){      
			MoveX(X_SUDU,X_COUNT,X_ZHONGZHI);
//			LED1 = !LED1;
			//MoveX_T(X_SUDU,X_COUNT,X_ZHONGZHI);
		}	
		if(MOVEY_ENABLE == 1){
			MoveY(Y_SUDU,Y_COUNT,Y_ZHONGZHI);
		}
		if(TURNLEFT_ENABLE == 1){
			
		}	
		if(TURNRIGTH_ENABLE == 1){
			
		}
		
		TIM_ClearITPendingBit( TIM7, TIM_IT_Update );                   /* 清除TIMx的中断待处理位:TIM 中断源 */
		//LED1 = !LED1;
		
	}
}

int xianFu_125(int x)
{
	int temp;
	temp = x;
	if(x>125)temp=125;
	if(x<-125)temp=-125;
	return temp;
}
int Tiaozheng(int x,int state)  //调整x次      state=0,调整x    state=1,调整y
{
	while(x!=0){
		x--;
		if(state == 0){MoveX(0,0,0);}
		if(state == 1){MoveY(0,0,0);}
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
	X_SUDU=0;
	X_COUNT=0;
	X_ZHONGZHI=0;
	Y_SUDU=0;
	Y_COUNT=0;
	Y_ZHONGZHI=0;
	MOVEX_ENABLE=0;
	MOVEY_ENABLE=0;
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



