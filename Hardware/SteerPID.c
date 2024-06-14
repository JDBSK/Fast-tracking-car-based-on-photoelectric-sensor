#include "stm32f10x.h"
#include "PID.h"
#include "Motor.h"
#include "OlED.h"


PID_type SteerPID;
float sensor_pos[9]={4.5,3.5,2,1,0,-1,-2,-3.5,-4.5};//err

/**
  * @Brief	ת��pid����
  * @Param  pidstruct ת��pid�ṹ��  directtion ������������ʾ��ǰλ��  
  * @Retval ��������ֵ
  */
PID_type SteerPID_control(PID_type pidstruct,uint8_t* Line_Direction)
{
	uint8_t Line_pos;

		for(uint8_t i=4;i<6;i++)
	{
	
		if(Line_Direction[i] == 1)//���������м�����ɨ��
		{
			Line_pos = i;//��ǰ�ߵ�λ�ã���������ȡ��
			break;
		}
	}
	for(uint8_t i=4;i>2;i--)
	{
		if(Line_Direction[i] == 1)//���������м�����ɨ��
		{
			Line_pos = i;//��ǰ�ߵ�λ�ã���������ȡ��
			break;
	  }
	}

	for(uint8_t i=0;i<3;i++)
	{
	
		if(Line_Direction[i] == 1)//�����������ߵ��м�ɨ��
		{
			Line_pos = i;//��ǰ�ߵ�λ�ã���������ȡ��
			break;
		}
	}	for(uint8_t i=8;i>5;i--)
	{
	
		if(Line_Direction[i] == 1)//�����������ߵ��м�ɨ��
		{
			Line_pos = i;//��ǰ�ߵ�λ�ã���������ȡ��
			break;
		}
	}
	
	pidstruct.Err = sensor_pos[Line_pos];   //��ȡ���������߲��  targetĬ��Ϊ����0����ʾ���ֲ�����
	pidstruct.Sum_err += pidstruct.Err;		
	
	pidstruct.Output_val = pidstruct.Kp *  pidstruct.Err +
						   pidstruct.Ki *  pidstruct.Sum_err +
						   pidstruct.Kd * (pidstruct.Err - pidstruct.LastErr); //����������ֵ ��10ms��
	
//	OLED_ShowSignedNum(2,1,pidstruct.Output_val,2);//��ʾ��������
	
		//�����ڵ������ת�ٷ�Χ��
	if(pidstruct.Output_val > 40)
        pidstruct.Output_val = 40;
    if(pidstruct.Output_val < -40)
        pidstruct.Output_val = -40;

		
    pidstruct.PrevErr = pidstruct.LastErr;  //����һ����ֵ�����ϴ����
    pidstruct.LastErr = pidstruct.Err;			//��������ֵ���ϴ����
	pidstruct.Sum_err += pidstruct.Err;
		
    return pidstruct;					//����PWM�µ�ռ�ձ�ֵ
}

