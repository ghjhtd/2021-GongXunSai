#include "control.h"		
  /**************************************************************************
���ߣ�ƽ��С��֮��
�ҵ��Ա�С�꣺http://shop114407458.taobao.com/
**************************************************************************/


/**************************************************************************
�������ܣ����еĿ��ƴ��붼��������
          TIM1���Ƶ�5ms��ʱ�ж� 
**************************************************************************/
//void TIM2_IRQHandler(void)   //TIM3�ж�
//{

//	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) //���ָ����TIM�жϷ������:TIM �ж�Դ 
//		{
//			
//			
//			if(delay_flag==1)
//			 {
//				 if(++delay_50==10)	 delay_50=0,delay_flag=0;          //===���������ṩ50ms�ľ�׼��ʱ
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
�������ܣ����PID����
��ڲ������Ƕ�
����  ֵ����ǿ���PWM
��    �ߣ�ƽ��С��֮��
**************************************************************************/


/**************************************************************************
�������ܣ�λ��PD���� 
��ڲ�����������
����  ֵ��λ�ÿ���PWM
��    �ߣ�ƽ��С��֮��
**************************************************************************/
//int Position(int Encoder)
//{  
//   static float Position_PWM,Last_Position,Position_Bias,Position_Differential;
//	 static float Position_Least;
//  	Position_Least =Encoder-Position_Zero;             //===
//    Position_Bias *=0.8;		   
//    Position_Bias += Position_Least*0.2;	             //===һ�׵�ͨ�˲���  
//	  Position_Differential=Position_Bias-Last_Position;
//	  Last_Position=Position_Bias;
//		Position_PWM=Position_Bias*Position_KP+Position_Differential*Position_KD; //===�ٶȿ���	
//	  return Position_PWM;
//}

/**************************************************************************
�������ܣ���ֵ��PWM�Ĵ���
��ڲ�������� PWM
����  ֵ����
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
		
	TIM_SetCompare1( TIM8, pwm ); 	//c6789    //����pwm
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
//����������
void MOTO_FX(int moto,u8 fx)
{
		switch(moto)
		{
	case 1:
	PCout(0)=fx,PCout(1)=!fx;	//c6789    //����pwm
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
�������ܣ����ת���ʼ��
��ڲ�������
����  ֵ����
**************************************************************************/
void Motor_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOE, ENABLE); //ʹ��PB PC�˿�ʱ��
 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;	//�˿�����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;      //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;     //50M
  GPIO_Init(GPIOB, &GPIO_InitStructure);					      //�����趨������ʼ��GPIOB 
   
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;	//�˿�����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;      //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;     //50M
  GPIO_Init(GPIOC, &GPIO_InitStructure);		
 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_6|GPIO_Pin_7;	//�˿�����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;      //�������
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
�������ܣ�����PI������
��ڲ���������������ֵ��Ŀ���ٶ�
����  ֵ�����PWM
��������ʽ��ɢPID��ʽ 
pwm+=Kp[e��k��-e(k-1)]+Ki*e(k)+Kd[e(k)-2e(k-1)+e(k-2)]
e(k)������ƫ�� 
e(k-1)������һ�ε�ƫ��  �Դ����� 
pwm�����������
�����ǵ��ٶȿ��Ʊջ�ϵͳ���棬ֻʹ��PI����
pwm+=Kp[e��k��-e(k-1)]+Ki*e(k)
**************************************************************************/
float Velocity_KP=80,Velocity_KI=4;
float Velocity_KP1=0.05,Velocity_KI1=0.05; //ѭ��pid

int Incremental_PI_A (int Encoder,int Target)
{ 	
	 static int Bias,Pwm,Last_bias;
	 Bias=-Encoder+Target;                //����ƫ��
	 Pwm+=Velocity_KP*(Bias-Last_bias)+Velocity_KI*Bias;   //����ʽPI������
	 if(Pwm>3000)Pwm=3000;
	 if(Pwm<-3000)Pwm=-3000;
	 Last_bias=Bias;	                   //������һ��ƫ�� 
	 return Pwm;                         //�������
}
int Incremental_PI_B (int Encoder,int Target)
{ 	
	 static int Bias,Pwm,Last_bias;
	 Bias=-Encoder+Target;               //����ƫ��
	 Pwm+=Velocity_KP*(Bias-Last_bias)+Velocity_KI*Bias;   //����ʽPI������
 if(Pwm>3000)Pwm=3000;
	 if(Pwm<-3000)Pwm=-3000;
	 Last_bias=Bias;	                   //������һ��ƫ�� 
	 return Pwm;                         //�������
}
int Incremental_PI_C (int Encoder,int Target)
{ 	
	 static int Bias,Pwm,Last_bias;
	 Bias=-Encoder+Target;                                 //����ƫ��
	 Pwm+=Velocity_KP*(Bias-Last_bias)+Velocity_KI*Bias;   //����ʽPI������
	 if(Pwm>3000)Pwm=3000;
	 if(Pwm<-3000)Pwm=-3000;
	 Last_bias=Bias;	                   //������һ��ƫ�� 
	 return Pwm;                         //�������
}
int Incremental_PI_D (int Encoder,int Target)
{ 	
	 static int Bias,Pwm,Last_bias;
	 Bias=-Encoder+Target;                                  //����ƫ��
	 Pwm+=Velocity_KP*(Bias-Last_bias)+Velocity_KI*Bias;   //����ʽPI������
 if(Pwm>3000)Pwm=3000;
	 if(Pwm<-3000)Pwm=-3000;
	 Last_bias=Bias;	                   //������һ��ƫ�� 
	 return Pwm;                         //�������
}


/**************************************************************************
�������ܣ�����PWM��ֵ 
��ڲ�������
����  ֵ����
**************************************************************************/
int PositionX_PID (int Encoder,int Target)
{ 	
	 float Position_KP=0,Position_KI=0.05,Position_KD=48;
	 static float Bias,Pwm,Integral_bias,Last_Bias;
	 Bias=Encoder-Target;                                  //����ƫ��
	 Integral_bias+=Bias;	                                 //���ƫ��Ļ���
	 Pwm=Position_KP*Bias+Position_KI*Integral_bias+Position_KD*(Bias-Last_Bias);       //λ��ʽPID������
	 Last_Bias=Bias;                                       //������һ��ƫ�� 
	 return Pwm;                                           //�������
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
	  int Amplitude=300;    //===PWM������7200 ������6900
	  if(a<750-Amplitude) a=750-Amplitude;	
		if(a>750+Amplitude)  a=750+Amplitude;	
    return a;	
}
/**************************************************************************
�������ܣ������޸�С������״̬  ���ưڸ˵�λ��
��ڲ�������
����  ֵ����
**************************************************************************/
//void Key(void)
//{	
//	int Position=2080; //Ŀ��λ�� ���ԭʼλ����10000  תһȦ��1040 �ͱ����������йأ�Ĭ���ǰڸ�Z��תһȦ�����1040��������
//	static int tmp,flag,count;
//	tmp=click_N_Double(100); 
//	
//	if(tmp==1)flag=1;//++
//  if(tmp==2)flag=2;//--
//	
//	if(flag==1) //�ڸ�˳ʱ���˶�
//	{
//		Position_Zero++;
//		count++;	
//		if(count==Position) 	flag=0,count=0;
//	}	
//		if(flag==2) //�ڸ���ʱ���˶�
//	{
//		Position_Zero--;
//		count++;	
//		if(count==Position) 	flag=0,count=0;
//	}
//}

/**************************************************************************
�������ܣ��쳣�رյ��
��ڲ�������ѹ
����  ֵ��1���쳣  0������
**************************************************************************/
//u8 Turn_Off(int voltage)
//{
//	    u8 temp; 
//			if(1==Flag_Stop||Angle_Balance<(ZHONGZHI-800)||Angle_Balance>(ZHONGZHI+800)||voltage<1110) //��ص�ѹ���ͣ��رյ��
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
�������ܣ�����ֵ����
��ڲ�����int
����  ֵ��unsigned int
**************************************************************************/
int myabs(int a)
{ 		   
	  int temp;
		if(a<0)  temp=-a;  
	  else temp=a;
	  return temp;
}

////*********************************ѭ��ģ��

//int Incremental_Bias (int Encoder)
//{  
//	 int Target = 0;
//	 static int Bias,Pwm,Last_bias;
//	 Bias=-Encoder+Target;                //����ƫ��
//	 TURN+=Velocity_KP1*(Bias-Last_bias)+Velocity_KI1*Bias;   //����ʽPI������
//	 if(Pwm>128)Pwm=128;
//	 if(Pwm<-128)Pwm=-128;
//	 Last_bias=Bias;	                   //������һ��ƫ�� 
//	 return Pwm;                         //�������
//}

//int Incremental_Juli (int Encoder,int Target)
//{  
//	 static int Bias,Pwm,Last_bias;
//	 Bias=-Encoder+Target;                //����ƫ��
//	 Pwm+=Velocity_KP1*(Bias-Last_bias)+Velocity_KI1*Bias;   //����ʽPI������
//	 if(Pwm>128)Pwm=128;
//	 if(Pwm<-128)Pwm=-128;
//	 Last_bias=Bias;	                   //������һ��ƫ�� 
//	 return Pwm;                         //�������
//}

//int Xianfu_Bias(int a)
//{	
//	  int Amplitude=80;    //������ѭ��ģ��ƫ��С��Amplitudeʱ��0
//	  if(a<Amplitude) a=0;	
//		if(a>-Amplitude)  a=0;	
//    return a;	
//}

//int paral(int zuo,int you, int juli ,int Pinxin ,int Chuizhi,int Xunxian){
//	  if(Pinxin == 1){
//			int bias = zuo - you;
//			bias = Xianfu_Bias(bias); //ƫ���Сʱ��0
//			TURN = Incremental_Bias(bias);  //����ƽ��pid
//			if(bias == 0 && Xunxian == 1){
//				PS2_LY = Incremental_Juli(you , juli);  //���ߵľ���pid		
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
//		Pinxin = 1;//��������������ƽ��
//		Xunxian = 1;//�������߹̶�����
//		Chuizhi = 0;//�ر�Ѱ��ֱ���ߵĹ���
//		if(x-X > 0){  //Ŀ��λ�����ұߣ�������
//			PS2_LX = 128;
//		}
//		if(x-X < 0){ //Ŀ��λ������ߣ�������
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
//		Pinxin = 1;//������������ƽ����ƽ��
//		Xunxian = 0;//�ر���ƽ�е��߹̶�����Ĺ���
//		Chuizhi = 1;//����Ѱ��ֱ���ߵĹ���
//		if(y-Y > 0){  //Ŀ��λ����ǰ�ߣ���ǰ��
//			PS2_LY = 128;
//		}
//		if(y-Y < 0){ //Ŀ��λ���ں��棬�����
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
//	Pinxin = 1;//��������������ƽ��
//	Xunxian = 1;//�������߹̶�����
//	Chuizhi = 0;//�ر�Ѱ��ֱ���ߵĹ���
//	if(aim > 0){  //Ŀ��λ�����ұߣ�������
//		PS2_LX = aim;
//		delay_ms(time);
//	}
//	if(aim < 0){ //Ŀ��λ������ߣ�������
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
//	Pinxin = 1;//������������ƽ����ƽ��
//	Xunxian = 0;//�ر���ƽ�е��߹̶�����Ĺ���
//	Chuizhi = 1;//����Ѱ��ֱ���ߵĹ���
//	if(aim > 0){  //Ŀ��λ����ǰ�ߣ���ǰ��
//		PS2_LY = aim;
//		delay_ms(time);
//	}
//	if(aim < 0){ //Ŀ��λ���ں��棬�����
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
}        //��x�������ٶ�x�ƶ�time ms

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
//}       //��x�������ٶ�x�ƶ�count��

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
		
}        //��y�������ٶ�x�ƶ�time ms

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
}        //��y�������ٶ�x�ƶ�count��






