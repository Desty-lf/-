#include "stm32f10x.h"
#include "led.h"
#include "key.h"

//TIM6�ж�ͨ����ʼ������
void TIM6_IRQ_init(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;					//����ṹ�壬�����ж�ͨ�����ȼ�
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM6_IRQn;			//ѡ���ж�ͨ������ʱ��6�жϣ�TIM6_IRQn��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;	//���ж�ͨ����ռ���ȼ���1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0;		//���ж�ͨ����Ӧ���ȼ���0
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;			//ʹ�ܸ��ж�ͨ��
	NVIC_Init(&NVIC_InitStructure);							//���ṹ��(NVIC_InitStructture)���趨д��NVIC���ƼĴ���
}

//TIM6��ʼ������
void tim6_init(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;		//����ṹ�壬��ʼ����ʱ��

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);	//ʹ�ܶ�ʱ��6��TIM6��ʱ��
	
	TIM_TimeBaseInitStructure.TIM_Prescaler=71;				//��ʱ��ʱ��Ԥ��Ƶֵ��72-1=71��ȡֵ��Χ��0~65535
	TIM_TimeBaseInitStructure.TIM_Period=49999;				//��ʱ��������ֵ��50000-1=49999��ȡֵ��Χ��0~65535
	TIM_TimeBaseInit(TIM6, &TIM_TimeBaseInitStructure);		//���ṹ��(TIM_TimeBaseInitStructture)���趨д��TIM6���üĴ�������ʱ������72MHz/72/50000=20Hz��Ƶ���ظ�����
	
	TIM_ITConfig(TIM6, TIM_IT_Update, ENABLE);				//ʹ�ܶ�ʱ��6��TIM6���ļ�������жϣ�TIM_IT_Update��
	TIM_Cmd(TIM6, ENABLE);									//ʹ�ܶ�ʱ��6��TIM6���������趨��ʼ����
}

void TIM7_IRQ_init(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;			
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM7_IRQn;		
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

void tim7_init(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);
	
	TIM_TimeBaseInitStructure.TIM_Prescaler=71;
	TIM_TimeBaseInitStructure.TIM_Period=99;
	TIM_TimeBaseInit(TIM7, &TIM_TimeBaseInitStructure);
	
	TIM_ITConfig(TIM7, TIM_IT_Update, ENABLE);
	TIM_Cmd(TIM7, ENABLE);
}

u8 DutyCycle=50;	//����PWM��ռ�ձȣ��趨��Χ��0-1005
u8 Duty=50;
u8 flag=0;
u8 space=10;
u8 key2=0;
//��ʱ��6��TIM6�����жϷ�����
//�˺������豻�����������ã������������
void TIM6_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM6, TIM_IT_Update) != RESET)		//�ж϶�ʱ��6��TIM6���Ƿ�����������жϣ�TIM_IT_Update��
	{
		if(KEY1_STATUS()==0)
		{
			while(KEY1_STATUS()==0);
			space=(space+10)%50+5;//����1����ʱ��PWM��ռ�ձȣ�DutyCycle������
		}
	    
		if(KEY2_STATUS()==0)
		{
			while(KEY2_STATUS()==0);
			flag=(flag+1)%3;
		}
		
		Duty=(Duty+space)%200;
		if(Duty>=0&&Duty<=100)	DutyCycle=Duty;
		else	DutyCycle=200-Duty;	
		TIM_ClearITPendingBit(TIM6, TIM_IT_Update);			//�����ʱ��6��TIM6���ļ�������жϣ�TIM_IT_Update����־����δ��������ظ�������жϷ�����
	}
}

u8 count=0;

void TIM7_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM7, TIM_IT_Update) != RESET)
	{
			if (count<DutyCycle)	
			{
				if(flag==0)	LED_ON_0();
				if(flag==1)	LED_ON_1();
				if(flag==2)	LED_ON_2();
			}
			else	LED_OFF();	
			count++;
			if(count==100)	count=0;
		
		TIM_ClearITPendingBit(TIM7, TIM_IT_Update);
	}
}
