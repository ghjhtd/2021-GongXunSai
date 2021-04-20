#include "parameter.h"

short gyrox_offset=0,gyroy_offset=0,gyroz_offset=0;//x,y,z轴角速度偏移量
short aacx_offset=0,aacy_offset=0,aacz_offset=0;//x,y,z轴加速度偏移量
float pitch,roll,yaw; 		//欧拉角
short gyrox,gyroy,gyroz;	//陀螺仪原始数据
short aacx,aacy,aacz;		//加速度传感器原始数据

//显示角速度
//gyrox:x轴角速度 精度:0.1。 范围:-2000.0 <---> +2000.0
//gyroy:y轴角速度 精度:0.1。 范围:-2000.0 <---> +2000.0
//gyroz:z轴角速度 精度:0.1。 范围:-2000.0 <---> +2000.0
void Show_Gyroscope(void)
{
	short temp;
	if(MPU_Get_Gyroscope(&gyrox,&gyroy,&gyroz)==0)
	{ 
		OLED_ShowString(0,2,"gyrox:",16);//显示x轴角速度rad/s
		OLED_ShowString(88,2,".",16);
		OLED_ShowString(0,4,"gyroy:",16);//显示y轴角速度rad/s
		OLED_ShowString(88,4,".",16);
		OLED_ShowString(0,6,"gyroz:",16);//显示z轴角速度rad/s
		OLED_ShowString(88,6,".",16);

		//显示gyrox
		gyrox-=gyrox_offset;//偏移校正
		temp=(float)10*gyrox*Gyro_Fsr/32768;
		if(temp<0)
		{
			OLED_ShowString(48,2,"-",16);//如果temp小于0，显示‘-’号
			temp=-temp;
		}
		else OLED_ShowString(48,2," ",16);
		OLED_ShowNum(56,2,temp/10,4,16);//显示整数部分
		OLED_ShowNum(96,2,temp%10,1,16);//显示小数部分
		
		//显示gyroy
		gyroy-=gyroy_offset;//偏移校正
		temp=(float)10*gyroy*Gyro_Fsr/32768;
		if(temp<0)
		{
			OLED_ShowString(48,4,"-",16);//如果temp小于0，显示‘-’号
			temp=-temp;
		}
		else OLED_ShowString(48,4," ",16);
		OLED_ShowNum(56,4,temp/10,4,16);//显示整数部分
		OLED_ShowNum(96,4,temp%10,1,16);//显示小数部分
		
		//显示gyroz
		gyroz-=gyroz_offset;//偏移校正
		temp=(float)10*gyroz*Gyro_Fsr/32768;
		if(temp<0)
		{
			OLED_ShowString(48,6,"-",16);//如果temp小于0，显示‘-’号
			temp=-temp;
		}
		else OLED_ShowString(48,6," ",16);
		OLED_ShowNum(56,6,temp/10,4,16);//显示整数部分
		OLED_ShowNum(96,6,temp%10,1,16);//显示小数部分			
	delay_ms(200);
 }
}

//显示加速度
//aacx:x轴加速度 精度:0.1。 范围:-2g <---> +2g
//aacy:y轴加速度 精度:0.1。 范围:-2g <---> +2g
//aacz:z轴加速度 精度:0.1。 范围:-2g <---> +2g
//g:重力加速度
void Show_Acceleration(void)
{
	short temp;
	if(MPU_Get_Accelerometer(&aacx,&aacy,&aacz)==0)
	{
		OLED_ShowString(0,2,"aacx:",16);//显示accx
		OLED_ShowString(72,2,".",16);
		OLED_ShowString(88,2,"m/s2",16);
		OLED_ShowString(0,4,"aacy:",16);//显示accy
		OLED_ShowString(72,4,".",16);
		OLED_ShowString(88,4,"m/s2",16);
		OLED_ShowString(0,6,"aacz:",16);//显示accz
		OLED_ShowString(72,6,".",16);
		OLED_ShowString(88,6,"m/s2",16);
		//显示accx
		aacx-=aacx_offset;//偏移校正
		temp=(float)10*Accel_G*Accel_Fsr*aacx/32768;
		if(temp<0)
		{
			temp=-temp;
			OLED_ShowString(40,2,"-",16);//如果temp小于0，显示‘-’号
		}
		else OLED_ShowString(40,2," ",16);
		OLED_ShowNum(48,2,temp/10,3,16);//显示整数部分
		OLED_ShowNum(80,2,temp%10,1,16);//显示小数部分
		//显示accy
		aacy-=aacy_offset;//偏移校正
		temp=(float)10*Accel_G*Accel_Fsr*aacy/32768;
		if(temp<0)
		{
			OLED_ShowString(40,4,"-",16);//如果temp小于0，显示‘-’号
			temp=-temp;
		}
		else OLED_ShowString(40,4," ",16);
		OLED_ShowNum(48,4,temp/10,3,16);//显示整数部分
		OLED_ShowNum(80,4,temp%10,1,16);//显示小数部分
		//显示accz
		aacz-=aacz_offset;//偏移校正
		temp=(float)10*Accel_G*Accel_Fsr*aacz/32768;
		if(temp<0)
		{
			OLED_ShowString(40,6,"-",16);//如果temp小于0，显示‘-’号
			temp=-temp;
		}
		else OLED_ShowString(40,6," ",16);
		OLED_ShowNum(48,6,temp/10,3,16);//显示整数部分
		OLED_ShowNum(80,6,temp%10,1,16);//显示小数部分			
		}
}

//显示温度
void Show_Temperture(u8 x,u8 y,u8 size1)
{
	short temp;
	temp=MPU_Get_Temperature();
	OLED_ShowString(x,y,"Temp :",size1);
	OLED_ShowString(x+size1/2*10,y,".",size1);
	OLED_ShowString(x+size1/2*12,y,"C",size1);
	if(temp<0)
	{
		OLED_ShowString(x+size1*3,y,"-",size1);
		temp=-temp;
	}
	else OLED_ShowString(x+size1*3,y," ",size1);
	OLED_ShowNum(x+size1/2*7,y,temp/100,3,size1);
	OLED_ShowNum(x+size1/2*11,y,temp%10,1,size1);
	delay_ms(100);
}

//x,y,z轴角速度校准
u8 Gyroscope_Adjust1(void)
{
	u8 t=10;
	gyrox_offset=0;
	gyroy_offset=0;
	gyroz_offset=0;
	delay_ms(50);
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
	gyrox_offset/=10;
	gyroy_offset/=10;
	gyroz_offset/=10;
	
	if(MPU_Get_Gyroscope(&gyrox,&gyroy,&gyroz)==0)
	{
		if(gyrox_offset==gyrox && gyroy_offset==gyroy && gyroz_offset==gyroz) return 0;
		else return 1;
	}
}


//x,y,z轴加速度校准
u8 Acceleration_Adjust1(void)
{
	short t=10;
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
		if(((aacx_offset-aacx)>-50 && (aacx_offset-aacx)<50) && 
			((aacy_offset-aacy)>-50 && (aacy_offset-aacy)<50) && 
		((aacz_offset-aacz)>-50 && (aacz_offset-aacz)<50)) 
		return 0;
			else return 1;
	}
}



//初始化MPU6050以及检测MPU6050是否连接
void Connect_Check(void)
{
	while(MPU_Init())
	{
		OLED_ShowString(0,2,"MPU6050 Link   ",16);
		delay_ms(200);
		OLED_ShowString(0,2,"MPU6050 Link.  ",16);
		delay_ms(200);
		OLED_ShowString(0,2,"MPU6050 Link.. ",16);
		delay_ms(200);
		OLED_ShowString(0,2,"MPU6050 Link...",16);
		delay_ms(200);
	}
	  OLED_ShowString(0,2,"MPU6050 is OK!",16);
}



void Acceleration_Adjust(void)
{
	while(Acceleration_Adjust1())
	{
		OLED_ShowString(0,6,"Accel Adjust   ",16);
		delay_ms(200);
		OLED_ShowString(0,6,"Accel Adjust.  ",16);
		delay_ms(200);
		OLED_ShowString(0,6,"Accel Adjust.. ",16);
		delay_ms(200);
		OLED_ShowString(0,6,"Accel Adjust...",16);
		delay_ms(200);
	}
	  OLED_ShowString(0,6,"Accel is OK!",16);
	delay_ms(200);
}


void Gyroscope_Adjust(void)
{
	while(Gyroscope_Adjust1())
	{
		OLED_ShowString(0,4,"Gyros Adjust   ",16);
		delay_ms(200);
		OLED_ShowString(0,4,"Gyros Adjust.  ",16);
		delay_ms(200);
		OLED_ShowString(0,4,"Gyros Adjust.. ",16);
		delay_ms(200);
		OLED_ShowString(0,4,"Gyros Adjust...",16);
		delay_ms(200);
	}
	  OLED_ShowString(0,4,"Gyros is OK!",16);
	  delay_ms(400);
}






