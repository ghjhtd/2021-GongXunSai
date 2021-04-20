/*
 *     OLED显示器
 *              ----------------------------------------------------------------
 *              GND    电源地
 *              VCC  接5V或3.3v电源
 *              D0   接PG12（SCL）
 *              D1   接PD5（SDA）
 *              RES  接PD10
 *              DC   接PD15
 *              CS   接PD1
 *              ----------------------------------------------------------------
 *
 * 按键
 * #define KEY0 PEin(4)       //PE4
 * #define KEY1 PEin(3)	//PE3
 * #define KEY2 PEin(2)	//PE2  这个硬件没接 程序用了
 * #define WK_UP PAin(0)	//PA0  WK_UP
 *
 *
 *
 * LED
 * #define LED0 PBout(5)// PB5
 * #define LED1 PEout(5)// PE5
 * 点亮方式
 * LED0=0;   LED1=0;
 *
 *
 *
 * PWM输出
 * PC6，PC7,PC8,PC9
 * PWM定义方式
 * TIM3_PWM_Init( 8600, 8 ); /* PWM频率=72000000/16000=4.5Khz */
PWM输出方法
TIM_SetCompare1( TIM3, 100 );
TIM_SetCompare2( TIM3, 100 );
TIM_SetCompare3( TIM3, 100 );
TIM_SetCompare4( TIM3, 100 );

PID
**************************板子硬件连接
板间通讯 串口三
蓝牙 串口二

前循迹 串口三
左循迹 串口四
右循迹 串口五

**************************

OLED_Clear();
					OLED_ShowString(0, 0, "Press Key1 to start", 12,1);
					OLED_ShowString(0, 12, "Press Key0 to return", 12,1); 
					OLED_Refresh();	
					OLED_Clear();










*
* /