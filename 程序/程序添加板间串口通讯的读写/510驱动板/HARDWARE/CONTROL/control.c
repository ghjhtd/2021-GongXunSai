#include "control.h"		
  /**************************************************************************
作者：平衡小车之家
我的淘宝小店：http://shop114407458.taobao.com/
**************************************************************************/


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
入口参数：电机 PWM
返回  值：无
**************************************************************************/
void Set_Pwm(int moto,int pwm)
{
    	if(pwm<0)		MOTO_FX(moto,0);
			else        MOTO_FX(moto,1);
			pwm=myabs(pwm);
	    if(pwm>4000)
				pwm=4000;
			
	switch(moto)
		{
	case 1:
		
	TIM_SetCompare1( TIM8, pwm ); 	//c6789    //四轮pwm
  break;
	case 2:
	TIM_SetCompare2( TIM8, pwm );
  break;
	case 3:
	TIM_SetCompare3( TIM8, pwm );
  break;
	case 4:
	TIM_SetCompare4( TIM8, pwm );
  break;

    }
}
//电机方向控制
void MOTO_FX(int moto,u8 fx)
{
		switch(moto)
		{
	case 1:
	PCout(0)=fx,PCout(1)=!fx;	//c6789    //四轮pwm
  break;
	case 2:
	PEout(7)=fx,PEout(6)=!fx;
  break;
	case 3:
		PBout(1)=fx,PBout(0)=!fx;
  break;
	case 4:
		PEout(0)=fx,PEout(1)=!fx;
  break;
    }
}


/**************************************************************************
函数功能：电机转向初始化
入口参数：无
返回  值：无
**************************************************************************/
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
**************************************************************************/
float Velocity_KP=80,Velocity_KI=4;
float Velocity_KP1=0.05,Velocity_KI1=0.05; //循迹pid

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
	 Bias=-Encoder+Target;               //计算偏差
	 Pwm+=Velocity_KP*(Bias-Last_bias)+Velocity_KI*Bias;   //增量式PI控制器
 if(Pwm>3000)Pwm=3000;
	 if(Pwm<-3000)Pwm=-3000;
	 Last_bias=Bias;	                   //保存上一次偏差 
	 return Pwm;                         //增量输出
}
int Incremental_PI_C (int Encoder,int Target)
{ 	
	 static int Bias,Pwm,Last_bias;
	 Bias=-Encoder+Target;                                 //计算偏差
	 Pwm+=Velocity_KP*(Bias-Last_bias)+Velocity_KI*Bias;   //增量式PI控制器
	 if(Pwm>3000)Pwm=3000;
	 if(Pwm<-3000)Pwm=-3000;
	 Last_bias=Bias;	                   //保存上一次偏差 
	 return Pwm;                         //增量输出
}
int Incremental_PI_D (int Encoder,int Target)
{ 	
	 static int Bias,Pwm,Last_bias;
	 Bias=-Encoder+Target;                                  //计算偏差
	 Pwm+=Velocity_KP*(Bias-Last_bias)+Velocity_KI*Bias;   //增量式PI控制器
 if(Pwm>3000)Pwm=3000;
	 if(Pwm<-3000)Pwm=-3000;
	 Last_bias=Bias;	                   //保存上一次偏差 
	 return Pwm;                         //增量输出
}


/**************************************************************************
函数功能：限制PWM赋值 
入口参数：无
返回  值：无
**************************************************************************/
int PositionX_PID (int Encoder,int Target)
{ 	
	 float Position_KP=0,Position_KI=0.05,Position_KD=48;
	 static float Bias,Pwm,Integral_bias,Last_Bias;
	 Bias=Encoder-Target;                                  //计算偏差
	 Integral_bias+=Bias;	                                 //求出偏差的积分
	 Pwm=Position_KP*Bias+Position_KI*Integral_bias+Position_KD*(Bias-Last_Bias);       //位置式PID控制器
	 Last_Bias=Bias;                                       //保存上一次偏差 
	 return Pwm;                                           //增量输出
}
int PositionY_PID (int Encoder,int Target)
{ 	
	 float Balance_KP=6, Balance_Ki=0, Balance_KD =0;
	 static int Bias,balance=750,Last_Bias,D_Bias,Delta_Delta_Bias,Pre_Delta_Bias;
	                                                                    /* ?? ?? ??? */
  Bias=-Encoder+Target;
	D_Bias = Bias - Last_Bias;                                                                      /* ??????? ?????? */


	Delta_Delta_Bias = D_Bias - Pre_Delta_Bias;                                                     /* pid ???????? */

	balance  = balance + Balance_KP * D_Bias + Balance_Ki * Bias + Balance_KD * Delta_Delta_Bias;    /* pid ???????? */

	Last_Bias = Bias;                                                                               /* ???????? */

	Pre_Delta_Bias = D_Bias;                                                                        /* pid ???????? */

	return(balance);

	 
	
	 
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

////*********************************循迹模块

//int Incremental_Bias (int Encoder)
//{  
//	 int Target = 0;
//	 static int Bias,Pwm,Last_bias;
//	 Bias=-Encoder+Target;                //计算偏差
//	 TURN+=Velocity_KP1*(Bias-Last_bias)+Velocity_KI1*Bias;   //增量式PI控制器
//	 if(Pwm>128)Pwm=128;
//	 if(Pwm<-128)Pwm=-128;
//	 Last_bias=Bias;	                   //保存上一次偏差 
//	 return Pwm;                         //增量输出
//}

//int Incremental_Juli (int Encoder,int Target)
//{  
//	 static int Bias,Pwm,Last_bias;
//	 Bias=-Encoder+Target;                //计算偏差
//	 Pwm+=Velocity_KP1*(Bias-Last_bias)+Velocity_KI1*Bias;   //增量式PI控制器
//	 if(Pwm>128)Pwm=128;
//	 if(Pwm<-128)Pwm=-128;
//	 Last_bias=Bias;	                   //保存上一次偏差 
//	 return Pwm;                         //增量输出
//}

//int Xianfu_Bias(int a)
//{	
//	  int Amplitude=80;    //将左右循迹模块偏差小于Amplitude时置0
//	  if(a<Amplitude) a=0;	
//		if(a>-Amplitude)  a=0;	
//    return a;	
//}

//int paral(int zuo,int you, int juli ,int Pinxin ,int Chuizhi,int Xunxian){
//	  if(Pinxin == 1){
//			int bias = zuo - you;
//			bias = Xianfu_Bias(bias); //偏差过小时置0
//			TURN = Incremental_Bias(bias);  //与线平行pid
//			if(bias == 0 && Xunxian == 1){
//				PS2_LY = Incremental_Juli(you , juli);  //与线的距离pid		
//			}
//	}
//		if(Chuizhi == 1){
//			if(qian/1000*AIM_max > 0.3){
//				PS2_LX = qian/1000*AIM_max;
//			}			
//		}
//}

//int MoveTo(int x,int y){
//	MoveX(x - X);
//	MoveY(y - Y);
//}

//int MoveX(int x){	
//	int temp = 0;
//	while(x != X){
//		Pinxin = 1;//开启左右轮与线平行
//		Xunxian = 1;//开启与线固定距离
//		Chuizhi = 0;//关闭寻垂直的线的功能
//		if(x-X > 0){  //目标位置在右边，玩右走
//			PS2_LX = 128;
//		}
//		if(x-X < 0){ //目标位置在左边，玩左走
//			PS2_LX = -128;
//		}		
//	}
//	PS2_LX = 0;	
//	PS2_LY = 0;
//	Pinxin = 0;
//	Xunxian = 0;
//	Chuizhi = 0;
//}

//int MoveY(int y){
//	int temp = 0;
//	while(y != Y){
//		Pinxin = 1;//开启左右轮与平行线平行
//		Xunxian = 0;//关闭与平行的线固定距离的功能
//		Chuizhi = 1;//开启寻垂直的线的功能
//		if(y-Y > 0){  //目标位置在前边，玩前走
//			PS2_LY = 128;
//		}
//		if(y-Y < 0){ //目标位置在后面，玩后走
//			PS2_LY = -128;
//		}		
//	}
//	PS2_LX = 0;	
//	PS2_LY = 0;
//	Pinxin = 0;
//	Xunxian = 0;
//	Chuizhi = 0;
//}

//int MoveX_T(int aim,int time){	
//	int temp = 0;
//	Pinxin = 1;//开启左右轮与线平行
//	Xunxian = 1;//开启与线固定距离
//	Chuizhi = 0;//关闭寻垂直的线的功能
//	if(aim > 0){  //目标位置在右边，玩右走
//		PS2_LX = aim;
//		delay_ms(time);
//	}
//	if(aim < 0){ //目标位置在左边，玩左走
//		PS2_LX = aim;
//		delay_ms(time);
//	}		
//	PS2_LX = 0;	
//	PS2_LY = 0;
//	Pinxin = 0;
//	Xunxian = 0;
//	Chuizhi = 0;
//}

//int MOveY_T(int aim,int time){
//	int temp = 0;
//	Pinxin = 1;//开启左右轮与平行线平行
//	Xunxian = 0;//关闭与平行的线固定距离的功能
//	Chuizhi = 1;//开启寻垂直的线的功能
//	if(aim > 0){  //目标位置在前边，玩前走
//		PS2_LY = aim;
//		delay_ms(time);
//	}
//	if(aim < 0){ //目标位置在后面，玩后走
//		PS2_LY = aim;
//		delay_ms(time);
//	}		
//	PS2_LX = 0;	
//	PS2_LY = 0;
//	Pinxin = 0;
//	Xunxian = 0;
//	Chuizhi = 0;
//}


int MoveX_T(int x,int count){
		PS2_LX = x;
		PS2_LY = 0;
		TURN = 0; 
		bias = (zuo - you);
		count_Jishu++;
		if(count_Jishu > 8){count_Biaozhi = 1;count_Jishu = 0;LED0 = !LED0; }
		if(bias > threshold&& myabs(bias) < 10000){
			TURN = temp_Turn; 
		}
		if(bias < -threshold&& myabs(bias) < 10000){
			TURN = -temp_Turn; 
		}
		if(myabs(bias) < threshold && myabs(zuo) > 156&& myabs(bias) < 10000){
			PS2_LY = -zuo / 7; 
		}
		if(myabs(qian) < 80) {tempY1 = 1;}
		if(tempY1 == 1 && qian >200 && count_Biaozhi == 1 ) {temp_Dot--;tempY1 = 0;count_Biaozhi =0;}
		if(tempY1 == 1 && qian < -200 && count_Biaozhi == 1) {temp_Dot++;tempY1 = 0;count_Biaozhi =0;}
		if(temp_Dot == count&& count!=0) {temp_Dot=0;tempY1 = 0;PS2_LX = 0;PS2_LY = 0;TURN = 0; return 0;}
		else return 1;
}        //在x轴上以速度x移动time ms

//int MoveX(int x,int count){
//	  //LED1 = !LED1;
//		PS2_LX = x;
//		PS2_LY = 0;
//		TURN = 0; 
//		bias = (zuo - you);
//		count_Jishu++;
//		if(count_Jishu > 44){count_Biaozhi = 1;count_Jishu = 0;LED0 = !LED0; }
//		if(myabs(bias) > threshold && myabs(bias) < 5000){
//			TURN = bias/16; 
//		}
//		if(myabs(bias) < threshold && myabs(zuo) > 156 && myabs(bias) < 10000){
//			PS2_LY = -zuo / 7; 
//		}
//		if(myabs(qian) < 211) {tempY1 = 1;}
//		if(tempY1 == 1 && qian >712 && count_Biaozhi == 1 ) {temp_Dot--;tempY1 = 0;count_Biaozhi =0;}
//		if(tempY1 == 1&& qian < -712 && count_Biaozhi == 1 ) {temp_Dot++;tempY1 = 0;count_Biaozhi =0;}
//		if(temp_Dot == count && count!=0) {temp_Dot=0;tempY1 = 0;PS2_LX = 0;PS2_LY = 0;TURN = 0; return 0;}
//		else return 1;	
//		
//}       //在x轴上以速度x移动count格

int MoveX(int x,int count){
	  //LED1 = !LED1;
		PS2_LX = x;
		PS2_LY = 0;
		TURN = 0; 
		bias = (zuo - you);
		count_Jishu++;
		if(count_Jishu > 58){count_Biaozhi = 1;count_Jishu = 0;LED0 = !LED0; }
		if(myabs(bias) > threshold && myabs(bias) < 5000){
			//PS2_LX = 0;
			TURN = bias/16; 
		}
		if(myabs(bias) < threshold && myabs(zuo) > 156 && myabs(bias) < 10000){
			PS2_LY = -zuo / 7; 
		}
		if(myabs(zuo) > 29000) {tempY1 = 1;}
		if(tempY1 == 1 && PS2_LX < -10 && count_Biaozhi == 1 ) {temp_Dot--;tempY1 = 0;count_Biaozhi =0;}
		if(tempY1 == 1&& PS2_LX > 10 && count_Biaozhi == 1 ) {temp_Dot++;tempY1 = 0;count_Biaozhi =0;}
		if(temp_Dot == count && count!=0) {temp_Dot=0;tempY1 = 0;PS2_LX = 0;PS2_LY = 0;TURN = 0; return 0;}
		else return 1;	
		
} 

int MoveY_T(int x,int time){
		
}        //在y轴上以速度x移动time ms

int MoveY(int y,int count){
		PS2_LX = 0;
		PS2_LY = y;
		TURN = 0; 
		bias = qian;
		count_JishuY++;
	  if(count_JishuY > 56){count_BiaozhiY = 1;count_JishuY = 0;LED0 = !LED0;}
		if(myabs(bias) > threshold && myabs(bias) < 10000){
			PS2_LX = qian / 9; 
		}
		if(myabs(zuo) < 211) {tempY2 = 1;}
		if(tempY2 == 1 && zuo >488&& count_BiaozhiY == 1) {temp_DotY--;tempY2 = 0;count_Biaozhi =0;}
		if(tempY2 == 1 && zuo <-488&& count_BiaozhiY == 1) {temp_DotY++;tempY2 = 0;count_Biaozhi =0;}
		if(temp_DotY == count && count!=0){temp_DotY=0;tempY2 = 0;PS2_LX = 0;PS2_LY = 0;TURN = 0; return 0;}
		else return 1;	
}        //在y轴上以速度x移动count格






