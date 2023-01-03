#include "gpioweidai.h"
#include "LED.h"
#include "SysTick.h"
#include "usart.h"
#include "dht11.h"

void data_pros()	//���ݴ�����
{
	u8 temp;  	    
	u8 humi;
	DHT11_Read_Data(&temp,&humi);
	printf("�¶�=%d��C  ʪ��=%d%%RH\r\n",temp,humi);
}

int main()
{
	u8 i=0;
	SysTick_Init(72);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  //�ж����ȼ����� ��2��
	LED_Init();
	USART1_Init(115200);
	while(DHT11_Init())	//���dht11�Ƿ����
	{
		printf("DHT11 Check Error!\r\n");
		delay_ms(500);		
	}
	printf("DHT11 Check OK!\r\n");
	while(1)
	{
		i++;
		if(i%20==0)
		{
			led1=!led1;
			data_pros();  	 //��ȡһ��DHT11��������Ҫ����100ms
		}
		
		delay_ms(100);		
	}
}




