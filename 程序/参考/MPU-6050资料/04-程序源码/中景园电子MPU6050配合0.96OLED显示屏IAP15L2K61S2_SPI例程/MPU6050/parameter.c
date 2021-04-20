#include "parameter.h"

short gyrox_offset=0,gyroy_offset=0,gyroz_offset=0;//x,y,z����ٶ�ƫ����
short aacx_offset=0,aacy_offset=0,aacz_offset=0;//x,y,z����ٶ�ƫ����
float pitch,roll,yaw; 		//ŷ����
short gyrox,gyroy,gyroz;	//������ԭʼ����
short aacx,aacy,aacz;		//���ٶȴ�����ԭʼ����

//��ʾ���ٶ�
//gyrox:x����ٶ� ����:0.1�� ��Χ:-2000.0 <---> +2000.0
//gyroy:y����ٶ� ����:0.1�� ��Χ:-2000.0 <---> +2000.0
//gyroz:z����ٶ� ����:0.1�� ��Χ:-2000.0 <---> +2000.0
void Show_Gyroscope(void)
{
	short temp;
	if(MPU_Get_Gyroscope(&gyrox,&gyroy,&gyroz)==0)
	{ 
		OLED_ShowString(0,2,"gyrox:",16);//��ʾx����ٶ�rad/s
		OLED_ShowString(88,2,".",16);
		OLED_ShowString(0,4,"gyroy:",16);//��ʾy����ٶ�rad/s
		OLED_ShowString(88,4,".",16);
		OLED_ShowString(0,6,"gyroz:",16);//��ʾz����ٶ�rad/s
		OLED_ShowString(88,6,".",16);

		//��ʾgyrox
		gyrox-=gyrox_offset;//ƫ��У��
		temp=(float)10*gyrox*Gyro_Fsr/32768;
		if(temp<0)
		{
			OLED_ShowString(48,2,"-",16);//���tempС��0����ʾ��-����
			temp=-temp;
		}
		else OLED_ShowString(48,2," ",16);
		OLED_ShowNum(56,2,temp/10,4,16);//��ʾ��������
		OLED_ShowNum(96,2,temp%10,1,16);//��ʾС������
		
		//��ʾgyroy
		gyroy-=gyroy_offset;//ƫ��У��
		temp=(float)10*gyroy*Gyro_Fsr/32768;
		if(temp<0)
		{
			OLED_ShowString(48,4,"-",16);//���tempС��0����ʾ��-����
			temp=-temp;
		}
		else OLED_ShowString(48,4," ",16);
		OLED_ShowNum(56,4,temp/10,4,16);//��ʾ��������
		OLED_ShowNum(96,4,temp%10,1,16);//��ʾС������
		
		//��ʾgyroz
		gyroz-=gyroz_offset;//ƫ��У��
		temp=(float)10*gyroz*Gyro_Fsr/32768;
		if(temp<0)
		{
			OLED_ShowString(48,6,"-",16);//���tempС��0����ʾ��-����
			temp=-temp;
		}
		else OLED_ShowString(48,6," ",16);
		OLED_ShowNum(56,6,temp/10,4,16);//��ʾ��������
		OLED_ShowNum(96,6,temp%10,1,16);//��ʾС������			
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
		OLED_ShowString(0,2,"aacx:",16);//��ʾaccx
		OLED_ShowString(72,2,".",16);
		OLED_ShowString(88,2,"m/s2",16);
		OLED_ShowString(0,4,"aacy:",16);//��ʾaccy
		OLED_ShowString(72,4,".",16);
		OLED_ShowString(88,4,"m/s2",16);
		OLED_ShowString(0,6,"aacz:",16);//��ʾaccz
		OLED_ShowString(72,6,".",16);
		OLED_ShowString(88,6,"m/s2",16);
		//��ʾaccx
		aacx-=aacx_offset;//ƫ��У��
		temp=(float)10*Accel_G*Accel_Fsr*aacx/32768;
		if(temp<0)
		{
			temp=-temp;
			OLED_ShowString(40,2,"-",16);//���tempС��0����ʾ��-����
		}
		else OLED_ShowString(40,2," ",16);
		OLED_ShowNum(48,2,temp/10,3,16);//��ʾ��������
		OLED_ShowNum(80,2,temp%10,1,16);//��ʾС������
		//��ʾaccy
		aacy-=aacy_offset;//ƫ��У��
		temp=(float)10*Accel_G*Accel_Fsr*aacy/32768;
		if(temp<0)
		{
			OLED_ShowString(40,4,"-",16);//���tempС��0����ʾ��-����
			temp=-temp;
		}
		else OLED_ShowString(40,4," ",16);
		OLED_ShowNum(48,4,temp/10,3,16);//��ʾ��������
		OLED_ShowNum(80,4,temp%10,1,16);//��ʾС������
		//��ʾaccz
		aacz-=aacz_offset;//ƫ��У��
		temp=(float)10*Accel_G*Accel_Fsr*aacz/32768;
		if(temp<0)
		{
			OLED_ShowString(40,6,"-",16);//���tempС��0����ʾ��-����
			temp=-temp;
		}
		else OLED_ShowString(40,6," ",16);
		OLED_ShowNum(48,6,temp/10,3,16);//��ʾ��������
		OLED_ShowNum(80,6,temp%10,1,16);//��ʾС������			
		}
}

//��ʾ�¶�
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

//x,y,z����ٶ�У׼
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
			gyrox_offset+=gyrox;//������ȡ10��x����ٶ�ֵ
			gyroy_offset+=gyroy;//������ȡ10��y����ٶ�ֵ
			gyroz_offset+=gyroz;//������ȡ10��z����ٶ�ֵ
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


//x,y,z����ٶ�У׼
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
		if(((aacx_offset-aacx)>-50 && (aacx_offset-aacx)<50) && 
			((aacy_offset-aacy)>-50 && (aacy_offset-aacy)<50) && 
		((aacz_offset-aacz)>-50 && (aacz_offset-aacz)<50)) 
		return 0;
			else return 1;
	}
}



//��ʼ��MPU6050�Լ����MPU6050�Ƿ�����
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






