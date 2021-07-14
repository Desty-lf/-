//#include "stm32f10x.h"
#include "delay.h"
#include "led.h"
#include "key.h"
#include "tim.h"

int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//�����ж����ȼ��ķ��鷽ʽ
	delay_init();
	led_init();
	key_init();
	TIM6_IRQ_init();	//��ʼ��TIM6�ж�ͨ��
	tim6_init();		//��ʼ��TIM6
	TIM7_IRQ_init();
	tim7_init();
	
	while(1)
	{	

	}
}
