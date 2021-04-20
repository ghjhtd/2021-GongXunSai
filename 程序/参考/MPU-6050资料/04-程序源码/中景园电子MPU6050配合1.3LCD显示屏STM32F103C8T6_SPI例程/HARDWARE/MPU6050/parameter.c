#include "parameter.h"

short gyrox_offset=0,gyroy_offset=0,gyroz_offset=0;//x,y,z轴角速度偏移量
short aacx_offset=0,aacy_offset=0,aacz_offset=0;//x,y,z轴加速度偏移量
float pitch,roll,yaw; 		//欧拉角
short gyrox,gyroy,gyroz;	//陀螺仪原始数据
short aacx,aacy,aacz;		//加速度传感器原始数据

//欧拉角
//pitch:俯仰角  精度:0.1°   范围:-90.0° <---> +90.0°
//roll :横滚角  精度:0.1°   范围:-180.0°<---> +180.0°
//yaw  :航向角  精度:0.1°   范围:-180.0°<---> +180.0°
//注   :由于未连接磁力计，yaw（航向角）会发生漂移，读数不准确
void Show_EulerAngle(u8 x,u8 y,u8 size,u16 color)
{
	short temp;
	if(mpu_dmp_get_data(&pitch,&roll,&yaw)==0)//读取欧拉角
		{ 
			LCD_ShowString(x,y,"Pitch:",size,color);//显示俯仰角
			LCD_ShowString(x+size/2*10,y,".",size,color);
			LCD_ShowString(x+size/2*12,y,"C",size,color);
			LCD_ShowString(x,y+size,"Roll :",size,color);//显示横滚角
			LCD_ShowString(x+size/2*10,y+size,".",size,color);
			LCD_ShowString(x+size/2*12,y+size,"C",size,color);
			LCD_ShowString(x,y+size*2,"Yaw  :",size,color);//显示航向角
			LCD_ShowString(x+size/2*10,y+size*2,".",size,color);
			LCD_ShowString(x+size/2*12,y+size*2,"C",size,color);
			//显示pitch
			temp=pitch*10;//将pitch放大10倍
			if(temp<0)
			{
				LCD_ShowString(x+size/2*6,y,"-",size,color);//如果temp小于0，显示‘-’号
				temp=-temp;
			}
			else LCD_ShowString(x+size/2*6,y," ",size,color);
			LCD_ShowNum(x+size/2*7,y,temp/10,3,size,color);//显示整数部分
			LCD_ShowNum(x+size/2*11,y,temp%10,1,size,color);//显示小数部分
			//显示roll
			temp=roll*10;//将roll放大10倍
			if(temp<0)
			{
				LCD_ShowString(x+size/2*6,y+size,"-",size,color);//如果temp小于0，显示‘-’号
				temp=-temp;
			}
			else LCD_ShowString(x+size/2*6,y+size," ",size,color);
			LCD_ShowNum(x+size/2*7,y+size,temp/10,3,size,color);//显示整数部分
			LCD_ShowNum(x+size/2*11,y+size,temp%10,1,size,color);//显示小数部分
			//显示yaw
			temp=yaw*10;//将yaw放大10倍
			if(temp<0)
			{
				LCD_ShowString(x+size/2*6,y+size*2,"-",size,color);//如果temp小于0，显示‘-’号
				temp=-temp;
			}
			else LCD_ShowString(x+size/2*6,y+size*2," ",size,color);
			LCD_ShowNum(x+size/2*7,y+size*2,temp/10,3,size,color);//显示整数部分
			LCD_ShowNum(x+size/2*11,y+size*2,temp%10,1,size,color);//显示小数部分			
	}
}

//显示角速度
//gyrox:x轴角速度 精度:0.1。 范围:-2000.0 <---> +2000.0
//gyroy:y轴角速度 精度:0.1。 范围:-2000.0 <---> +2000.0
//gyroz:z轴角速度 精度:0.1。 范围:-2000.0 <---> +2000.0
void Show_Gyroscope(u8 x,u8 y,u8 size,u16 color)
{
	short temp;
	if(MPU_Get_Gyroscope(&gyrox,&gyroy,&gyroz)==0)
	{ 
		LCD_ShowString(x,y,"gyrox:",size,color);//显示x轴角速度rad/s
		LCD_ShowString(x+size/2*11,y,".",size,color);
		LCD_ShowString(x+size/2*13,y,"rad/s",size,color);
		LCD_ShowString(x,y+size,"gyroy:",size,color);//显示y轴角速度rad/s
		LCD_ShowString(x+size/2*11,y+size,".",size,color);
		LCD_ShowString(x+size/2*13,y+size,"rad/s",size,color);
		LCD_ShowString(x,y+size*2,"gyroz:",size,color);//显示z轴角速度rad/s
		LCD_ShowString(x+size/2*11,y+size*2,".",size,color);
		LCD_ShowString(x+size/2*13,y+size*2,"rad/s",size,color);

		//显示gyrox
		gyrox-=gyrox_offset;//偏移校正
		temp=10*gyrox*Gyro_Fsr/32768;
		if(temp<0)
		{
			LCD_ShowString(x+size/2*6,y,"-",size,color);//如果temp小于0，显示‘-’号
			temp=-temp;
		}
		else LCD_ShowString(x+size/2*6,y," ",size,color);
		LCD_ShowNum(x+size/2*7,y,temp/10,4,size,color);//显示整数部分
		LCD_ShowNum(x+size/2*12,y,temp%10,1,size,color);//显示小数部分
		
		//显示gyroy
		gyroy-=gyroy_offset;//偏移校正
		temp=10*gyroy*Gyro_Fsr/32768;
		if(temp<0)
		{
			LCD_ShowString(x+size/2*6,y+size,"-",size,color);//如果temp小于0，显示‘-’号
			temp=-temp;
		}
		else LCD_ShowString(x+size/2*6,y+size," ",size,color);
		LCD_ShowNum(x+size/2*7,y+size,temp/10,4,size,color);//显示整数部分
		LCD_ShowNum(x+size/2*12,y+size,temp%10,1,size,color);//显示小数部分
		
		//显示gyroz
		gyroz-=gyroz_offset;//偏移校正
		temp=10*gyroz*Gyro_Fsr/32768;
		if(temp<0)
		{
			LCD_ShowString(x+size/2*6,y+size*2,"-",size,color);//如果temp小于0，显示‘-’号
			temp=-temp;
		}
		else LCD_ShowString(x+size/2*6,y+size*2," ",size,color);
		LCD_ShowNum(x+size/2*7,y+size*2,temp/10,4,size,color);//显示整数部分
		LCD_ShowNum(x+size/2*12,y+size*2,temp%10,1,size,color);//显示小数部分			
 }
}

//显示加速度
//aacx:x轴加速度 精度:0.1。 范围:-2g <---> +2g
//aacy:y轴加速度 精度:0.1。 范围:-2g <---> +2g
//aacz:z轴加速度 精度:0.1。 范围:-2g <---> +2g
//g:重力加速度
void Show_Acceleration(u8 x,u8 y,u8 size,u16 color)
{
	short temp;
	if(MPU_Get_Accelerometer(&aacx,&aacy,&aacz)==0)
	{
		LCD_ShowString(x,y,"aacx:",size,color);//显示accx
		LCD_ShowString(x+size/2*9,y,".",size,color);
		LCD_ShowString(x+size/2*11,y,"m/s2",size,color);
		LCD_ShowString(x,y+size,"aacy:",size,color);//显示accy
		LCD_ShowString(x+size/2*9,y+size,".",size,color);
		LCD_ShowString(x+size/2*11,y+size,"m/s2",size,color);
		LCD_ShowString(x,y+size*2,"aacz:",size,color);//显示accz
		LCD_ShowString(x+size/2*9,y+size*2,".",size,color);
		LCD_ShowString(x+size/2*11,y+size*2,"m/s2",size,color);
		//显示accx
		aacx-=aacx_offset;//偏移校正
		temp=(float)10*Accel_G*Accel_Fsr*aacx/32768;
		if(temp<0)
		{
			temp=-temp;
			LCD_ShowString(x+size/2*5,y,"-",size,color);//如果temp小于0，显示‘-’号
		}
		else LCD_ShowString(x+size/2*5,y," ",size,color);
		LCD_ShowNum(x+size/2*6,y,temp/10,3,size,color);//显示整数部分
		LCD_ShowNum(x+size/2*10,y,temp%10,1,size,color);//显示小数部分
		//显示accy
		aacy-=aacy_offset;//偏移校正
		temp=(float)10*Accel_G*Accel_Fsr*aacy/32768;
		if(temp<0)
		{
			LCD_ShowString(x+size/2*5,y+size,"-",size,color);//如果temp小于0，显示‘-’号
			temp=-temp;
		}
		else LCD_ShowString(x+size/2*5,y+size," ",size,color);
		LCD_ShowNum(x+size/2*6,y+size,temp/10,3,size,color);//显示整数部分
		LCD_ShowNum(x+size/2*10,y+size,temp%10,1,size,color);//显示小数部分
		//显示accz
		aacz-=aacz_offset;//偏移校正
		temp=(float)10*Accel_G*Accel_Fsr*aacz/32768;
		if(temp<0)
		{
			LCD_ShowString(x+size/2*5,y+size*2,"-",size,color);//如果temp小于0，显示‘-’号
			temp=-temp;
		}
		else LCD_ShowString(x+size/2*5,y+size*2," ",size,color);
		LCD_ShowNum(x+size/2*6,y+size*2,temp/10,3,size,color);//显示整数部分
		LCD_ShowNum(x+size/2*10,y+size*2,temp%10,1,size,color);//显示小数部分			
		}
}

//显示温度
void Show_Temperture(u8 x,u8 y,u8 size,u16 color)
{
	short temp;
	temp=MPU_Get_Temperature();
	LCD_ShowString(x,y,"Temp :",size,color);
	LCD_ShowString(x+size/2*10,y,".",size,color);
	LCD_ShowString(x+size/2*12,y,"C",size,color);
	if(temp<0)
	{
		LCD_ShowString(x+size/2*6,y,"-",size,color);
		temp=-temp;
	}
	else LCD_ShowString(x+size/2*6,y," ",size,color);
	LCD_ShowNum(x+size/2*7,y,temp/100,3,size,color);
	LCD_ShowNum(x+size/2*11,y,temp%10,1,size,color);
}

//x,y,z轴角速度校准
u8 Gyroscope_Adjust1(void)
{
	u8 t=10;
	delay_ms(50);
	gyrox_offset=0;
	gyroy_offset=0;
	gyroz_offset=0;
	while(t--)
	{
		if(MPU_Get_Gyroscope(&gyrox,&gyroy,&gyroz)==0)
		{
			gyrox_offset+=gyrox;//连续读取10个x轴角速度值
			gyroy_offset+=gyroy;//连续读取10个y轴角速度值
			gyroz_offset+=gyroz;//连续读取10个z轴角速度值
			delay_ms(10);
		}
	}
	gyrox_offset/=10;//取平均值
	gyroy_offset/=10;//取平均值
	gyroz_offset/=10;//取平均值
	
	if(MPU_Get_Gyroscope(&gyrox,&gyroy,&gyroz)==0)
	{
		if((gyrox_offset-gyrox)>-5 && (gyrox_offset-gyrox)<5 &&
			 (gyroy_offset-gyroy)>-5 && (gyroy_offset-gyroy)<5 && 
		   (gyroz_offset-gyroz)>-5 && (gyroz_offset-gyroz)<5) return 0;
		else return 1;
	}
}


u8 Acceleration_Adjust1(void)
{
	short t=10;
	short m=50;
	delay_ms(50);
	aacx_offset=0;
	aacy_offset=0;
	aacz_offset=0;
	while(t--)
	{
		if(MPU_Get_Accelerometer(&aacx,&aacy,&aacz)==0)
		{
			aacx_offset+=aacx/10;//连续读取10个x轴加速度值
			aacy_offset+=aacy/10;//连续读取10个y轴加速度值
			//水平放置时任何时候z轴都有重力加速度，所以计算偏移量的时候需要减去一个重力加速度的值
			aacz-=16384;
			aacz_offset+=aacz/10;//连续读取10个z轴加速度值
			delay_ms(10);
		}
	}
	if(MPU_Get_Accelerometer(&aacx,&aacy,&aacz)==0)
	{
		aacz-=16384;
		if(((aacx_offset-aacx)>-m && (aacx_offset-aacx)<m) && 
			((aacy_offset-aacy)>-m && (aacy_offset-aacy)<m) && 
		((aacz_offset-aacz)>-m && (aacz_offset-aacz)<m)) 
		return 0;
			else return 1;
	}
}


//初始化MPU6050以及检测MPU6050是否连接
void Connect_Check(void)
{
	while(mpu_dmp_init())
	{
		LCD_ShowString(60,35,"MPU6050 Connect   ",16,RED);
		delay_ms(200);
		LCD_ShowString(60,35,"MPU6050 Connect.  ",16,RED);
		delay_ms(200);
		LCD_ShowString(60,35,"MPU6050 Connect.. ",16,RED);
		delay_ms(200);
		LCD_ShowString(60,35,"MPU6050 Connect...",16,RED);
		delay_ms(200);
	}
	  LCD_ShowString(60,35,"MPU6050 is OK!    ",16,RED);
	  delay_ms(400);
}

//加速度传感器校准界面
void Acceleration_Adjust(void)
{
	while(Acceleration_Adjust1())
	{
		LCD_ShowString(60,51,"Accel Adjust   ",16,RED);
		delay_ms(200);
		LCD_ShowString(60,51,"Accel Adjust.  ",16,RED);
		delay_ms(200);
		LCD_ShowString(60,51,"Accel Adjust.. ",16,RED);
		delay_ms(200);
		LCD_ShowString(60,51,"Accel Adjust...",16,RED);
		delay_ms(200);
	}
	  LCD_ShowString(60,51,"Accel is OK!   ",16,RED);
	  delay_ms(400);
}

//陀螺仪校准界面
void Gyroscope_Adjust(void)
{
	while(Gyroscope_Adjust1())
	{
		LCD_ShowString(60,67,"Gyros Adjust   ",16,RED);
		delay_ms(200);
		LCD_ShowString(60,67,"Gyros Adjust.  ",16,RED);
		delay_ms(200);
		LCD_ShowString(60,67,"Gyros Adjust.. ",16,RED);
		delay_ms(200);
		LCD_ShowString(60,67,"Gyros Adjust...",16,RED);
		delay_ms(200);
	}
	  LCD_ShowString(60,67,"Gyros is OK!   ",16,RED);
}



