 /**
  ******************************************************************************
  * @�ļ��� ��control.c
  * @�ļ�˵�������ļ�Ϊ���ڶ��ת��PIDѭ����������غ���
  * @�汾��V1.0.1
  * @���ڣ�2020-12-12 
  * @ħʯ�Ƽ�@
  * @�Ա��������ӣ�https://shop418595371.taobao.com
  *  ����ֱ���Ա���������ħʯ���ӿƼ�������
  ******************************************************************************/
#include "control.h"
#include "encoder.h"
#include "pid.h"
#include "common.h"
#include "motor.h"
#include "stdio.h"
#include "stdlib.h"
#include "servor.h"
#define pi 3.1415926


float WheelOneCircleDis=WheelDiameter*pi;//����С����������һȦ�������


/*@brief:����pid������ߵ����Ŀ���ٶ�
 * @param:
 *        [in]int EncodeSpdL: ��ǰ��������������ֵ
 *        [in]float TarSpdL:��ߵ��Ŀ���ٶ�,����ٶ�Խ1.19m/s
 * @return: ������ߵ��������pwmռ�ձ�
 */
int ChangeSpeedMotorL(int NowEncodeSpdL,float TarSpdL)
{
	int pwm=0;
	int bias=0;
	int TarEncodeSpdL;
	TarEncodeSpdL=(int)((TarSpdL*ACircleEncoder)/(WheelOneCircleDis*100)+0.5f);//����Ŀ���ٶ����Ŀ��������ٶ�

	bias=NowEncodeSpdL-TarEncodeSpdL;
	pwm=PositionPIDToSpd(bias,SpdPdate);
	if(pwm>MAX_MOTOR_PWM)		pwm=MAX_MOTOR_PWM;//�޷�
	else if(pwm<-MAX_MOTOR_PWM)  pwm=-MAX_MOTOR_PWM;
	return pwm;
}

/*@brief:����pid�����ұߵ����Ŀ���ٶ�
 * @param:
 *        [in]int NowEncodeSpdR: ��ǰ�ҵ������������ֵ
 *        [in]float TarSpdR:�ұߵ��Ŀ���ٶ�,����ٶ�Խ1.27m/s
 * @return: �����ұߵ��������pwmռ�ձ�
 */
int ChangeSpeedMotorR(int NowEncodeSpdR,float TarSpdR)
{
	int pwm=0;
	int bias=0;
	int TarEncodeSpdR;
	TarEncodeSpdR=(int)((TarSpdR*ACircleEncoder)/(WheelOneCircleDis*100)+0.5f);//����Ŀ���ٶ����Ŀ��������ٶ�
	bias=NowEncodeSpdR-TarEncodeSpdR;
	pwm=PositionPIDToSpd(bias,SpdPdate);
	if(pwm>MAX_MOTOR_PWM)		pwm=MAX_MOTOR_PWM;//�޷�
	else if(pwm<-MAX_MOTOR_PWM)  pwm=-MAX_MOTOR_PWM;
	return pwm;
}


/*@brief:����С����Ŀ�����pid������ߵ���ٶ�
 * @param:
 *        [in]int NowEncodeLALL: ��ǰ���������������
 *        [in]float TarDis:��ߵ��Ŀ����룬0-10M
 * @return: ������ߵ��������pwmռ�ձ�
 */
int ChangeDisSpeedMotorL(int NowEncodeLALL,float TarDis)
{
	int pwm=0;
	int bias=0;
	int TarEncodeLALL;
	TarEncodeLALL=(int)(((TarDis/WheelOneCircleDis)*ACircleEncoder)+0.5f);//����Ŀ��������Ŀ�������ֵ
	bias=NowEncodeLALL-TarEncodeLALL;
	pwm=PositionPID(bias,DisPdate);
	if(pwm>MAX_MOTOR_PWM)		pwm=MAX_MOTOR_PWM;//�޷�
	else if(pwm<-MAX_MOTOR_PWM)  pwm=-MAX_MOTOR_PWM;
	return pwm;
}

/*@brief:����С����Ŀ�����pid�����ұߵ���ٶ�
 * @param:
 *        [in]int NowEncodeRALL: ��ǰ�ҵ�������������
 *        [in]float TarDis:��ߵ��Ŀ����룬0-10M
 * @return: �����ұߵ��������pwmռ�ձ�
 */
int ChangeDisSpeedMotorR(int NowEncodeRALL,float TarDis)
{
	int pwm=0;
	int bias=0;
	int TarEncodeRALL;
	TarEncodeRALL=(int)(((TarDis/WheelOneCircleDis)*ACircleEncoder)+0.5f);//����Ŀ��������Ŀ�������ֵ
	bias=NowEncodeRALL-TarEncodeRALL;
	pwm=PositionPID2(bias,DisPdate);
	if(pwm>MAX_MOTOR_PWM)		pwm=MAX_MOTOR_PWM;//�޷�
	else if(pwm<-MAX_MOTOR_PWM)  pwm=-MAX_MOTOR_PWM;
	return pwm;
}


/*@brief:����ѭ��������pid����С��ת��ʹС�����ں����м�
 * @param:
 *        [in]int TraceDate: ѭ�������������ֵ
 *        [in]float TarSpdL:�ұߵ��Ŀ���ٶ�,����ٶ�Խ1.27m/s
 * @return: ���ص��ڵ���ٶȵ�ת��pwm
 */
int ChangeTraceTurn(int TraceDate)
{
	int pwm=0;
	int bias;
	bias=TraceDate;
	pwm=PositionPID(bias,TraceTurnPdate);
	if(pwm>MAX_MOTOR_PWM)		pwm=MAX_MOTOR_PWM;//�޷�
	else if(pwm<-MAX_MOTOR_PWM)  pwm=-MAX_MOTOR_PWM;
	return pwm;
}


/*@brief:ͨ��PD����������С������һ���ľ���
 * @param:
 *        [in]float NowEncodeLALL: ��ǰ���ֱ����������
 *        [in]float NowEncodeRALL: ��ǰ���ֱ����������
 *        [in]float TarDisL: ��ߵ��Ŀ����룬0-10M
 *        [in]float TarDisR:�ұߵ��Ŀ����룬0-10M
 *@return: ���߽�������0�����߷���1
 */
void MoveDis(int NowEncodeLALL,int NowEncodeRALL,float TarDisL,float TarDisR)
{
	int dislpwm,disrpwm;
	dislpwm=ChangeDisSpeedMotorL(NowEncodeLALL,TarDisL);
	disrpwm=ChangeDisSpeedMotorR(NowEncodeRALL,TarDisR);
	if(abs(dislpwm)<200) dislpwm=0;//��ֹ���ת�����պĵ�
	if(abs(disrpwm)<200) disrpwm=0;
	Set_Pwm_MotorL(dislpwm);
	Set_Pwm_MotorR(disrpwm);
}


/*@brief:С���ٶȵ�pid���ƺ�����ͨ���ٶ�Pi�ٶȿ��������ڣ�ʹС�����ﵽ�趨�ٶ�
 * @param:
 *        [in]float NowEncodeSpdL: ��ǰ���ֱ������ٶ�ֵ
 *        [in]float NowEncodeSpdR: ��ǰ���ֱ������ٶ�ֵ
 *        [in]float TarSpdL: ���ֵ��Ŀ���ٶȣ�����ٶ�Խ1.19m/s
 *        [in]float TarSpdR:���ֵ��Ŀ���ٶ�,����ٶ�Խ1.27m/s
 *@return: ���߽�������0�����߷���1
 */
void MoveSpeed(int NowEncodeSpdL,int NowEncodeSpdR,float TarSpdL,float TarSpdR)
{
	int spdlpwm,spdrpwm;
	spdlpwm=ChangeSpeedMotorL(NowEncodeSpdL,TarSpdL);
	spdrpwm=ChangeSpeedMotorR(NowEncodeSpdR,TarSpdR);
	Set_Pwm_MotorL(spdlpwm);
	Set_Pwm_MotorR(spdrpwm);
}

/*@brief: ��С������ѭ��������
 *@param:
 *        [in]TraceDate: ѭ�������������ֵ
 *        [in]TarSpeed:ѭ����Ŀ���ٶ�,�ٶȴ�С0-1.14m/s
 *@return: ����Ŀ��㷵��1�����򷵻�0
 */
void TraceMove(int TraceDate,float TarSpeed)
{
	int turnpwm=0;
	int spdpwm=0;
	int ServorAngle=0;
	
	turnpwm=ChangeTraceTurn(TraceDate);
	
	spdpwm=ChangeSpeedMotorR(Encode_Left,TarSpeed);
	
	if(turnpwm>MAX_SERVOR_PWM)		turnpwm=MAX_SERVOR_PWM;//���ת��pwm�޷�
	else if(turnpwm<-MAX_SERVOR_PWM)  turnpwm=-MAX_SERVOR_PWM;//���ת��pwm�޷�
	
	if(spdpwm>MAX_MOTOR_PWM)		spdpwm=MAX_MOTOR_PWM;//���ת��pwm�޷�
	else if(spdpwm<-MAX_MOTOR_PWM)  spdpwm=-MAX_MOTOR_PWM;//���ת��pwm�޷�
	
//	printf("turnpwm:%d\r\n",turnpwm);
	
	ServorAngle=turnpwm+Servo_MID;
//	printf("ServorAngle:%d\r\n",ServorAngle);
	Set_Servor_Angle(ServorAngle);		//���ö���Ƕ�
	Set_Pwm_MotorR(spdpwm);				//���õ��1ռ�ձ�
	Set_Pwm_MotorL(spdpwm);				//���õ��2ռ�ձ�
}


/*@brief: ����Ŀ�����ѭ����ʻ������ʻĿ������ֹͣѭ��
 *@param:
 *        [in]TraceDate: ѭ�������������ֵ
 *        [in]TarDis:С����ʻ��Ŀ�����,�����Χ0-10M
 *@return: ����Ŀ��㷵��1�����򷵻�0
 */
void TraceMoveWithDis(int TraceDate,float TarDis)
{
	int turnpwm=0;
	int spdpwm;
	u8 ServorAngle=0;
	
	turnpwm=ChangeTraceTurn(TraceDate);
	
	spdpwm=ChangeDisSpeedMotorR(Encode_Left_ALL,TarDis);
		
	if(turnpwm>MAX_SERVOR_PWM)		spdpwm=MAX_SERVOR_PWM;//���ת��pwm�޷�
	else if(spdpwm<-MAX_SERVOR_PWM)  spdpwm=-MAX_SERVOR_PWM;//���ת��pwm�޷�
	
	if(spdpwm>MAX_MOTOR_PWM)		spdpwm=MAX_MOTOR_PWM;//�޷�
	else if(spdpwm<-MAX_MOTOR_PWM)  spdpwm=-MAX_MOTOR_PWM;

	ServorAngle=turnpwm+Servo_MID;
	Set_Servor_Angle(ServorAngle);		//���ö���Ƕ�
	Set_Pwm_MotorR(spdpwm);				//���õ��1ռ�ձ�
	Set_Pwm_MotorL(spdpwm);				//���õ��2ռ�ձ�
}


