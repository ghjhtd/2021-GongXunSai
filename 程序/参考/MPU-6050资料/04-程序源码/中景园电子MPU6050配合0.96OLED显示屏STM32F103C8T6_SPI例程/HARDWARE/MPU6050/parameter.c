#include "parameter.h"

short gyrox_offset=0,gyroy_offset=0,gyroz_offset=0;//x,y,z����ٶ�ƫ����
short aacx_offset=0,aacy_offset=0,aacz_offset=0;//x,y,z����ٶ�ƫ����
float pitch,roll,yaw; 		//ŷ����
short gyrox,gyroy,gyroz;	//������ԭʼ����
short aacx,aacy,aacz;		//���ٶȴ�����ԭʼ����

//��ʾ�¶Ⱥ�ŷ����
//Temp :�¶�    ����:0.1��
//pitch:������  ����:0.1��   ��Χ:-90.0�� <---> +90.0��
//roll :�����  ����:0.1��   ��Χ:-180.0��<---> +180.0��
//yaw  :�����  ����:0.1��   ��Χ:-180.0��<---> +180.0��
//ע   :����δ���Ӵ����ƣ�yaw������ǣ��ᷢ��Ư�ƣ�������׼ȷ
void Show_EulerAngle(void)
{
	short temp;
	if(mpu_dmp_get_data(&pitch,&roll,&yaw)==0)//��ȡŷ����
		{ 
			temp=MPU_Get_Temperature();//��ȡ�¶�
			OLED_ShowString(0, 0,"Temp :    . C  ",16);//��ʾ�¶�
			OLED_ShowString(0,16,"Pitch:    . C  ",16);//��ʾ������
			OLED_ShowString(0,32,"Roll :    . C  ",16);//��ʾ�����
			OLED_ShowString(0,48,"Yaw  :    . C  ",16);//��ʾ�����
			//��ʾ�¶�
			if(temp<0)
			{
				OLED_ShowString(48,0,"-",16);//���tempС��0����ʾ��-����
				temp=-temp;
			}
			else OLED_ShowString(48,0," ",16);
			OLED_ShowNum(56,0,temp/100,3,16);//��ʾ��������
			OLED_ShowNum(88,0,temp%10,1,16);//��ʾС������
			//��ʾpitch
			temp=pitch*10;//��pitch�Ŵ�10��
			if(temp<0)
			{
				OLED_ShowString(48,16,"-",16);//���tempС��0����ʾ��-����
				temp=-temp;
			}
			else OLED_ShowString(48,16," ",16);
			OLED_ShowNum(56,16,temp/10,3,16);//��ʾ��������
			OLED_ShowNum(88,16,temp%10,1,16);//��ʾС������
			//��ʾroll
			temp=roll*10;//��roll�Ŵ�10��
			if(temp<0)
			{
				OLED_ShowString(48,32,"-",16);//���tempС��0����ʾ��-����
				temp=-temp;
			}
			else OLED_ShowString(48,32," ",16);
			OLED_ShowNum(56,32,temp/10,3,16);//��ʾ��������
			OLED_ShowNum(88,32,temp%10,1,16);//��ʾС������
			//��ʾyaw
			temp=yaw*10;//��yaw�Ŵ�10��
			if(temp<0)
			{
				OLED_ShowString(48,48,"-",16);//���tempС��0����ʾ��-����
				temp=-temp;
			}
			else OLED_ShowString(48,48," ",16);
			OLED_ShowNum(56,48,temp/10,3,16);//��ʾ��������
			OLED_ShowNum(88,48,temp%10,1,16);//��ʾС������			
	  OLED_Refresh();
		delay_ms(200);
	}
}

//��ʾ���ٶ�
//gyrox:x����ٶ� ����:0.1�� ��Χ:-2000.0 <---> +2000.0
//gyroy:y����ٶ� ����:0.1�� ��Χ:-2000.0 <---> +2000.0
//gyroz:z����ٶ� ����:0.1�� ��Χ:-2000.0 <---> +2000.0
void Show_Gyroscope(void)
{
	short temp;
	if(MPU_Get_Gyroscope(&gyrox,&gyroy,&gyroz)==0)
	{ 
		OLED_ShowString(0,16,"gyrox:     .   ",16);//��ʾx����ٶ�rad/s
		OLED_ShowString(0,32,"gyroy:     .   ",16);//��ʾy����ٶ�rad/s
		OLED_ShowString(0,48,"gyroz:     .   ",16);//��ʾz����ٶ�rad/s

		//��ʾgyrox
		gyrox-=gyrox_offset;//ƫ��У��
		temp=10*gyrox*Gyro_Fsr/32768;
		if(temp<0)
		{
			OLED_ShowString(48,16,"-",16);//���tempС��0����ʾ��-����
			temp=-temp;
		}
		else OLED_ShowString(48,16," ",16);
		OLED_ShowNum(56,16,temp/10,4,16);//��ʾ��������
		OLED_ShowNum(96,16,temp%10,1,16);//��ʾС������
		
		//��ʾgyroy
		gyroy-=gyroy_offset;//ƫ��У��
		temp=10*gyroy*Gyro_Fsr/32768;
		if(temp<0)
		{
			OLED_ShowString(48,32,"-",16);//���tempС��0����ʾ��-����
			temp=-temp;
		}
		else OLED_ShowString(48,32," ",16);
		OLED_ShowNum(56,32,temp/10,4,16);//��ʾ��������
		OLED_ShowNum(96,32,temp%10,1,16);//��ʾС������
		
		//��ʾgyroz
		gyroz-=gyroz_offset;//ƫ��У��
		temp=10*gyroz*Gyro_Fsr/32768;
		if(temp<0)
		{
			OLED_ShowString(48,48,"-",16);//���tempС��0����ʾ��-����
			temp=-temp;
		}
		else OLED_ShowString(48,48," ",16);
		OLED_ShowNum(56,48,temp/10,4,16);//��ʾ��������
		OLED_ShowNum(96,48,temp%10,1,16);//��ʾС������			
	OLED_Refresh();
	delay_ms(200);
 }
}

//��ʾ���ٶ�
//aacx:x����ٶ� ����:0.1�� ��Χ:-2g <---> +2g
//aacy:y����ٶ� ����:0.1�� ��Χ:-2g <---> +2g
//aacz:z����ٶ� ����:0.1�� ��Χ:-2g <---> +2g
//g:�������ٶ�
void Show_Acceleration(void)
{
	short temp;
	if(MPU_Get_Accelerometer(&aacx,&aacy,&aacz)==0)
	{
		OLED_ShowString(0,16,"aacx:    . m/s2",16);//��ʾaccx
		OLED_ShowString(0,32,"aacy:    . m/s2",16);//��ʾaccy
		OLED_ShowString(0,48,"aacz:    . m/s2",16);//��ʾaccz
		//��ʾaccx
		aacx-=aacx_offset;//ƫ��У��
		temp=(float)10*Accel_G*Accel_Fsr*aacx/32768;
		if(temp<0)
		{
			temp=-temp;
			OLED_ShowString(40,16,"-",16);//���tempС��0����ʾ��-����
		}
		else OLED_ShowString(40,16," ",16);
		OLED_ShowNum(48,16,temp/10,3,16);//��ʾ��������
		OLED_ShowNum(80,16,temp%10,1,16);//��ʾС������
		//��ʾaccy
		aacy-=aacy_offset;//ƫ��У��
		temp=(float)10*Accel_G*Accel_Fsr*aacy/32768;
		if(temp<0)
		{
			OLED_ShowString(40,32,"-",16);//���tempС��0����ʾ��-����
			temp=-temp;
		}
		else OLED_ShowString(40,32," ",16);
		OLED_ShowNum(48,32,temp/10,3,16);//��ʾ��������
		OLED_ShowNum(80,32,temp%10,1,16);//��ʾС������
		//��ʾaccz
		aacz-=aacz_offset;//ƫ��У��
		temp=(float)10*Accel_G*Accel_Fsr*aacz/32768;
		if(temp<0)
		{
			OLED_ShowString(40,48,"-",16);//���tempС��0����ʾ��-����
			temp=-temp;
		}
		else OLED_ShowString(40,48," ",16);
		OLED_ShowNum(48,48,temp/10,3,16);//��ʾ��������
		OLED_ShowNum(80,48,temp%10,1,16);//��ʾС������			
	  OLED_Refresh();
		delay_ms(200);
		}
}

//��ʾ�¶�
void Show_Temperture(u8 x,u8 y,u8 size)
{
	short temp;
	temp=MPU_Get_Temperature();
	OLED_ShowString(x,y,"Temp :    . C  ",size);
	if(temp<0)
	{
		OLED_ShowString(x+size*3,y,"-",size);
		temp=-temp;
	}
	else OLED_ShowString(x+size*3,y," ",size);
	OLED_ShowNum(x+size/2*7,y,temp/10,3,size);
	OLED_ShowNum(x+size/2*11,y,temp%10,1,size);
	OLED_Refresh();
	delay_ms(100);
}

//x,y,z����ٶ�У׼
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
			gyrox_offset+=gyrox;//������ȡ10��x����ٶ�ֵ
			gyroy_offset+=gyroy;//������ȡ10��y����ٶ�ֵ
			gyroz_offset+=gyroz;//������ȡ10��z����ٶ�ֵ
			delay_ms(10);
		}
	}
	gyrox_offset/=10;//ȡƽ��ֵ
	gyroy_offset/=10;//ȡƽ��ֵ
	gyroz_offset/=10;//ȡƽ��ֵ
	
	if(MPU_Get_Gyroscope(&gyrox,&gyroy,&gyroz)==0)
	{
		if((gyrox_offset-gyrox)>-5 && (gyrox_offset-gyrox)<5 &&
			 (gyroy_offset-gyroy)>-5 && (gyroy_offset-gyroy)<5 && 
		   (gyroz_offset-gyroz)>-5 && (gyroz_offset-gyroz)<5) return 0;
		else return 1;
	}
}


//x,y,z����ٶ�У׼
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
			aacx_offset+=aacx/10;//������ȡ10��x����ٶ�ֵ
			aacy_offset+=aacy/10;//������ȡ10��y����ٶ�ֵ
			//ˮƽ����ʱ�κ�ʱ��z�ᶼ���������ٶȣ����Լ���ƫ������ʱ����Ҫ��ȥһ���������ٶȵ�ֵ
			aacz-=16384;
			aacz_offset+=aacz/10;//������ȡ10��z����ٶ�ֵ
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


//��ʼ��MPU6050�Լ����MPU6050�Ƿ�����
void Connect_Check(void)
{
	while(mpu_dmp_init())
	{
		OLED_ShowString(0,16,"MPU6050 Link   ",16);
		OLED_Refresh();
		delay_ms(200);
		OLED_ShowString(0,16,"MPU6050 Link.  ",16);
		OLED_Refresh();
		delay_ms(200);
		OLED_ShowString(0,16,"MPU6050 Link.. ",16);
		OLED_Refresh();
		delay_ms(200);
		OLED_ShowString(0,16,"MPU6050 Link...",16);
		OLED_Refresh();
		delay_ms(200);
	}
	  OLED_ShowString(0,16,"MPU6050 is OK! ",16);
	  OLED_Refresh();
	  delay_ms(400);
}

void Acceleration_Adjust(void)
{
	while(Acceleration_Adjust1())
	{
		OLED_ShowString(0,48,"Accel Adjust   ",16);
		OLED_Refresh();
		delay_ms(200);
		OLED_ShowString(0,48,"Accel Adjust.  ",16);
		OLED_Refresh();
		delay_ms(200);
		OLED_ShowString(0,48,"Accel Adjust.. ",16);
		OLED_Refresh();
		delay_ms(200);
		OLED_ShowString(0,48,"Accel Adjust...",16);
		OLED_Refresh();
		delay_ms(200);
	}
	  OLED_ShowString(0,48,"Accel is OK!   ",16);
	OLED_Refresh();
	delay_ms(800);
}


void Gyroscope_Adjust(void)
{
	while(Gyroscope_Adjust1())
	{
		OLED_ShowString(0,32,"Gyros Adjust   ",16);
		OLED_Refresh();
		delay_ms(200);
		OLED_ShowString(0,32,"Gyros Adjust.  ",16);
		OLED_Refresh();
		delay_ms(200);
		OLED_ShowString(0,32,"Gyros Adjust.. ",16);
		OLED_Refresh();
		delay_ms(200);
		OLED_ShowString(0,32,"Gyros Adjust...",16);
		OLED_Refresh();
		delay_ms(200);
	}
	  OLED_ShowString(0,32,"Gyros is OK!   ",16);
	  OLED_Refresh();
	  delay_ms(400);
}

