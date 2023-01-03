#include "LED.h"
void LED_Init()
{
 
	GPIO_InitTypeDef GPIO_InitStructure;                    //����ṹ�����
	RCC_APB2PeriphClockCmd(LED_PORT_RCC,ENABLE);            //��ʼ��GPIOB�˿�ʹ��ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);    //��ʼ��GPIOE�˿�ʹ��ʱ��
	
	GPIO_InitStructure.GPIO_Pin=LED_PIN|GPIO_Pin_6;                   // ѡ����Ҫ���õ�IO��
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;          //ѡ�����ģʽ�����������
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;         //ѡ������ٶ�
	GPIO_Init(GPIOB,&GPIO_InitStructure);                  // ��ʼ��GPIOB
	GPIO_Init(GPIOE,&GPIO_InitStructure);                  // ��ʼ��GPIOE
	GPIO_SetBits(LED_PORT,LED_PIN);                         //���ùܽ������ƽ���ߵ�ƽ��B
	GPIO_SetBits(GPIOE,LED_PIN);                             //���ùܽ������ƽ���ߵ�ƽ��E
	GPIO_SetBits(GPIOE,GPIO_Pin_6);
}
