#include "show.h"
#include "DataScope_DP.h"
  /**************************************************************************
作者：平衡小车之家
我的淘宝小店：http://shop114407458.taobao.com/
**************************************************************************/
unsigned char i,temp;          //计数变量
unsigned char Send_Cout; //串口需要发送的数据个数
float Vol;
 
 extern float Angle_Balance;
 extern int Encoder;
 
/**************************************************************************
函数功能：OLED显示
入口参数：无
返回  值：无
**************************************************************************/
void lcd_show(void)
{
u8 x=0,y=12;
	u8 size_last=0;
	u8 len_last=0;

//	OLED_Str_Next(&x,&y,"ENC1",12,&len_last,&size_last);
//	OLED_Num_Next(&x,&y,Encoder1,3,12,&len_last,&size_last);
//	OLED_Str_Next(&x,&y,"ENC2",12,&len_last,&size_last);
//	OLED_Num_Next(&x,&y,Encoder2,3,12,&len_last,&size_last);
//	OLED_Str_Newline(&x,&y,"ENC3",12,&len_last,&size_last);
//	OLED_Num_Next(&x,&y,Encoder3,3,12,&len_last,&size_last);
//	OLED_Str_Next(&x,&y,"ENC4",12,&len_last,&size_last);
//	OLED_Num_Next(&x,&y,Encoder4,3,12,&len_last,&size_last);
	OLED_Num_Next(&x,&y,pwm1,4,12,&len_last,&size_last);
	OLED_Num_Next(&x,&y,pwm2,4,12,&len_last,&size_last);
	OLED_Num_Next(&x,&y,pwm3,4,12,&len_last,&size_last);
	OLED_Num_Next(&x,&y,pwm4,4,12,&len_last,&size_last);
	 OLED_Refresh();

}

void pid_show(void)
{
  u8 x=0,y=12;
	u8 size_last=0;
	u8 len_last=0;
	OLED_Clear();
	OLED_Str_Next(&x,&y,"KP",12,&len_last,&size_last);
	OLED_Num_Next(&x,&y,Velocity_KP,5,12,&len_last,&size_last);
	OLED_Str_Next(&x,&y,"KI",12,&len_last,&size_last);
	OLED_Num_Next(&x,&y,Velocity_KI,5,12,&len_last,&size_last);
	
	OLED_Refresh();
}
void key_show(void)
{
  u8 x=0,y=12;
	u8 size_last=0;
	u8 len_last=0;
	OLED_Clear();
	OLED_Str_Next(&x,&y,"KEY",12,&len_last,&size_last);
	OLED_Num_Next(&x,&y,key,5,12,&len_last,&size_last);

	
	OLED_Refresh();
}

void xy_show(void)
{
  u8 x=0,y=12;
	u8 size_last=0;
	u8 len_last=0;
	OLED_Clear();
	OLED_Str_Next(&x,&y,"X",12,&len_last,&size_last);
	OLED_Num_Next(&x,&y,X,5,12,&len_last,&size_last);
	OLED_Str_Next(&x,&y,"Y",12,&len_last,&size_last);
	OLED_Num_Next(&x,&y,Y,5,12,&len_last,&size_last);
	OLED_Str_Next(&x,&y,"temp",12,&len_last,&size_last);
	OLED_Num_Next(&x,&y,temp_Dot,5,12,&len_last,&size_last);
	OLED_Refresh();
}

void xunji_show(void)
{
	u8 x=0,y=12;
	u8 size_last=0;
	u8 len_last=0;
  OLED_Clear();
	OLED_Str_Next(&x,&y,"Left",12,&len_last,&size_last);
	OLED_Num_Next(&x,&y,zuo,5,12,&len_last,&size_last);
	OLED_Str_Next(&x,&y,"Right",12,&len_last,&size_last);
	OLED_Num_Next(&x,&y,you,5,12,&len_last,&size_last);
	OLED_Str_Next(&x,&y,"Front",12,&len_last,&size_last);
	OLED_Num_Next(&x,&y,qian,5,12,&len_last,&size_last);
	OLED_Str_Next(&x,&y,"tempY1",12,&len_last,&size_last);
	OLED_Num_Next(&x,&y,tempY1,5,12,&len_last,&size_last);

	OLED_Str_Next(&x,&y,"temp",12,&len_last,&size_last);
	OLED_Num_Next(&x,&y,temp_Dot,5,12,&len_last,&size_last);
	
//	OLED_Str_Next(&x,&y,"temp_Turn",12,&len_last,&size_last);
//	OLED_Num_Next(&x,&y,temp_Turn,5,12,&len_last,&size_last);
//	OLED_Str_Next(&x,&y,"temp_Sudu",12,&len_last,&size_last);
//	OLED_Num_Next(&x,&y,temp_Sudu,5,12,&len_last,&size_last);
//	OLED_Str_Newline(&x,&y,"right",12,&len_last,&size_last);
//	OLED_Num_Next(&x,&y,you,5,12,&len_last,&size_last);
//	OLED_Str_Newline(&x,&y,"qian",12,&len_last,&size_last);
//	OLED_Num_Next(&x,&y,qian,5,12,&len_last,&size_last);
//	OLED_Str_Newline(&x,&y,YOU,12,&len_last,&size_last);
//	OLED_Str_Newline(&x,&y,ZUO,12,&len_last,&size_last);
//	OLED_Num_Next(&x,&y,zuo,5,12,&len_last,&size_last);
//	OLED_Str_Newline(&x,&y,"ENC3",12,&len_last,&size_last);
//	OLED_Num_Next(&x,&y,Encoder3,3,12,&len_last,&size_last);
//	OLED_Str_Next(&x,&y,"ENC4",12,&len_last,&size_last);
//	OLED_Num_Next(&x,&y,Encoder4,3,12,&len_last,&size_last);
//	OLED_Num_Next(&x,&y,pwm1,4,12,&len_last,&size_last);
//	OLED_Num_Next(&x,&y,pwm2,4,12,&len_last,&size_last);
//	OLED_Num_Next(&x,&y,pwm3,4,12,&len_last,&size_last);
//	OLED_Num_Next(&x,&y,pwm4,4,12,&len_last,&size_last);
	 OLED_Refresh();

//	
//	OLED_ShowString( 0, 0, "left:", 12,1); 
//	OLED_ShowNum(30,0,zuo,5,12,1);
//	OLED_ShowString( 0, 20, "Right:", 12,1); 
//	OLED_ShowNum(30,20,you,5,12,1);
//	OLED_Refresh();
}

void xunjiY_show(void)
{
	u8 x=0,y=12;
	u8 size_last=0;
	u8 len_last=0;
  OLED_Clear();
	OLED_Str_Next(&x,&y,"Left",12,&len_last,&size_last);
	OLED_Num_Next(&x,&y,zuo,5,12,&len_last,&size_last);
	OLED_Str_Next(&x,&y,"Right",12,&len_last,&size_last);
	OLED_Num_Next(&x,&y,you,5,12,&len_last,&size_last);
	OLED_Str_Next(&x,&y,"Front",12,&len_last,&size_last);
	OLED_Num_Next(&x,&y,qian,5,12,&len_last,&size_last);
	OLED_Str_Next(&x,&y,"Mode",12,&len_last,&size_last);
	OLED_Num_Next(&x,&y,Mode,5,12,&len_last,&size_last);

	OLED_Str_Next(&x,&y,"temp",12,&len_last,&size_last);
	OLED_Num_Next(&x,&y,temp_DotY,5,12,&len_last,&size_last);
	
	 OLED_Refresh();

}

void usart_show(void)
{
	u8 x=0,y=12;
	u8 size_last=0;
	u8 len_last=0;
  OLED_Clear();
	OLED_Str_Next(&x,&y,"UART1:",12,&len_last,&size_last);
	OLED_Num_Next(&x,&y,uart_show,5,12,&len_last,&size_last);
	 OLED_Refresh();

}

//oled同行显示有符号整数
void OLED_Num_Next(u8* px,u8* py,int num,u8 len,u8 size1,u8*len_last,u8*size_last)
{
	 *px=*px+(*len_last)*(*size_last/2);
	 if(*px+(len*size1)>128)
	 {
		 *px=0;
		 (*py)+=*size_last;
	 }
	 if(num>=0)
	 {
		 OLED_ShowString(*px, *py, " ", size1,1); 
		 OLED_ShowNum(*px+size1/2,*py,num,len,size1,1);
	 }
	 else
	 {
		OLED_ShowString(*px, *py, "-", size1,1); 
		 OLED_ShowNum(*px+size1/2,*py,-num,len,size1,1);
	 }
	 *len_last=len+1;
	 *size_last=size1;
	 
}
//oled换行显示有符号整数
void OLED_Num_Newline(u8* px,u8* py,int num,u8 len,u8 size1,u8*len_last,u8*size_last)
{
	 *px=0;
	 (*py)+=*size_last;
	 if(num>=0)
	 {
		 OLED_ShowString(*px, *py, " ", size1,1); 
		 OLED_ShowNum(*px+size1/2,*py,num,len,size1,1);
	 }
	 else
	 {
		OLED_ShowString(*px, *py, "-", size1,1); 
		 OLED_ShowNum(*px+size1/2,*py,-num,len,size1,1);
	 }
	 *len_last=len+1;
	 *size_last=size1;
 }
//oled同行显示字符串
 void OLED_Str_Next(u8* px,u8* py,char* chr,u8 size1,u8*len_last,u8*size_last)
 {
	 *px=*px+(*len_last+1)*(*size_last/2);
	  if(*px+(strlen(chr)*size1)>128)
	 {
		 *px=0;
		 (*py)+=*size_last;
	 }
	 OLED_ShowString(*px, *py,(u8*)chr, size1,0);
	 *len_last=strlen(chr);
	 *size_last=size1;
 }
//oled换行显示字符串
 void OLED_Str_Newline(u8* px,u8* py,char* chr,u8 size1,u8*len_last,u8*size_last)
 {
	  *px=0;
	  (*py)+=*size_last;
	 OLED_ShowString(*px, *py,(u8*)chr, size1,1);
	 *len_last=strlen(chr);
	 *size_last=size1;
 }

/**************************************************************************
函数功能：虚拟示波器往上位机发送数据 关闭显示屏
入口参数：无
返回  值：无
作    者：平衡小车之家
**************************************************************************/
void DataScope(void)
{   
		DataScope_Get_Channel_Data( x, 1 );      
		DataScope_Get_Channel_Data( y, 2 );         
		DataScope_Get_Channel_Data( 0, 3 );              
//		DataScope_Get_Channel_Data( 0 , 4 );   
//		DataScope_Get_Channel_Data(0, 5 ); //用您要显示的数据替换0就行了
//		DataScope_Get_Channel_Data(0 , 6 );//用您要显示的数据替换0就行了
//		DataScope_Get_Channel_Data(0, 7 );
//		DataScope_Get_Channel_Data( 0, 8 ); 
//		DataScope_Get_Channel_Data(0, 9 );  
//		DataScope_Get_Channel_Data( 0 , 10);
		Send_Cout = DataScope_Data_Generate(3);
		for( i = 0 ; i < Send_Cout; i++) 
		{
		while((USART1->SR&0X40)==0);  
		USART1->DR = DataScope_OutPut_Buffer[i]; 
		}
		
}

