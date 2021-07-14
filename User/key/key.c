#include "stm32f10x.h"

//按键端口初始化
//KEY1连接PC12端口，KEY2连接PC13端口
void key_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;					//定义结构体,初始化IO端口

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	//使能PC端口时钟

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13;	//选定的IO端口：PC12、PC13
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;			//IO端口的工作模式：上拉输入
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		//IO端口最高的输出速率：50MHz
	GPIO_Init(GPIOC, &GPIO_InitStructure);					//将结构体(GPIO_InitStructure)的设定写入GPIOC配置寄存器
}
 
//返回KEY1状态
//return 0：PC12端口为低电平，KEY1被按下
//return 1：PC12端口为高电平，KEY1未被按下
int KEY1_STATUS(void)
{
	u8 status;
	status=GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_12);		//读取PC12端口电平
	return(status);
}

//返回KEY2状态
//return 0：PC13端口为低电平，KEY2被按下
//return 1：PC13端口为高电平，KEY2未被按下
int KEY2_STATUS(void)
{
	u8 status;
	status=GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_13);		//读取PC13端口电平
	return(status);
}

int KEY_COLOR()
{
	int flag=0;
	if(KEY2_STATUS()==0)
		flag=(flag+1)%4;
	return flag;
}



