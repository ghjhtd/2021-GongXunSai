#include "encoder.h"
  /**************************************************************************
���ߣ�ƽ��С��֮��
�ҵ��Ա�С�꣺http://shop114407458.taobao.com/
**************************************************************************/

  /**************************************************************************
??:??????
??????:http://shop114407458.taobao.com/
**************************************************************************/
/**************************************************************************
????:?TIM2???????????
????:?
??  ?:?
**************************************************************************/
/**************************************************************************
�������ܣ���TIM2��ʼ��Ϊ�������ӿ�ģʽ
��ڲ�������
����  ֵ����
**************************************************************************/
void Encoder_Init_TIM1(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;  
  TIM_ICInitTypeDef TIM_ICInitStructure;  
  GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);// ��Ҫʹ��AFIOʱ��
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);//ʹ�ܶ�ʱ��2��ʱ��
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);//ʹ��PA�˿�ʱ��
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);//ʹ��PB�˿�ʱ��
 	GPIO_PinRemapConfig(GPIO_FullRemap_TIM1, ENABLE);//������ӳ��
 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;	//�˿�����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //��������
  GPIO_Init(GPIOE, &GPIO_InitStructure);					      //�����趨������ʼ��GPIOA
 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;	//�˿�����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //��������
  GPIO_Init(GPIOE, &GPIO_InitStructure);	
  
  TIM_DeInit(TIM1);

  TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
  TIM_TimeBaseStructure.TIM_Prescaler = 0x0; // Ԥ��Ƶ�� 
  TIM_TimeBaseStructure.TIM_Period = ENCODER_TIM_PERIOD; //�趨�������Զ���װֵ
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;//ѡ��ʱ�ӷ�Ƶ������Ƶ
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;////TIM���ϼ���  
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
  
	TIM_EncoderInterfaceConfig(TIM1, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);//ʹ�ñ�����ģʽ
  TIM_ICStructInit(&TIM_ICInitStructure);
  TIM_ICInitStructure.TIM_ICFilter = 10;
  TIM_ICInit(TIM1, &TIM_ICInitStructure);
  TIM_ClearFlag(TIM1, TIM_FLAG_Update);//���TIM�ĸ��±�־λ
  TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);
  //Reset counter
  TIM_SetCounter(TIM1,0);
  TIM_Cmd(TIM1, ENABLE); 
}
/**************************************************************************
�������ܣ���TIM3��ʼ��Ϊ�������ӿ�ģʽ
��ڲ�������
����  ֵ����
**************************************************************************/
void Encoder_Init_TIM3(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;  
  TIM_ICInitTypeDef TIM_ICInitStructure;  
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);//ʹ�ܶ�ʱ��3��ʱ��
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//ʹ��PA�˿�ʱ��
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;	//�˿�����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //��������
  GPIO_Init(GPIOA, &GPIO_InitStructure);					      //�����趨������ʼ��GPIOA
  
  TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
  TIM_TimeBaseStructure.TIM_Prescaler = 0x0; // Ԥ��Ƶ�� 
  TIM_TimeBaseStructure.TIM_Period = ENCODER_TIM_PERIOD; //�趨�������Զ���װֵ
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;//ѡ��ʱ�ӷ�Ƶ������Ƶ
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;////TIM���ϼ���  
  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
  TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);//ʹ�ñ�����ģʽ3
  TIM_ICStructInit(&TIM_ICInitStructure);
  TIM_ICInitStructure.TIM_ICFilter = 10;
  TIM_ICInit(TIM3, &TIM_ICInitStructure);
  TIM_ClearFlag(TIM3, TIM_FLAG_Update);//���TIM�ĸ��±�־λ
  TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
  //Reset counter
  TIM_SetCounter(TIM3,0);
  TIM_Cmd(TIM3, ENABLE); 
}

/**************************************************************************
�������ܣ���TIM4��ʼ��Ϊ�������ӿ�ģʽ
��ڲ�������
����  ֵ����
**************************************************************************/
void Encoder_Init_TIM4(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;  
  TIM_ICInitTypeDef TIM_ICInitStructure;  
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);//ʹ�ܶ�ʱ��4��ʱ��
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);//ʹ��PB�˿�ʱ��
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;	//�˿�����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //��������
  GPIO_Init(GPIOB, &GPIO_InitStructure);					      //�����趨������ʼ��GPIOB
  
  TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
  TIM_TimeBaseStructure.TIM_Prescaler = 0x0; // Ԥ��Ƶ�� 
  TIM_TimeBaseStructure.TIM_Period = ENCODER_TIM_PERIOD; //�趨�������Զ���װֵ
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;//ѡ��ʱ�ӷ�Ƶ������Ƶ
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;////TIM���ϼ���  
  TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
  TIM_EncoderInterfaceConfig(TIM4, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);//ʹ�ñ�����ģʽ3
  TIM_ICStructInit(&TIM_ICInitStructure);
  TIM_ICInitStructure.TIM_ICFilter = 10;
  TIM_ICInit(TIM4, &TIM_ICInitStructure);
  TIM_ClearFlag(TIM4, TIM_FLAG_Update);//���TIM�ĸ��±�־λ
  TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
  //Reset counter
  TIM_SetCounter(TIM4,0);
  TIM_Cmd(TIM4, ENABLE); 
}

/**************************************************************************
�������ܣ���TIM5��ʼ��Ϊ�������ӿ�ģʽ
��ڲ�������
����  ֵ����
**************************************************************************/
void Encoder_Init_TIM5(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;  
  TIM_ICInitTypeDef TIM_ICInitStructure;  
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);//ʹ�ܶ�ʱ����ʱ��
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//ʹ��PA�˿�ʱ��
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;	//�˿�����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //��������
  GPIO_Init(GPIOA, &GPIO_InitStructure);					      //�����趨������ʼ��GPIOA
  
  TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
  TIM_TimeBaseStructure.TIM_Prescaler = 0x0; // Ԥ��Ƶ�� 
  TIM_TimeBaseStructure.TIM_Period = ENCODER_TIM_PERIOD; //�趨�������Զ���װֵ
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;//ѡ��ʱ�ӷ�Ƶ������Ƶ
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;////TIM���ϼ���  
  TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);
  TIM_EncoderInterfaceConfig(TIM5, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);//ʹ�ñ�����ģʽ3
  TIM_ICStructInit(&TIM_ICInitStructure);
  TIM_ICInitStructure.TIM_ICFilter = 10;
  TIM_ICInit(TIM5, &TIM_ICInitStructure);
  TIM_ClearFlag(TIM5, TIM_FLAG_Update);//���TIM�ĸ��±�־λ
  TIM_ITConfig(TIM5, TIM_IT_Update, ENABLE);
  //Reset counter
  TIM_SetCounter(TIM5,0);
  TIM_Cmd(TIM5, ENABLE); 
}
/**************************************************************************
�������ܣ���λʱ���ȡ����������
��ڲ�������ʱ��
����  ֵ���ٶ�ֵ
**************************************************************************/
int Read_Encoder(u8 TIMX)
{
    int Encoder_TIM;    
   switch(TIMX)
	 {
	   case 1:  Encoder_TIM= (short)TIM1 -> CNT;   TIM1 -> CNT=0;  break;
		 case 3:  Encoder_TIM= (short)TIM3 -> CNT;   TIM3 -> CNT=0;  break;
		 case 4:  Encoder_TIM= (short)TIM4 -> CNT;   TIM4 -> CNT=0;  break;	
		 case 5:  Encoder_TIM= (short)TIM5 -> CNT;   TIM5 -> CNT=0;  break;	
		 default:  Encoder_TIM=0;
	 }
		return Encoder_TIM;
}
/**************************************************************************
�������ܣ�TIM2�жϷ�����
��ڲ�������
����  ֵ����
**************************************************************************/
void TIM1_IRQHandler(void)
{ 		    		  			    
	if(TIM1->SR&0X0001)//����ж�
	{    				   				     	    	
	}				   
	TIM1->SR&=~(1<<0);//����жϱ�־λ 	    
}

/**************************************************************************
�������ܣ�TIM3�жϷ�����
��ڲ�������
����  ֵ����
**************************************************************************/
void TIM3_IRQHandler(void)
{ 		    		  			    
	if(TIM3->SR&0X0001)//����ж�
	{    				   				     	    	
	}				   
	TIM3->SR&=~(1<<0);//����жϱ�־λ 	    
}
/**************************************************************************
�������ܣ�TIM4�жϷ�����
��ڲ�������
����  ֵ����
**************************************************************************/
void TIM4_IRQHandler(void)
{ 		    		  			    
	if(TIM4->SR&0X0001)//����ж�
	{    				   				     	    	
	}				   
	TIM4->SR&=~(1<<0);//����жϱ�־λ 	    
}

/**************************************************************************
�������ܣ�TIM4�жϷ�����
��ڲ�������
����  ֵ����
**************************************************************************/
void TIM5_IRQHandler(void)
{ 		    		  			    
	if(TIM5->SR&0X0001)//����ж�
	{    				   				     	    	
	}				   
	TIM5->SR&=~(1<<0);//����жϱ�־λ 	    
}


/**************************************************************************
�������ܣ���TIM2��ʼ��Ϊ�������ӿ�ģʽ
��ڲ�������
����  ֵ����
**************************************************************************/
/*void Encoder_Init_TIM2(void)
{
	RCC->APB1ENR|=1<<0;     //TIM2ʱ��ʹ��
	RCC->APB2ENR|=1<<2;    //ʹ��PORTAʱ��
	GPIOA->CRL&=0XFFFFFF00;//PA0 PA1
	GPIOA->CRL|=0X00000044;//��������
	/* �Ѷ�ʱ����ʼ��Ϊ������ģʽ */ 
//	TIM2->DIER|=1<<0;   //��������ж�				
//	TIM2->DIER|=1<<6;   //�������ж�
//	MY_NVIC_Init(1,3,TIM2_IRQn,1);

	/* Timer configuration in Encoder mode */ 
//	TIM2->PSC = 0x0;//Ԥ��Ƶ��
//	TIM2->ARR = ENCODER_TIM_PERIOD;//�趨�������Զ���װֵ 
//	TIM2->CR1 &=~(3<<8);// ѡ��ʱ�ӷ�Ƶ������Ƶ
//	TIM2->CR1 &=~(3<<5);// ѡ�����ģʽ:���ض���ģʽ
		
//	TIM2->CCMR1 |= 1<<0; //CC1S='01' IC1FP1ӳ�䵽TI1
//	TIM2->CCMR1 |= 1<<8; //CC2S='01' IC2FP2ӳ�䵽TI2
//	TIM2->CCER &= ~(1<<1);	 //CC1P='0'	 IC1FP1�����࣬IC1FP1=TI1
	//TIM2->CCER &= ~(1<<5);	 //CC2P='0'	 IC2FP2�����࣬IC2FP2=TI2
//	TIM2->CCMR1 |= 3<<4; //	IC1F='1000' ���벶��1�˲���
//	TIM2->SMCR |= 3<<0;	 //SMS='011' ���е�������������غ��½�����Ч
//	TIM2->CNT = 10000;
//	TIM2->CR1 |= 0x01;    //CEN=1��ʹ�ܶ�ʱ��
//}
/**************************************************************************
�������ܣ���TIM4��ʼ��Ϊ�������ӿ�ģʽ
��ڲ�������
����  ֵ����
**************************************************************************/
//void Encoder_Init_TIM4(void)
//{
//	NVIC_InitTypeDef NVIC_InitStructure;
//	
//	RCC->APB1ENR|=1<<2;     //TIM4ʱ��ʹ��
//	RCC->APB2ENR|=1<<3;     //ʹ��PORTBʱ��
//	GPIOB->CRL&=0X00FFFFFF; //PB6 PB7
//	GPIOB->CRL|=0X44000000; //��������
////	 �Ѷ�ʱ����ʼ��Ϊ������ģʽ */ 
////	TIM4->PSC = 0x0;//Ԥ��Ƶ��
////	TIM4->ARR = ENCODER_TIM_PERIOD-1;//�趨�������Զ���װֵ 
////  TIM4->CCMR1 |= 1<<0;          //����ģʽ��IC1FP1ӳ�䵽TI1��
////  TIM4->CCMR1 |= 1<<8;          //����ģʽ��IC2FP2ӳ�䵽TI2��
////  TIM4->CCER |= 0<<1;           //IC1������
////  TIM4->CCER |= 0<<5;           //IC2������
////	TIM4->SMCR |= 3<<0;	          //SMS='011' ���е�������������غ��½�����Ч
////	TIM4->CNT=10000;
////	TIM4->CR1 |= 0x01;            //CEN=1��ʹ�ܶ�ʱ��
//	
//		/* Enable the TIM3 Update Interrupt */
//	//����������Ҫͬʱ���òſ���ʹ���ж�
//	TIM4->DIER|=1<<0;   //��������ж�				
//	TIM4->DIER|=1<<6;   //�������ж�
//	//MY_NVIC_Init(1,3,TIM4_IRQn,1);
//  NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;  //TIM3�ж�
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  //��ռ���ȼ�0��
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //�����ȼ�3��
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
//	NVIC_Init(&NVIC_InitStructure);  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���
//	/* Timer configuration in Encoder mode */ 
//	TIM4->PSC = 0x0;//Ԥ��Ƶ��
//	TIM4->ARR = ENCODER_TIM_PERIOD;//�趨�������Զ���װֵ 
//	TIM4->CR1 &=~(3<<8);// ѡ��ʱ�ӷ�Ƶ������Ƶ
//	TIM4->CR1 &=~(3<<5);// ѡ�����ģʽ:���ض���ģʽ
//		
//	TIM4->CCMR1 |= 1<<0; //CC1S='01' IC1FP1ӳ�䵽TI1
//	TIM4->CCMR1 |= 1<<8; //CC2S='01' IC2FP2ӳ�䵽TI2
//	TIM4->CCER &= ~(1<<1);	 //CC1P='0'	 IC1FP1�����࣬IC1FP1=TI1
//	TIM4->CCER &= ~(1<<5);	 //CC2P='0'	 IC2FP2�����࣬IC2FP2=TI2
//	TIM4->CCMR1 |= 3<<4; //	IC1F='1000' ���벶��1�˲���
//	TIM4->SMCR |= 3<<0;	 //SMS='011' ���е�������������غ��½�����Ч
//	TIM4->CNT = 10000;
//	TIM4->CR1 |= 0x01;    //CEN=1��ʹ�ܶ�ʱ��
//}
///**************************************************************************
//�������ܣ���λʱ���ȡ����������
//��ڲ�������ʱ��
//����  ֵ���ٶ�ֵ
//**************************************************************************/
//int Read_Encoder(u8 TIMX)
//{
//    int Encoder_TIM;    
//   switch(TIMX)
//	 {
//	   case 2:  Encoder_TIM= (short)TIM2 -> CNT; break;
//		 case 3:  Encoder_TIM= (short)TIM3 -> CNT;  TIM3 -> CNT=0;break;	
//		 case 4:  Encoder_TIM= (short)TIM4 -> CNT;   /*TIM4 -> CNT=0;*/break;	
//		 default:  Encoder_TIM=0;
//	 }
//		return Encoder_TIM;
//}

//void TIM4_IRQHandler(void)
//{ 		    		  			    
//	if(TIM4->SR&0X0001)//����ж�
//	{
//			    				   				     	    	
//	}				   
//	TIM4->SR&=~(1<<0);//����жϱ�־λ 	    
//}
////void TIM2_IRQHandler(void)
////{ 		    		  			    
////	if(TIM2->SR&0X0001)//����ж�
//	//{
//			    				   				     	    	
////	}				   
////	TIM2->SR&=~(1<<0);//����жϱ�־λ 	    
////}
