#include "parameter.h"

short gyrox_offset=0,gyroy_offset=0,gyroz_offset=0;//x,y,z����ٶ�ƫ����
short aacx_offset=0,aacy_offset=0,aacz_offset=0;//x,y,z����ٶ�ƫ����
float pitch,roll,yaw; 		//ŷ����
short gyrox,gyroy,gyroz;	//������ԭʼ����
short aacx,aacy,aacz;		//���ٶȴ�����ԭʼ����

//ŷ����
//pitch:������  ����:0.1��   ��Χ:-90.0�� <---> +90.0��
//roll :�����  ����:0.1��   ��Χ:-180.0��<---> +180.0��
//yaw  :�����  ����:0.1��   ��Χ:-180.0��<---> +180.0��
//ע   :����δ���Ӵ����ƣ�yaw������ǣ��ᷢ��Ư�ƣ�������׼ȷ
void Show_EulerAngle(u8 x,u8 y,u8 size,u16 color)
{
	short temp;
	if(mpu_dmp_get_data(&pitch,&roll,&yaw)==0)//��ȡŷ����
		{ 
			LCD_ShowString(x,y,"Pitch:",size,color);//��ʾ������
			LCD_ShowString(x+size/2*10,y,".",size,color);
			LCD_ShowString(x+size/2*12,y,"C",size,color);
			LCD_ShowString(x,y+size,"Roll :",size,color);//��ʾ�����
			LCD_ShowString(x+size/2*10,y+size,".",size,color);
			LCD_ShowString(x+size/2*12,y+size,"C",size,color);
			LCD_ShowString(x,y+size*2,"Yaw  :",size,color);//��ʾ�����
			LCD_ShowString(x+size/2*10,y+size*2,".",size,color);
			LCD_ShowString(x+size/2*12,y+size*2,"C",size,color);
			//��ʾpitch
			temp=pitch*10;//��pitch�Ŵ�10��
			if(temp<0)
			{
				LCD_ShowString(x+size/2*6,y,"-",size,color);//���tempС��0����ʾ��-����
				temp=-temp;
			}
			else LCD_ShowString(x+size/2*6,y," ",size,color);
			LCD_ShowNum(x+size/2*7,y,temp/10,3,size,color);//��ʾ��������
			LCD_ShowNum(x+size/2*11,y,temp%10,1,size,color);//��ʾС������
			//��ʾroll
			temp=roll*10;//��roll�Ŵ�10��
			if(temp<0)
			{
				LCD_ShowString(x+size/2*6,y+size,"-",size,color);//���tempС��0����ʾ��-����
				temp=-temp;
			}
			else LCD_ShowString(x+size/2*6,y+size," ",size,color);
			LCD_ShowNum(x+size/2*7,y+size,temp/10,3,size,color);//��ʾ��������
			LCD_ShowNum(x+size/2*11,y+size,temp%10,1,size,color);//��ʾС������
			//��ʾyaw
			temp=yaw*10;//��yaw�Ŵ�10��
			if(temp<0)
			{
				LCD_ShowString(x+size/2*6,y+size*2,"-",size,color);//���tempС��0����ʾ��-����
				temp=-temp;
			}
			else LCD_ShowString(x+size/2*6,y+size*2," ",size,color);
			LCD_ShowNum(x+size/2*7,y+size*2,temp/10,3,size,color);//��ʾ��������
			LCD_ShowNum(x+size/2*11,y+size*2,temp%10,1,size,color);//��ʾС������			
	}
}

//��ʾ���ٶ�
//gyrox:x����ٶ� ����:0.1�� ��Χ:-2000.0 <---> +2000.0
//gyroy:y����ٶ� ����:0.1�� ��Χ:-2000.0 <---> +2000.0
//gyroz:z����ٶ� ����:0.1�� ��Χ:-2000.0 <---> +2000.0
void Show_Gyroscope(u8 x,u8 y,u8 size,u16 color)
{
	short temp;
	if(MPU_Get_Gyroscope(&gyrox,&gyroy,&gyroz)==0)
	{ 
		LCD_ShowString(x,y,"gyrox:",size,color);//��ʾx����ٶ�rad/s
		LCD_ShowString(x+size/2*11,y,".",size,color);
		LCD_ShowString(x+size/2*13,y,"rad/s",size,color);
		LCD_ShowString(x,y+size,"gyroy:",size,color);//��ʾy����ٶ�rad/s
		LCD_ShowString(x+size/2*11,y+size,".",size,color);
		LCD_ShowString(x+size/2*13,y+size,"rad/s",size,color);
		LCD_ShowString(x,y+size*2,"gyroz:",size,color);//��ʾz����ٶ�rad/s
		LCD_ShowString(x+size/2*11,y+size*2,".",size,color);
		LCD_ShowString(x+size/2*13,y+size*2,"rad/s",size,color);

		//��ʾgyrox
		gyrox-=gyrox_offset;//ƫ��У��
		temp=10*gyrox*Gyro_Fsr/32768;
		if(temp<0)
		{
			LCD_ShowString(x+size/2*6,y,"-",size,color);//���tempС��0����ʾ��-����
			temp=-temp;
		}
		else LCD_ShowString(x+size/2*6,y," ",size,color);
		LCD_ShowNum(x+size/2*7,y,temp/10,4,size,color);//��ʾ��������
		LCD_ShowNum(x+size/2*12,y,temp%10,1,size,color);//��ʾС������
		
		//��ʾgyroy
		gyroy-=gyroy_offset;//ƫ��У��
		temp=10*gyroy*Gyro_Fsr/32768;
		if(temp<0)
		{
			LCD_ShowString(x+size/2*6,y+size,"-",size,color);//���tempС��0����ʾ��-����
			temp=-temp;
		}
		else LCD_ShowString(x+size/2*6,y+size," ",size,color);
		LCD_ShowNum(x+size/2*7,y+size,temp/10,4,size,color);//��ʾ��������
		LCD_ShowNum(x+size/2*12,y+size,temp%10,1,size,color);//��ʾС������
		
		//��ʾgyroz
		gyroz-=gyroz_offset;//ƫ��У��
		temp=10*gyroz*Gyro_Fsr/32768;
		if(temp<0)
		{
			LCD_ShowString(x+size/2*6,y+size*2,"-",size,color);//���tempС��0����ʾ��-����
			temp=-temp;
		}
		else LCD_ShowString(x+size/2*6,y+size*2," ",size,color);
		LCD_ShowNum(x+size/2*7,y+size*2,temp/10,4,size,color);//��ʾ��������
		LCD_ShowNum(x+size/2*12,y+size*2,temp%10,1,size,color);//��ʾС������			
 }
}

//��ʾ���ٶ�
//aacx:x����ٶ� ����:0.1�� ��Χ:-2g <---> +2g
//aacy:y����ٶ� ����:0.1�� ��Χ:-2g <---> +2g
//aacz:z����ٶ� ����:0.1�� ��Χ:-2g <---> +2g
//g:�������ٶ�
void Show_Acceleration(u8 x,u8 y,u8 size,u16 color)
{
	short temp;
	if(MPU_Get_Accelerometer(&aacx,&aacy,&aacz)==0)
	{
		LCD_ShowString(x,y,"aacx:",size,color);//��ʾaccx
		LCD_ShowString(x+size/2*9,y,".",size,color);
		LCD_ShowString(x+size/2*11,y,"m/s2",size,color);
		LCD_ShowString(x,y+size,"aacy:",size,color);//��ʾaccy
		LCD_ShowString(x+size/2*9,y+size,".",size,color);
		LCD_ShowString(x+size/2*11,y+size,"m/s2",size,color);
		LCD_ShowString(x,y+size*2,"aacz:",size,color);//��ʾaccz
		LCD_ShowString(x+size/2*9,y+size*2,".",size,color);
		LCD_ShowString(x+size/2*11,y+size*2,"m/s2",size,color);
		//��ʾaccx
		aacx-=aacx_offset;//ƫ��У��
		temp=(float)10*Accel_G*Accel_Fsr*aacx/32768;
		if(temp<0)
		{
			temp=-temp;
			LCD_ShowString(x+size/2*5,y,"-",size,color);//���tempС��0����ʾ��-����
		}
		else LCD_ShowString(x+size/2*5,y," ",size,color);
		LCD_ShowNum(x+size/2*6,y,temp/10,3,size,color);//��ʾ��������
		LCD_ShowNum(x+size/2*10,y,temp%10,1,size,color);//��ʾС������
		//��ʾaccy
		aacy-=aacy_offset;//ƫ��У��
		temp=(float)10*Accel_G*Accel_Fsr*aacy/32768;
		if(temp<0)
		{
			LCD_ShowString(x+size/2*5,y+size,"-",size,color);//���tempС��0����ʾ��-����
			temp=-temp;
		}
		else LCD_ShowString(x+size/2*5,y+size," ",size,color);
		LCD_ShowNum(x+size/2*6,y+size,temp/10,3,size,color);//��ʾ��������
		LCD_ShowNum(x+size/2*10,y+size,temp%10,1,size,color);//��ʾС������
		//��ʾaccz
		aacz-=aacz_offset;//ƫ��У��
		temp=(float)10*Accel_G*Accel_Fsr*aacz/32768;
		if(temp<0)
		{
			LCD_ShowString(x+size/2*5,y+size*2,"-",size,color);//���tempС��0����ʾ��-����
			temp=-temp;
		}
		else LCD_ShowString(x+size/2*5,y+size*2," ",size,color);
		LCD_ShowNum(x+size/2*6,y+size*2,temp/10,3,size,color);//��ʾ��������
		LCD_ShowNum(x+size/2*10,y+size*2,temp%10,1,size,color);//��ʾС������			
		}
}

//��ʾ�¶�
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

//���ٶȴ�����У׼����
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

//������У׼����
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



