#ifndef __SYS_H
#define __SYS_H	  
#include <stm32f10x.h>   
 /**************************************************************************
���ߣ�ƽ��С��֮�� 
�Ա����̣�http://shop114407458.taobao.com/
**************************************************************************/
//0,��֧��ucos
//1,֧��ucos
#define SYSTEM_SUPPORT_UCOS		0		//����ϵͳ�ļ����Ƿ�֧��UCOS
																	    
	 
//λ������,ʵ��51���Ƶ�GPIO���ƹ���
//����ʵ��˼��,�ο�<<CM3Ȩ��ָ��>>������(87ҳ~92ҳ).
//IO�ڲ����궨��
#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2)) 
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr)) 
#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum)) 
//IO�ڵ�ַӳ��
#define GPIOA_ODR_Addr    (GPIOA_BASE+12) //0x4001080C 
#define GPIOB_ODR_Addr    (GPIOB_BASE+12) //0x40010C0C 
#define GPIOC_ODR_Addr    (GPIOC_BASE+12) //0x4001100C 
#define GPIOD_ODR_Addr    (GPIOD_BASE+12) //0x4001140C 
#define GPIOE_ODR_Addr    (GPIOE_BASE+12) //0x4001180C 
#define GPIOF_ODR_Addr    (GPIOF_BASE+12) //0x40011A0C    
#define GPIOG_ODR_Addr    (GPIOG_BASE+12) //0x40011E0C    

#define GPIOA_IDR_Addr    (GPIOA_BASE+8) //0x40010808 
#define GPIOB_IDR_Addr    (GPIOB_BASE+8) //0x40010C08 
#define GPIOC_IDR_Addr    (GPIOC_BASE+8) //0x40011008 
#define GPIOD_IDR_Addr    (GPIOD_BASE+8) //0x40011408 
#define GPIOE_IDR_Addr    (GPIOE_BASE+8) //0x40011808 
#define GPIOF_IDR_Addr    (GPIOF_BASE+8) //0x40011A08 
#define GPIOG_IDR_Addr    (GPIOG_BASE+8) //0x40011E08 
 
//IO�ڲ���,ֻ�Ե�һ��IO��!
//ȷ��n��ֵС��16!
#define PAout(n)   BIT_ADDR(GPIOA_ODR_Addr,n)  //��� 
#define PAin(n)    BIT_ADDR(GPIOA_IDR_Addr,n)  //���� 

#define PBout(n)   BIT_ADDR(GPIOB_ODR_Addr,n)  //��� 
#define PBin(n)    BIT_ADDR(GPIOB_IDR_Addr,n)  //���� 

#define PCout(n)   BIT_ADDR(GPIOC_ODR_Addr,n)  //��� 
#define PCin(n)    BIT_ADDR(GPIOC_IDR_Addr,n)  //���� 

#define PDout(n)   BIT_ADDR(GPIOD_ODR_Addr,n)  //��� 
#define PDin(n)    BIT_ADDR(GPIOD_IDR_Addr,n)  //���� 

#define PEout(n)   BIT_ADDR(GPIOE_ODR_Addr,n)  //��� 
#define PEin(n)    BIT_ADDR(GPIOE_IDR_Addr,n)  //����

#define PFout(n)   BIT_ADDR(GPIOF_ODR_Addr,n)  //��� 
#define PFin(n)    BIT_ADDR(GPIOF_IDR_Addr,n)  //����

#define PGout(n)   BIT_ADDR(GPIOG_ODR_Addr,n)  //��� 
#define PGin(n)    BIT_ADDR(GPIOG_IDR_Addr,n)  //����
/////////////////////////////////////////////////////////////////
//Ex_NVIC_Configר�ö���
#define GPIO_A 0
#define GPIO_B 1
#define GPIO_C 2
#define GPIO_D 3
#define GPIO_E 4
#define GPIO_F 5
#define GPIO_G 6 

#define FTIR   1  //�½��ش���
#define RTIR   2  //�����ش���
#include <math.h>
#include "delay.h"
#include "led.h"
#include "key.h"
#include "oled.h"
#include "usart.h"
#include "pstwo.h"
#include "mpu6050.h"
#include "inv_mpu_dmp_motion_driver.h"
#include "inv_mpu.h"
#include "ioi2c.h"
#include "dmpKey.h"
#include "dmpmap.h"

#include "timer.h"
#include "encoder.h"
#include "show.h"								   
#include "DataScope_DP.h"

//JTAGģʽ���ö���
#define JTAG_SWD_DISABLE   0X02
#define SWD_ENABLE         0X01
#define JTAG_SWD_ENABLE    0X00	                                     

extern u8 Flag_Stop,delay_50,delay_flag,uart_show;         //ֹͣ��־λ 50ms��׼��ʾ��־λ(��λ��ʹ��)
extern int Position_Zero;            //���������������
extern int key;                                  //���PWM���� Ӧ��Motor�� ��Moto�¾�	
extern int Voltage;                                //��ص�ѹ������صı���
                                                   //��λ�ƴ���������
extern float Balance_KP, Balance_KI,Balance_KD,Position_KP,Position_KD;  //PIDϵ��
extern float Pitch,Roll,Yaw;                                     
extern	int pwm1,pwm2,pwm3,pwm4;
extern int usart_flag;
extern u8 RX_BUF[15],RX_CNT,look_count;  //����ͷ����ͨѶ����洢
extern float angle_dangqian,angle_aim;
extern int x,y,r,length,yaim;
extern int Encoder1,Encoder2,Encoder3,Encoder4;
extern volatile u16 ADCConvertedValue[10][3];   //adcͨ����ֵ
extern char YOU[30];
extern char ZUO[30];
extern char QIAN[30];
extern float Velocity_KP,Velocity_KI;
extern int PS2_LX,PS2_LY,PS2_RX,PS2_RY,PS2_KEY,PS2_KEY2,TURN;
extern int AIM_max;//�ٶȵ�λ

extern int volatile qian,zuo,you,Xunxian,Pinxin,Juli,Chuizhi;
extern int X,Y;   //С���ڵ�ͼ�ϵĶ�λ���꣬��ͼ���½ǵ�������0��0
extern int threshold;   //Ѳ����ֵ
extern int Mode;
extern int num[8],num_cnt,cishu_flag;
extern int bias,temp_Dot,tempY1,temp_Turn,jishu_shineng,temp_Sudu,count_Jishu,count_Biaozhi,count_JishuY,count_BiaozhiY,temp_DotY,tempY2;

extern u8 MOVEX_ENABLE,MOVEY_ENABLE,TURNLEFT_ENABLE,TURNRIGTH_ENABLE;
extern int X_SUDU,X_COUNT,X_ZHONGZHI;
extern int Y_SUDU,Y_COUNT,Y_ZHONGZHI;
extern int COLOR[];
extern char NUM[30];
extern int count_saoma, count_look;

/////////////////////////////////////////////////////////////////  
void Stm32_Clock_Init(u8 PLL);  //ʱ�ӳ�ʼ��  
void Sys_Soft_Reset(void);      //ϵͳ��λ
void Sys_Standby(void);         //����ģʽ 	
void MY_NVIC_SetVectorTable(u32 NVIC_VectTab, u32 Offset);//����ƫ�Ƶ�ַ
void MY_NVIC_PriorityGroupConfig(u8 NVIC_Group);//����NVIC����
void MY_NVIC_Init(u8 NVIC_PreemptionPriority,u8 NVIC_SubPriority,u8 NVIC_Channel,u8 NVIC_Group);//�����ж�
void Ex_NVIC_Config(u8 GPIOx,u8 BITx,u8 TRIM);//�ⲿ�ж����ú���(ֻ��GPIOA~G)
void JTAG_Set(u8 mode);
//////////////////////////////////////////////////////////////////////////////
//����Ϊ��ຯ��
void WFI_SET(void);		//ִ��WFIָ��
void INTX_DISABLE(void);//�ر������ж�
void INTX_ENABLE(void);	//���������ж�
void MSR_MSP(u32 addr);	//���ö�ջ��ַ
#endif











