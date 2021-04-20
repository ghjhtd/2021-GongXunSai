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
	 OLED_ShowNum(48,42,step,2,12);
	
	 OLED_ShowNum(0,42,CGQ[0],1,12);
	 OLED_ShowNum(6,42,CGQ[1],1,12);
		OLED_ShowNum(12,42,CGQ[2],1,12);
		OLED_ShowNum(18,42,CGQ[3],1,12);
		 OLED_ShowNum(24,42,CGQ[4],1,12);
		 OLED_ShowNum(30,42,CGQ[5],1,12);
	OLED_ShowNum(36,42,CGQ[6],1,12);
		OLED_ShowNum(0,0,num[1],1,40);
		OLED_ShowNum(20,0,num[2],1,40);
		OLED_ShowNum(40,0,num[3],1,40);
		OLED_ShowNum(68,0,num[5],1,40);
   	OLED_ShowNum(88,0,num[6],1,40);
			OLED_ShowNum(108,0,num[7],1,40);
	 OLED_Refresh();
//	 LCD_ShowxNum(240, 110,x,4,16,0);
//	 LCD_ShowxNum(372, 110,xaim,4,16,0);
//	 LCD_ShowxNum(240, 130,y,4,16,0);
//	 LCD_ShowxNum(372, 130,yaim,4,16,0);
//	 LCD_ShowxNum(232, 170,PWM0,4,16,0);
//	 LCD_ShowxNum(232, 190,PWM1,4,16,0);
	
	
//	LCD_ShowString(200,110,200,16,16,"adc1 0000  ");
//  LCD_ShowString(300,110,200,16,16,"adc1 AIM 0000");	
//	LCD_ShowString(200,130,200,16,16,"adc2 0000");
//  LCD_ShowString(300,130,200,16,16,"adc2 AIM 0000");	
//	LCD_ShowString(200,150,200,16,16,"KP  00   KI  00   KD  00");
//	LCD_ShowString(200,170,200,16,16,"PW0 00000 ");
//  LCD_ShowString(200,190,200,16,16,"PW1 00000 ");
//	LCD_ShowString(200,210,200,16,16,"PW2 00000 ")
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
////		DataScope_Get_Channel_Data( 0 , 4 );   
////		DataScope_Get_Channel_Data(0, 5 ); //用您要显示的数据替换0就行了
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

