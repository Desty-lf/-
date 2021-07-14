#include "stm32f10x.h"

//LED端口初始化
//LED1连接PC14端口，LED2连接PC15端口
void led_init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;					//定义结构体,初始化IO端口

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//使能PC端口时钟

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2;	//选定的IO端口：PA0,PA1、PA2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;		//IO端口的工作模式：推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		//IO端口最高的输出速率：50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);					//将结构体(GPIO_InitStructure)的设定写入GPIOA配置寄存器
}

//点亮LED1
void LED1_ON(void)
{
	GPIO_SetBits(GPIOA,GPIO_Pin_0);	//将PA0端口置高电平
}

//熄灭LED1
void LED1_OFF(void)
{
	GPIO_ResetBits(GPIOA,GPIO_Pin_0);	//将PA0端口置低电平
}

//点亮LED2
void LED2_ON(void)
{
	GPIO_SetBits(GPIOA,GPIO_Pin_1);	//将PA1端口置高电平
}

//熄灭LED2
void LED2_OFF(void)
{
	GPIO_ResetBits(GPIOA,GPIO_Pin_1);	//将PA1端口置低电平
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
