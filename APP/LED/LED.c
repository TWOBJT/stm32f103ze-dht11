#include "LED.h"
void LED_Init()
{
 
	GPIO_InitTypeDef GPIO_InitStructure;                    //定义结构体变量
	RCC_APB2PeriphClockCmd(LED_PORT_RCC,ENABLE);            //初始化GPIOB端口使能时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);    //初始化GPIOE端口使能时钟
	
	GPIO_InitStructure.GPIO_Pin=LED_PIN|GPIO_Pin_6;                   // 选择你要设置的IO口
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;          //选择输出模式（推挽输出）
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;         //选择输出速度
	GPIO_Init(GPIOB,&GPIO_InitStructure);                  // 初始化GPIOB
	GPIO_Init(GPIOE,&GPIO_InitStructure);                  // 初始化GPIOE
	GPIO_SetBits(LED_PORT,LED_PIN);                         //设置管脚输出点平（高电平）B
	GPIO_SetBits(GPIOE,LED_PIN);                             //设置管脚输出点平（高电平）E
	GPIO_SetBits(GPIOE,GPIO_Pin_6);
}
