#include "control.h"		
  /**************************************************************************
作者：平衡小车之家
我的淘宝小店：http://shop114407458.taobao.com/
**************************************************************************/
int pwm0,pwm1;

void Motor_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOE, ENABLE); //使能PB PC端口时钟
 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;	//端口配置
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;      //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;     //50M
  GPIO_Init(GPIOB, &GPIO_InitStructure);					      //根据设定参数初始化GPIOB 
   
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;	//端口配置
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;      //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;     //50M
  GPIO_Init(GPIOC, &GPIO_InitStructure);		
 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_6|GPIO_Pin_7;	//端口配置
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;      //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;     //50M
  GPIO_Init(GPIOE, &GPIO_InitStructure);
	
	GPIO_ResetBits(GPIOB,GPIO_Pin_0);	
	GPIO_ResetBits(GPIOB,GPIO_Pin_1);	
	GPIO_ResetBits(GPIOC,GPIO_Pin_0);	
	GPIO_ResetBits(GPIOC,GPIO_Pin_1);	
	GPIO_ResetBits(GPIOE,GPIO_Pin_0);	
	GPIO_ResetBits(GPIOE,GPIO_Pin_1);	
	GPIO_ResetBits(GPIOE,GPIO_Pin_6);	
	GPIO_ResetBits(GPIOE,GPIO_Pin_7);	
}
/**************************************************************************
函数功能：增量PI控制器
入口参数：编码器测量值，目标速度
返回  值：电机PWM
根据增量式离散PID公式 
pwm+=Kp[e（k）-e(k-1)]+Ki*e(k)+Kd[e(k)-2e(k-1)+e(k-2)]
e(k)代表本次偏差 
e(k-1)代表上一次的偏差  以此类推 
pwm代表增量输出
在我们的速度控制闭环系统里面，只使用PI控制
pwm+=Kp[e（k）-e(k-1)]+Ki*e(k)
Velocity_KP,Velocity_KI
**************************************************************************/
int Incremental_PI_A (int Encoder,int Target)
{ 	
	 static int Bias,Pwm,Last_bias;
	  Bias=-Encoder+Target;                //计算偏差
	 Pwm+=Velocity_KP*(Bias-Last_bias)+Velocity_KI*Bias;   //增量式PI控制器
	  if(Pwm>3000)Pwm=3000;
	 if(Pwm<-3000)Pwm=-3000;
	 Last_bias=Bias;	                   //保存上一次偏差 
	 return Pwm;                         //增量输出
}
int Incremental_PI_B (int Encoder,int Target)
{ 	
	 static int Bias,Pwm,Last_bias;
	 Bias=-Encoder+Target;                //计算偏差
	 Pwm+=Velocity_KP*(Bias-Last_bias)+Velocity_KI*Bias;   //增量式PI控制器
	  if(Pwm>3000)Pwm=3000;
	 if(Pwm<-3000)Pwm=-3000;
	 Last_bias=Bias;	                   //保存上一次偏差 
	 return Pwm;                         //增量输出
}
int Incremental_PI_C (int Encoder,int Target)
{ 	
	 static int Bias,Pwm,Last_bias;
	  Bias=-Encoder+Target;                                    //计算偏差
	 Pwm+=Velocity_KP*(Bias-Last_bias)+Velocity_KI*Bias;   //增量式PI控制器
	 if(Pwm>3000)Pwm=3000;
	 if(Pwm<-3000)Pwm=-3000;
	 Last_bias=Bias;	                   //保存上一次偏差 
	 return Pwm;                         //增量输出
}
int Incremental_PI_D (int Encoder,int Target)
{ 	
	 static int Bias,Pwm,Last_bias;
	 Bias=-Encoder+Target;                                 //计算偏差
	 Pwm+=Velocity_KP*(Bias-Last_bias)+Velocity_KI*Bias;   //增量式PI控制器
	 if(Pwm>3000)Pwm=3000;
	 if(Pwm<-3000)Pwm=-3000;
	 Last_bias=Bias;	                   //保存上一次偏差 
	 return Pwm;                         //增量输出
}
/**************************************************************************
函数功能：位置式PID控制器
入口参数：编码器测量位置信息，目标位置
返回  值：电机PWM
根据位置式离散PID公式 
pwm=Kp*e(k)+Ki*∑e(k)+Kd[e（k）-e(k-1)]
e(k)代表本次偏差 
e(k-1)代表上一次的偏差  
∑e(k)代表e(k)以及之前的偏差的累积和;其中k为1,2,,k;
pwm代表输出
**************************************************************************/
int Position_PID_A (int Encoder,int Target)
{ 	
	 static float Bias,Pwm,Integral_bias,Last_Bias;
	 Bias=Encoder-Target;                                  //计算偏差
	 Integral_bias+=Bias;	                                 //求出偏差的积分
	 if(Integral_bias>100000)Integral_bias=10000;
	 if(Integral_bias<-100000)Integral_bias=-10000;
	 Pwm=Position_KP*Bias+Position_KI/100*Integral_bias+Position_KD*(Bias-Last_Bias);       //位置式PID控制器
	 Last_Bias=Bias;                                       //保存上一次偏差 
	 return Pwm;                                           //增量输出
}
int Position_PID_B (int Encoder,int Target)
{ 	
	 static float Bias,Pwm,Integral_bias,Last_Bias;
	 Bias=Encoder-Target;                                  //计算偏差
	 Integral_bias+=Bias;	                                 //求出偏差的积分
	 if(Integral_bias>100000)Integral_bias=10000;
	 if(Integral_bias<-100000)Integral_bias=-10000;
	 Pwm=Position_KP*Bias+Position_KI/100*Integral_bias+Position_KD*(Bias-Last_Bias);       //位置式PID控制器
	 Last_Bias=Bias;                                       //保存上一次偏差 
	 return Pwm;                                           //增量输出
}
int Position_PID_C (int Encoder,int Target)
{ 	
	 static float Bias,Pwm,Integral_bias,Last_Bias;
	 Bias=Encoder-Target;                                  //计算偏差
	 Integral_bias+=Bias;	                                 //求出偏差的积分
	 if(Integral_bias>100000)Integral_bias=10000;
	 if(Integral_bias<-100000)Integral_bias=-10000;
	 Pwm=Position_KP*Bias+Position_KI/100*Integral_bias+Position_KD*(Bias-Last_Bias);       //位置式PID控制器
	 Last_Bias=Bias;                                       //保存上一次偏差 
	 return Pwm;                                           //增量输出
}
int Position_PID_D (int Encoder,int Target)
{ 	
	 static float Bias,Pwm,Integral_bias,Last_Bias;
	 Bias=Encoder-Target;                                  //计算偏差
	 Integral_bias+=Bias;	                                 //求出偏差的积分
	 if(Integral_bias>100000)Integral_bias=10000;
	 if(Integral_bias<-100000)Integral_bias=-10000;
	 Pwm=Position_KP*Bias+Position_KI/100*Integral_bias+Position_KD*(Bias-Last_Bias);       //位置式PID控制器
	 Last_Bias=Bias;                                       //保存上一次偏差 
	 return Pwm;                                           //增量输出
}
/**************************************************************************
函数功能：所有的控制代码都在这里面
          TIM1控制的5ms定时中断 
**************************************************************************/
//void TIM2_IRQHandler(void)   //TIM3中断
//{

//	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) //检查指定的TIM中断发生与否:TIM 中断源 
//		{
//			
//			
//			if(delay_flag==1)
//			 {
//				 if(++delay_50==10)	 delay_50=0,delay_flag=0;          //===给主函数提供50ms的精准延时
//			 }	
//       if(x==0&&y==0)
//			 {
//				  pwm0=740;
//			    pwm1=780;
//			 }			 
//			 else
//			 { 
//			 pwm0= PositionX_PID ( x, xaim)+740;
//			 pwm1= PositionY_PID ( y, yaim)+780;
//			 }
//			PWM0= Xianfu_Pwm(pwm0);
//			PWM1= Xianfu_Pwm(pwm1);
//			
//				TIM_SetCompare1(TIM3,PWM0);	
//			  TIM_SetCompare2(TIM3,PWM1);	
//	
//		}
//			TIM_ClearITPendingBit(TIM2, TIM_IT_Update  );
//}


/**************************************************************************
函数功能：倾角PID控制
入口参数：角度
返回  值：倾角控制PWM
作    者：平衡小车之家
**************************************************************************/


/**************************************************************************
函数功能：位置PD控制 
入口参数：编码器
返回  值：位置控制PWM
作    者：平衡小车之家
**************************************************************************/
//int Position(int Encoder)
//{  
//   static float Position_PWM,Last_Position,Position_Bias,Position_Differential;
//	 static float Position_Least;
//  	Position_Least =Encoder-Position_Zero;             //===
//    Position_Bias *=0.8;		   
//    Position_Bias += Position_Least*0.2;	             //===一阶低通滤波器  
//	  Position_Differential=Position_Bias-Last_Position;
//	  Last_Position=Position_Bias;
//		Position_PWM=Position_Bias*Position_KP+Position_Differential*Position_KD; //===速度控制	
//	  return Position_PWM;
//}

/**************************************************************************
函数功能：赋值给PWM寄存器
入口参数：PWM
返回  值：无
**************************************************************************/
//void Set_Pwm(int moto)
//{
//    	if(moto<0)			AIN2=1,			AIN1=0;
//			else 	          AIN2=0,			AIN1=1;
//			PWMA=myabs(moto);
//}

/**************************************************************************
函数功能：限制PWM赋值 
入口参数：无
返回  值：无
**************************************************************************/
int PositionX_PID (int Encoder,int Target)
{ 	
	 float Position_KP=5.2,Position_KI=0.05,Position_KD=48;
	 static float Bias,Pwm,Integral_bias,Last_Bias;
	 Bias=Encoder-Target;                                  //计算偏差
	 Integral_bias+=Bias;	                                 //求出偏差的积分
	 Pwm=Position_KP*Bias+Position_KI*Integral_bias+Position_KD*(Bias-Last_Bias);       //位置式PID控制器
	 Last_Bias=Bias;                                       //保存上一次偏差 
	 return Pwm;                                           //增量输出
}
int PositionY_PID (int Encoder,int Target)
{ 	
	 float Position_KP=5.2,Position_KI=0.015,Position_KD=48;
	 static float Bias,Pwm,Integral_bias,Last_Bias;
	 Bias=Encoder-Target;                                  //计算偏差
	 Integral_bias+=Bias;	                                 //求出偏差的积分
	 Pwm=Position_KP*Bias+Position_KI*Integral_bias+Position_KD*(Bias-Last_Bias);       //位置式PID控制器
	 Last_Bias=Bias;                                       //保存上一次偏差 
	 return Pwm;                                           //增量输出
}
int Xianfu_Pwm(int a)
{	
	  int Amplitude=300;    //===PWM满幅是7200 限制在6900
	  if(a<750-Amplitude) a=750-Amplitude;	
		if(a>750+Amplitude)  a=750+Amplitude;	
    return a;	
}
/**************************************************************************
函数功能：按键修改小车运行状态  控制摆杆的位置
入口参数：无
返回  值：无
**************************************************************************/
//void Key(void)
//{	
//	int Position=2080; //目标位置 电机原始位置是10000  转一圈是1040 和编码器精度有关，默认是摆杆Z轴转一圈，输出1040个跳变沿
//	static int tmp,flag,count;
//	tmp=click_N_Double(100); 
//	
//	if(tmp==1)flag=1;//++
//  if(tmp==2)flag=2;//--
//	
//	if(flag==1) //摆杆顺时针运动
//	{
//		Position_Zero++;
//		count++;	
//		if(count==Position) 	flag=0,count=0;
//	}	
//		if(flag==2) //摆杆逆时针运动
//	{
//		Position_Zero--;
//		count++;	
//		if(count==Position) 	flag=0,count=0;
//	}
//}

/**************************************************************************
函数功能：异常关闭电机
入口参数：电压
返回  值：1：异常  0：正常
**************************************************************************/
//u8 Turn_Off(int voltage)
//{
//	    u8 temp; 
//			if(1==Flag_Stop||Angle_Balance<(ZHONGZHI-800)||Angle_Balance>(ZHONGZHI+800)||voltage<1110) //电池电压过低，关闭电机
//			{	      
//      Flag_Stop=1;				
//      temp=1;                                            
//			AIN1=0;                                            
//			AIN2=0;
//      }
//			else
//      temp=0;
//      return temp;			
//}
//	

/**************************************************************************
函数功能：绝对值函数
入口参数：int
返回  值：unsigned int
**************************************************************************/
int myabs(int a)
{ 		   
	  int temp;
		if(a<0)  temp=-a;  
	  else temp=a;
	  return temp;
}
