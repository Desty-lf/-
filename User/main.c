//#include "stm32f10x.h"
#include "delay.h"
#include "led.h"
#include "key.h"
#include "tim.h"

int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//配置中断优先级的分组方式
	delay_init();
	led_init();
	key_init();
	TIM6_IRQ_init();	//初始化TIM6中断通道
	tim6_init();		//初始化TIM6
	TIM7_IRQ_init();
	tim7_init();
	
	while(1)
	{	

	}
}
