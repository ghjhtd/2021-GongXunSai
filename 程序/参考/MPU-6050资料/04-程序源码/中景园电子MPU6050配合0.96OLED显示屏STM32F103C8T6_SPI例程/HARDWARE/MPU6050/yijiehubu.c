#include "parameter.h"

float angle;

/**************************************************************************
�������ܣ�һ�׻����˲�
��ڲ��������ٶȡ����ٶ�
����  ֵ����
**************************************************************************/
float Yijielvbo(float angle_m, float gyro_m)
{
	float K1 =0.02; 
   angle = K1 * angle_m+ (1-K1) * (angle + gyro_m * 0.005);
	return angle;
}


u8 Yijielvbo_EulerAngle(float *pitch,float *roll,float *yaw)
{
	short gyrox,gyroy,gyroz;	//������ԭʼ����
	short aacx,aacy,aacz;		//���ٶȴ�����ԭʼ����
	if((MPU_Get_Gyroscope(&gyrox,&gyroy,&gyroz)==0) && (MPU_Get_Accelerometer(&aacx,&aacy,&aacz)==0))
	{
		*pitch=Yijielvbo(aacx,gyrox);
		*roll=Yijielvbo(aacx,gyrox);
		*yaw=Yijielvbo(aacx,gyrox);
	}
	else return 0;
		return 1;
}





