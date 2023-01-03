#ifndef _led_H
#define _led_H

#include "stm32f10x.h"

#define LED_PORT_RCC   RCC_APB2Periph_GPIOB
#define LED_PIN        GPIO_Pin_5
#define LED_PORT       GPIOB
      
void LED_Init(void);

#define led1 PEout(5)
#define led2 PBout(5)
#endif
