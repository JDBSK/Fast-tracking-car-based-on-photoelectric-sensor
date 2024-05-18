#ifndef __PID_H
#define __PID_H

extern float setspeed;
extern float Err;


typedef struct 
{
	float Target_val;   //Ŀ��ֵ  ��Ӧ������
	float Err;          /*�� k ��ƫ�� */
	float LastErr;     /* Error[-1],�� k-1 ��ƫ�� */
	float PrevErr;    /* Error[-2],�� k-2 ��ƫ�� */
	float Kp,Ki,Kd;     //���������֡�΢��ϵ��
	float Sum_err;     //����ֵ
	float Output_val;   	  //���ֵ
}PID_type;

extern PID_type L_pid,R_pid;


PID_type PID_Init(PID_type pidstruct);
PID_type PID_control(PID_type pidstruct,int16_t speed);
PID_type PID_SetVal(PID_type pidstruct,float Kp,float Ki,float Kd);

#endif
