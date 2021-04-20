 /**
  ******************************************************************************
  * @文件名 ：control.c
  * @文件说明：此文件为关于舵机转向PID循迹车控制相关函数
  * @版本：V1.0.1
  * @日期：2020-12-12 
  * @魔石科技@
  * @淘宝店铺链接：https://shop418595371.taobao.com
  *  或者直接淘宝搜索店铺魔石电子科技工作室
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


float WheelOneCircleDis=WheelDiameter*pi;//定义小车轮子行走一圈距离变量


/*@brief:根据pid调节左边电机到目标速度
 * @param:
 *        [in]int EncodeSpdL: 当前左电机编码器测速值
 *        [in]float TarSpdL:左边电机目标速度,最大速度越1.19m/s
 * @return: 返回左边电机计算后的pwm占空比
 */
int ChangeSpeedMotorL(int NowEncodeSpdL,float TarSpdL)
{
	int pwm=0;
	int bias=0;
	int TarEncodeSpdL;
	TarEncodeSpdL=(int)((TarSpdL*ACircleEncoder)/(WheelOneCircleDis*100)+0.5f);//根据目标速度求出目标编码器速度

	bias=NowEncodeSpdL-TarEncodeSpdL;
	pwm=PositionPIDToSpd(bias,SpdPdate);
	if(pwm>MAX_MOTOR_PWM)		pwm=MAX_MOTOR_PWM;//限幅
	else if(pwm<-MAX_MOTOR_PWM)  pwm=-MAX_MOTOR_PWM;
	return pwm;
}

/*@brief:根据pid调节右边电机到目标速度
 * @param:
 *        [in]int NowEncodeSpdR: 当前右电机编码器测速值
 *        [in]float TarSpdR:右边电机目标速度,最大速度越1.27m/s
 * @return: 返回右边电机计算后的pwm占空比
 */
int ChangeSpeedMotorR(int NowEncodeSpdR,float TarSpdR)
{
	int pwm=0;
	int bias=0;
	int TarEncodeSpdR;
	TarEncodeSpdR=(int)((TarSpdR*ACircleEncoder)/(WheelOneCircleDis*100)+0.5f);//根据目标速度求出目标编码器速度
	bias=NowEncodeSpdR-TarEncodeSpdR;
	pwm=PositionPIDToSpd(bias,SpdPdate);
	if(pwm>MAX_MOTOR_PWM)		pwm=MAX_MOTOR_PWM;//限幅
	else if(pwm<-MAX_MOTOR_PWM)  pwm=-MAX_MOTOR_PWM;
	return pwm;
}


/*@brief:根据小车的目标距离pid调节左边电机速度
 * @param:
 *        [in]int NowEncodeLALL: 当前左电机编码器总里程
 *        [in]float TarDis:左边电机目标距离，0-10M
 * @return: 返回左边电机计算后的pwm占空比
 */
int ChangeDisSpeedMotorL(int NowEncodeLALL,float TarDis)
{
	int pwm=0;
	int bias=0;
	int TarEncodeLALL;
	TarEncodeLALL=(int)(((TarDis/WheelOneCircleDis)*ACircleEncoder)+0.5f);//根据目标距离求出目标编码器值
	bias=NowEncodeLALL-TarEncodeLALL;
	pwm=PositionPID(bias,DisPdate);
	if(pwm>MAX_MOTOR_PWM)		pwm=MAX_MOTOR_PWM;//限幅
	else if(pwm<-MAX_MOTOR_PWM)  pwm=-MAX_MOTOR_PWM;
	return pwm;
}

/*@brief:根据小车的目标距离pid调节右边电机速度
 * @param:
 *        [in]int NowEncodeRALL: 当前右电机编码器总里程
 *        [in]float TarDis:左边电机目标距离，0-10M
 * @return: 返回右边电机计算后的pwm占空比
 */
int ChangeDisSpeedMotorR(int NowEncodeRALL,float TarDis)
{
	int pwm=0;
	int bias=0;
	int TarEncodeRALL;
	TarEncodeRALL=(int)(((TarDis/WheelOneCircleDis)*ACircleEncoder)+0.5f);//根据目标距离求出目标编码器值
	bias=NowEncodeRALL-TarEncodeRALL;
	pwm=PositionPID2(bias,DisPdate);
	if(pwm>MAX_MOTOR_PWM)		pwm=MAX_MOTOR_PWM;//限幅
	else if(pwm<-MAX_MOTOR_PWM)  pwm=-MAX_MOTOR_PWM;
	return pwm;
}


/*@brief:根据循迹传感器pid调节小车转向使小车处于黑线中间
 * @param:
 *        [in]int TraceDate: 循迹传感器输出的值
 *        [in]float TarSpdL:右边电机目标速度,最大速度越1.27m/s
 * @return: 返回调节电机速度的转向pwm
 */
int ChangeTraceTurn(int TraceDate)
{
	int pwm=0;
	int bias;
	bias=TraceDate;
	pwm=PositionPID(bias,TraceTurnPdate);
	if(pwm>MAX_MOTOR_PWM)		pwm=MAX_MOTOR_PWM;//限幅
	else if(pwm<-MAX_MOTOR_PWM)  pwm=-MAX_MOTOR_PWM;
	return pwm;
}


/*@brief:通过PD控制器控制小车行走一定的距离
 * @param:
 *        [in]float NowEncodeLALL: 当前左轮编码器总里程
 *        [in]float NowEncodeRALL: 当前右轮编码器总里程
 *        [in]float TarDisL: 左边电机目标距离，0-10M
 *        [in]float TarDisR:右边电机目标距离，0-10M
 *@return: 行走结束返回0，否者返回1
 */
void MoveDis(int NowEncodeLALL,int NowEncodeRALL,float TarDisL,float TarDisR)
{
	int dislpwm,disrpwm;
	dislpwm=ChangeDisSpeedMotorL(NowEncodeLALL,TarDisL);
	disrpwm=ChangeDisSpeedMotorR(NowEncodeRALL,TarDisR);
	if(abs(dislpwm)<200) dislpwm=0;//防止电机转不动空耗电
	if(abs(disrpwm)<200) disrpwm=0;
	Set_Pwm_MotorL(dislpwm);
	Set_Pwm_MotorR(disrpwm);
}


/*@brief:小车速度的pid控制函数，通过速度Pi速度控制器调节，使小车最快达到设定速度
 * @param:
 *        [in]float NowEncodeSpdL: 当前左轮编码器速度值
 *        [in]float NowEncodeSpdR: 当前右轮编码器速度值
 *        [in]float TarSpdL: 左轮电机目标速度，最大速度越1.19m/s
 *        [in]float TarSpdR:右轮电机目标速度,最大速度越1.27m/s
 *@return: 行走结束返回0，否者返回1
 */
void MoveSpeed(int NowEncodeSpdL,int NowEncodeSpdR,float TarSpdL,float TarSpdR)
{
	int spdlpwm,spdrpwm;
	spdlpwm=ChangeSpeedMotorL(NowEncodeSpdL,TarSpdL);
	spdrpwm=ChangeSpeedMotorR(NowEncodeSpdR,TarSpdR);
	Set_Pwm_MotorL(spdlpwm);
	Set_Pwm_MotorR(spdrpwm);
}

/*@brief: 让小车根据循迹黑线走
 *@param:
 *        [in]TraceDate: 循迹传感器输出的值
 *        [in]TarSpeed:循迹的目标速度,速度大小0-1.14m/s
 *@return: 到达目标点返回1，否则返回0
 */
void TraceMove(int TraceDate,float TarSpeed)
{
	int turnpwm=0;
	int spdpwm=0;
	int ServorAngle=0;
	
	turnpwm=ChangeTraceTurn(TraceDate);
	
	spdpwm=ChangeSpeedMotorR(Encode_Left,TarSpeed);
	
	if(turnpwm>MAX_SERVOR_PWM)		turnpwm=MAX_SERVOR_PWM;//舵机转向pwm限幅
	else if(turnpwm<-MAX_SERVOR_PWM)  turnpwm=-MAX_SERVOR_PWM;//舵机转向pwm限幅
	
	if(spdpwm>MAX_MOTOR_PWM)		spdpwm=MAX_MOTOR_PWM;//电机转速pwm限幅
	else if(spdpwm<-MAX_MOTOR_PWM)  spdpwm=-MAX_MOTOR_PWM;//电机转速pwm限幅
	
//	printf("turnpwm:%d\r\n",turnpwm);
	
	ServorAngle=turnpwm+Servo_MID;
//	printf("ServorAngle:%d\r\n",ServorAngle);
	Set_Servor_Angle(ServorAngle);		//设置舵机角度
	Set_Pwm_MotorR(spdpwm);				//设置电机1占空比
	Set_Pwm_MotorL(spdpwm);				//设置电机2占空比
}


/*@brief: 根据目标距离循迹行驶，当行驶目标距离后停止循迹
 *@param:
 *        [in]TraceDate: 循迹传感器输出的值
 *        [in]TarDis:小车行驶的目标距离,输出范围0-10M
 *@return: 到达目标点返回1，否则返回0
 */
void TraceMoveWithDis(int TraceDate,float TarDis)
{
	int turnpwm=0;
	int spdpwm;
	u8 ServorAngle=0;
	
	turnpwm=ChangeTraceTurn(TraceDate);
	
	spdpwm=ChangeDisSpeedMotorR(Encode_Left_ALL,TarDis);
		
	if(turnpwm>MAX_SERVOR_PWM)		spdpwm=MAX_SERVOR_PWM;//舵机转向pwm限幅
	else if(spdpwm<-MAX_SERVOR_PWM)  spdpwm=-MAX_SERVOR_PWM;//舵机转向pwm限幅
	
	if(spdpwm>MAX_MOTOR_PWM)		spdpwm=MAX_MOTOR_PWM;//限幅
	else if(spdpwm<-MAX_MOTOR_PWM)  spdpwm=-MAX_MOTOR_PWM;

	ServorAngle=turnpwm+Servo_MID;
	Set_Servor_Angle(ServorAngle);		//设置舵机角度
	Set_Pwm_MotorR(spdpwm);				//设置电机1占空比
	Set_Pwm_MotorL(spdpwm);				//设置电机2占空比
}


