#include "gpio.h"

void Init_LED(void)
{
	//ENABLE PORT(S)
	RCC->AHB1ENR|=RCC_AHB1ENR_GPIOBEN;		//GPIO B clock enable
	
	
//		//CONFIGURE PORT:GPIOB  PIN:0 TO OUTPUT for LED1
//	GPIOB->MODER |= 0x01;						//ONLY set  GPIOB0
//	// the above assumes that bit 1 is to zero
//	GPIOB->MODER &= ~0x02;					//ONLY clear GPIOB1
	
	//CONFIGURE PORT PIN FUNCTIONS
	GPIOB->MODER&=~(3u<<(2*0));						//clear pin functions on GPIOB
	GPIOB->MODER|=(1u<<(2*0));						//set new pin functions on GPIOB
}	
	

void Toggle_LED (void)
{
	GPIOB->ODR^=(1u<<0);								//XOR GPIOB output data register to invert the selected pin
}



void LED_ON (void)
{
//			GPIOB->ODR |= (1<<0);							//ONLY TURN LED ON
			GPIOB->BSRR = (1<<0);							//ONLY TURN LED ON
}

void LED_OFF (void)
{
//			GPIOB->ODR &= ~1;							//ONLY TURN LED ON
			GPIOB->BSRR = (1<<(1+16));							//ONLY TURN LED ON
}

