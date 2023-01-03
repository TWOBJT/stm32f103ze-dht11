#include "usart.h"

int fputc(int ch,FILE *p)      //printf重定向到串口一
{
	USART_SendData(USART1,(u8)ch);         //通过外设 USART1 发送单个数据
	while (USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);   //检查 USART1的 发送完成标志位 设置与否
	return ch;
}

void USART1_Init(u32 botel)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;  //TX                 // 选择你要设置的IO口
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;          //选择输出模式（复用推挽输出）
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;         //选择输出速度
	GPIO_Init(GPIOA,&GPIO_InitStructure);                  // 初始化GPIOB
	       
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;  //RX                // 选择你要设置的IO口
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;          //选择输入模式（浮空输入）
	GPIO_Init(GPIOA,&GPIO_InitStructure);

/*****串口1初始化*******/
	
	USART_InitStructure.USART_BaudRate=botel;  //设置波特率为9600
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;   //设置字长 8位
	USART_InitStructure.USART_StopBits=USART_StopBits_1; //设置停止位 1位
	USART_InitStructure.USART_Parity=USART_Parity_No; //设置奇偶校验 无校验
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;	//设置硬件流控制（不使用硬件流控制）
	USART_InitStructure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;  //模式选择，输出输入模式
	
	USART_Init(USART1,&USART_InitStructure);
	
	USART_Cmd(USART1,ENABLE);
	
/********设置串口中断类型并使能**********/

    
    USART_ClearFlag(USART1,USART_FLAG_TC);         //清除 发送完成中断标志位
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);  //接收中断配置
	
	NVIC_InitStructure.NVIC_IRQChannel=USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=3;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
}
	 
void USART1_IRQHandler(void)
      { 
 		u8 r;
		if(USART_GetITStatus(USART1,USART_IT_RXNE)!=RESET)  //检查串口1的接收中断是否发生
		{
			r=USART_ReceiveData(USART1);      //返回 USART1 最近接收到的数据
			USART_SendData(USART1,r);         //通过外设 USART1 发送单个数据
			while (USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);   //检查 USART1的 发送完成标志位 设置与否

		}
		USART_ClearFlag(USART1,USART_FLAG_TC);
	
       }

