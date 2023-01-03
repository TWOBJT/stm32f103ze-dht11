#ifndef _dht11_H
#define _dht11_H

#include "gpioweidai.h"
#include "SysTick.h"


#define DHT11 (GPIO_Pin_11) //PG11
#define GPIO_DHT11 GPIOG

#define DHT11_DQ_IN PGin(11)	  //����
#define DHT11_DQ_OUT PGout(11)  //���

void DHT11_IO_OUT(void);
void DHT11_IO_IN(void);
u8 DHT11_Init(void);
void DHT11_Rst(void);
u8 DHT11_Check(void);
u8 DHT11_Read_Bit(void);
u8 DHT11_Read_Byte(void);
u8 DHT11_Read_Data(u8 *temp,u8 *humi);


#endif


