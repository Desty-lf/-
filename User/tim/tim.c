#include "stm32f10x.h"
#include "led.h"
#include "key.h"

//TIM6中断通道初始化函数
void TIM6_IRQ_init(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;					//定义结构体，配置中断通道优先级
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM6_IRQn;			//选定中断通道：定时器6中断（TIM6_IRQn）
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;	//该中断通道抢占优先级：1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0;		//该中断通道响应优先级：0
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;			//使能该中断通道
	NVIC_Init(&NVIC_InitStructure);							//将结构体(NVIC_InitStructture)的设定写入NVIC控制寄存器
}

//TIM6初始化函数
void tim6_init(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;		//定义结构体，初始化定时器

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);	//使能定时器6（TIM6）时钟
	
	TIM_TimeBaseInitStructure.TIM_Prescaler=71;				//定时器时钟预分频值：72-1=71。取值范围：0~65535
	TIM_TimeBaseInitStructure.TIM_Period=49999;				//定时器计数阈值：50000-1=49999。取值范围：0~65535
	TIM_TimeBaseInit(TIM6, &TIM_TimeBaseInitStructure);		//将结构体(TIM_TimeBaseInitStructture)的设定写入TIM6配置寄存器。定时器将以72MHz/72/50000=20Hz的频率重复计数
	
	TIM_ITConfig(TIM6, TIM_IT_Update, ENABLE);				//使能定时器6（TIM6）的计数溢出中断（TIM_IT_Update）
	TIM_Cmd(TIM6, ENABLE);									//使能定时器6：TIM6按照上述设定开始工作
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

u8 DutyCycle=50;	//定义PWM波占空比，设定范围：0-1005
u8 Duty=50;
u8 flag=0;
u8 space=10;
u8 key2=0;
//定时器6（TIM6）的中断服务函数
//此函数无需被其他函数调用，无需输入参数
void TIM6_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM6, TIM_IT_Update) != RESET)		//判断定时器6（TIM6）是否发生计数溢出中断（TIM_IT_Update）
	{
		if(KEY1_STATUS()==0)
		{
			while(KEY1_STATUS()==0);
			space=(space+10)%50+5;//按键1按下时，PWM波占空比（DutyCycle）增加
		}
	    
		if(KEY2_STATUS()==0)
		{
			while(KEY2_STATUS()==0);
			flag=(flag+1)%3;
		}
		
		Duty=(Duty+space)%200;
		if(Duty>=0&&Duty<=100)	DutyCycle=Duty;
		else	DutyCycle=200-Duty;	
		TIM_ClearITPendingBit(TIM6, TIM_IT_Update);			//清除定时器6（TIM6）的计数溢出中断（TIM_IT_Update）标志。如未清除，将重复进入此中断服务函数
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
