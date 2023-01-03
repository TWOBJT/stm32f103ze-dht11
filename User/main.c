#include "gpioweidai.h"
#include "LED.h"
#include "SysTick.h"
#include "usart.h"
#include "dht11.h"

void data_pros()	//数据处理函数
{
	u8 temp;  	    
	u8 humi;
	DHT11_Read_Data(&temp,&humi);
	printf("温度=%d°C  湿度=%d%%RH\r\n",temp,humi);
}

int main()
{
	u8 i=0;
	SysTick_Init(72);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  //中断优先级分组 分2组
	LED_Init();
	USART1_Init(115200);
	while(DHT11_Init())	//检测dht11是否存在
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
			data_pros();  	 //读取一次DHT11数据最少要大于100ms
		}
		
		delay_ms(100);		
	}
}




