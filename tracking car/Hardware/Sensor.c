#include "stm32f10x.h"                  // Device header

//pa4567  pb034 ��紫�������ж������к��߾ͷ���1

void Sensor_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
	 

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_3 | GPIO_Pin_4;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
}

uint8_t* read_sensor(void)//���⴫����ʶ�𵽺��߷��������źŵ͵�ƽ0��δʶ�𵽺��߷��ظߵ�ƽ1
{
	static uint8_t sensor[7];
	/*��λ�ô�����˳�����ҵĴ��������ص������ź����δ�������sensor[0��8]��*/
	sensor[0]=GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4);//����Ĵ�����
	sensor[1]=GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5);
	sensor[2]=GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6);
	sensor[3]=GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_7);//����Ĵ�����
	sensor[4]=GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0);
	sensor[5]=GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_3);
	sensor[6]=GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_4);
	return sensor;
}

