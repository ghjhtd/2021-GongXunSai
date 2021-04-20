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
	 //OLED_Clear();
	OLED_Str_Next(&x,&y,"SVO0",12,&len_last,&size_last);
	OLED_Num_Next(&x,&y,servo[0][SET_ANGLE],3,12,&len_last,&size_last);
  OLED_Str_Next(&x,&y,"SVO1",12,&len_last,&size_last);
	OLED_Num_Next(&x,&y,servo[1][SET_ANGLE],3,12,&len_last,&size_last);
	OLED_Str_Next(&x,&y,"SVO2",12,&len_last,&size_last);
	OLED_Num_Next(&x,&y,servo[2][SET_ANGLE],3,12,&len_last,&size_last);
	OLED_Str_Next(&x,&y,"SVO3",12,&len_last,&size_last);
	OLED_Num_Next(&x,&y,servo[3][SET_ANGLE],3,12,&len_last,&size_last);
	OLED_Str_Next(&x,&y,"SVO4",12,&len_last,&size_last);
	OLED_Num_Next(&x,&y,servo[4][SET_ANGLE],3,12,&len_last,&size_last);
	OLED_Str_Next(&x,&y,"SVO5",12,&len_last,&size_last);
	OLED_Num_Next(&x,&y,servo[5][SET_ANGLE],3,12,&len_last,&size_last);
	OLED_Str_Newline(&x,&y,"S",12,&len_last,&size_last);
	OLED_Str_Next(&x,&y,COMMAND,12,&len_last,&size_last);
	 OLED_Refresh();

}

void openmv(void)
{
u8 x=0,y=12;
	u8 size_last=0;
	u8 len_last=0;
	OLED_Num_Next(&x,&y,test_usart,3,12,&len_last,&size_last);
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
		 OLED_ShowString(*px, *py, " ", size1 ); 
		 OLED_ShowNum(*px+size1/2,*py,num,len,size1);
	 }
	 else
	 {
		OLED_ShowString(*px, *py, "-", size1 ); 
		 OLED_ShowNum(*px+size1/2,*py,-num,len,size1);
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
		 OLED_ShowString(*px, *py, " ", size1 ); 
		 OLED_ShowNum(*px+size1/2,*py,num,len,size1);
	 }
	 else
	 {
		OLED_ShowString(*px, *py, "-", size1 ); 
		 OLED_ShowNum(*px+size1/2,*py,-num,len,size1);
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
	 OLED_ShowString(*px, *py,(u8*)chr, size1 );
	 *len_last=strlen(chr);
	 *size_last=size1;
 }
//oled换行显示字符串
 void OLED_Str_Newline(u8* px,u8* py,char* chr,u8 size1,u8*len_last,u8*size_last)
 {
	  *px=0;
	  (*py)+=*size_last;
	 OLED_ShowString(*px, *py,(u8*)chr, size1 );
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
//		DataScope_Get_Channel_Data( x, 1 );      
//		DataScope_Get_Channel_Data( y, 2 );         
//		DataScope_Get_Channel_Data( 0, 3 );              
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

