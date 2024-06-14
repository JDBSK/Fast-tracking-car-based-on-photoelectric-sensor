#include "stm32f10x.h"                  // Device header
#include "PID.h"

float Err=0,LastErr=0,LastLastErr=0;
//float pwm_CCR=0,Add_CCR=0;                                //pwm�µ�PWM�Ƚ�ֵ��add���µ�PWMռ�ձȸ���ֵ
float setspeed=0;                              //�趨����������ֵ


PID_type L_pid,R_pid;


PID_type PID_Init(PID_type pidstruct)
{
	pidstruct.Kp = 0;
	pidstruct.Ki = 0;
	pidstruct.Kd = 0;
	
	pidstruct.Target_val = 0;//�������ٶ�
	pidstruct.Err = 0;
	pidstruct.LastErr = 0;
	pidstruct.PrevErr = 0;
	pidstruct.Sum_err = 0;
	pidstruct.Output_val=0; //���CRR ����ʱ��
	return pidstruct;
}


/**
  * @Brief	pid����
  * @Param  speed ������10ms����ֵ 	pidstruct pid�ṹ��
  * @Retval crr�Ƚ�ֵ��max 400-1��
  */
PID_type PID_control(PID_type pidstruct,int16_t speed)
{
	
  pidstruct.Err = pidstruct.Target_val - speed;   
	pidstruct.Sum_err += pidstruct.Err;	
	if(pidstruct.Sum_err > 799)pidstruct.Sum_err = 799;
	if(pidstruct.Sum_err < -799)	 pidstruct.Sum_err = -799;//0
	
    //Add_CCR = p*(Err-LastErr)+i*(Err)+d*(Err+LastLastErr-2*LastErr);
	
	
	pidstruct.Output_val = pidstruct.Kp * pidstruct.Err +
												 pidstruct.Ki * pidstruct.Sum_err +
												 pidstruct.Kd * (pidstruct.Err - pidstruct.LastErr); //ռ�ձ�
	
	//if( 1 < pidstruct.Err || pidstruct.Err < -1 ) //�޷���΢С�仯�����ģ����ٶ���
	//{
	 //pwm_CCR+=Add_CCR; ����ʽ
		//pwm_CCR = pidstruct.Output_val;
	if(pidstruct.Output_val > 799)
        pidstruct.Output_val = 799;
    if(pidstruct.Output_val < -799)
        pidstruct.Output_val = -799;
	//}
	 

		
    pidstruct.PrevErr = pidstruct.LastErr;  //����һ����ֵ�����ϴ����
    pidstruct.LastErr = pidstruct.Err;			//��������ֵ���ϴ����
		pidstruct.Sum_err += pidstruct.Err;
		
    return pidstruct;					//����PWM�µ�ռ�ձ�ֵ
}

PID_type PID_SetVal(PID_type pidstruct,float Kp,float Ki,float Kd)
{
	pidstruct.Kp = Kp;
	pidstruct.Ki = Ki;
	pidstruct.Kd = Kd;
	
	return pidstruct;
}
