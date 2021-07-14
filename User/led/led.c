#include "stm32f10x.h"

//LED�˿ڳ�ʼ��
//LED1����PC14�˿ڣ�LED2����PC15�˿�
void led_init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;					//����ṹ��,��ʼ��IO�˿�

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//ʹ��PC�˿�ʱ��

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2;	//ѡ����IO�˿ڣ�PA0,PA1��PA2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;		//IO�˿ڵĹ���ģʽ���������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		//IO�˿���ߵ�������ʣ�50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);					//���ṹ��(GPIO_InitStructure)���趨д��GPIOA���üĴ���
}

//����LED1
void LED1_ON(void)
{
	GPIO_SetBits(GPIOA,GPIO_Pin_0);	//��PA0�˿��øߵ�ƽ
}

//Ϩ��LED1
void LED1_OFF(void)
{
	GPIO_ResetBits(GPIOA,GPIO_Pin_0);	//��PA0�˿��õ͵�ƽ
}

//����LED2
void LED2_ON(void)
{
	GPIO_SetBits(GPIOA,GPIO_Pin_1);	//��PA1�˿��øߵ�ƽ
}

//Ϩ��LED2
void LED2_OFF(void)
{
	GPIO_ResetBits(GPIOA,GPIO_Pin_1);	//��PA1�˿��õ͵�ƽ
}

void LED_ON_0(void)
{
	GPIO_ResetBits(GPIOA,GPIO_Pin_0|GPIO_Pin_2);
}
void LED_ON_1(void)
{
	GPIO_ResetBits(GPIOA,GPIO_Pin_1|GPIO_Pin_2);
}
void LED_ON_2(void)
{
	GPIO_ResetBits(GPIOA,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2);
}

void LED_OFF(void)
{
	GPIO_SetBits(GPIOA,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2);
}
