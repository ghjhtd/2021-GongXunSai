#include "control.h"		
  /**************************************************************************
���ߣ�ƽ��С��֮��
�ҵ��Ա�С�꣺http://shop114407458.taobao.com/
**************************************************************************/
int pwm0,pwm1;

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
��ڲ�����PWM
����  ֵ����
**************************************************************************/
//void Set_Pwm(int moto)
//{
//    	if(moto<0)			AIN2=1,			AIN1=0;
//			else 	          AIN2=0,			AIN1=1;
//			PWMA=myabs(moto);
//}

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
