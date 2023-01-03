#include "usart.h"

int fputc(int ch,FILE *p)      //printf�ض��򵽴���һ
{
	USART_SendData(USART1,(u8)ch);         //ͨ������ USART1 ���͵�������
	while (USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);   //��� USART1�� ������ɱ�־λ �������
	return ch;
}

void USART1_Init(u32 botel)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;  //TX                 // ѡ����Ҫ���õ�IO��
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;          //ѡ�����ģʽ���������������
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;         //ѡ������ٶ�
	GPIO_Init(GPIOA,&GPIO_InitStructure);                  // ��ʼ��GPIOB
	       
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;  //RX                // ѡ����Ҫ���õ�IO��
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;          //ѡ������ģʽ���������룩
	GPIO_Init(GPIOA,&GPIO_InitStructure);

/*****����1��ʼ��*******/
	
	USART_InitStructure.USART_BaudRate=botel;  //���ò�����Ϊ9600
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;   //�����ֳ� 8λ
	USART_InitStructure.USART_StopBits=USART_StopBits_1; //����ֹͣλ 1λ
	USART_InitStructure.USART_Parity=USART_Parity_No; //������żУ�� ��У��
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;	//����Ӳ�������ƣ���ʹ��Ӳ�������ƣ�
	USART_InitStructure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;  //ģʽѡ���������ģʽ
	
	USART_Init(USART1,&USART_InitStructure);
	
	USART_Cmd(USART1,ENABLE);
	
/********���ô����ж����Ͳ�ʹ��**********/

    
    USART_ClearFlag(USART1,USART_FLAG_TC);         //��� ��������жϱ�־λ
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);  //�����ж�����
	
	NVIC_InitStructure.NVIC_IRQChannel=USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=3;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
}
	 
void USART1_IRQHandler(void)
      { 
 		u8 r;
		if(USART_GetITStatus(USART1,USART_IT_RXNE)!=RESET)  //��鴮��1�Ľ����ж��Ƿ���
		{
			r=USART_ReceiveData(USART1);      //���� USART1 ������յ�������
			USART_SendData(USART1,r);         //ͨ������ USART1 ���͵�������
			while (USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);   //��� USART1�� ������ɱ�־λ �������

		}
		USART_ClearFlag(USART1,USART_FLAG_TC);
	
       }

