#include "stm32f10x.h"

//�����˿ڳ�ʼ��
//KEY1����PC12�˿ڣ�KEY2����PC13�˿�
void key_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;					//����ṹ��,��ʼ��IO�˿�

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	//ʹ��PC�˿�ʱ��

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13;	//ѡ����IO�˿ڣ�PC12��PC13
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;			//IO�˿ڵĹ���ģʽ����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		//IO�˿���ߵ�������ʣ�50MHz
	GPIO_Init(GPIOC, &GPIO_InitStructure);					//���ṹ��(GPIO_InitStructure)���趨д��GPIOC���üĴ���
}
 
//����KEY1״̬
//return 0��PC12�˿�Ϊ�͵�ƽ��KEY1������
//return 1��PC12�˿�Ϊ�ߵ�ƽ��KEY1δ������
int KEY1_STATUS(void)
{
	u8 status;
	status=GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_12);		//��ȡPC12�˿ڵ�ƽ
	return(status);
}

//����KEY2״̬
//return 0��PC13�˿�Ϊ�͵�ƽ��KEY2������
//return 1��PC13�˿�Ϊ�ߵ�ƽ��KEY2δ������
int KEY2_STATUS(void)
{
	u8 status;
	status=GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_13);		//��ȡPC13�˿ڵ�ƽ
	return(status);
}

int KEY_COLOR()
{
	int flag=0;
	if(KEY2_STATUS()==0)
		flag=(flag+1)%4;
	return flag;
}



