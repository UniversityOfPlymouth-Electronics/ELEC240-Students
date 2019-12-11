#include "gpio.h"

void Init_LED(void)
{
	//ENABLE PORT(S)
	RCC->AHB1ENR|=RCC_AHB1ENR_GPIOBEN;		//GPIO B clock enable
	
	//CONFIGURE PORT PIN FUNCTIONS
	GPIOB->MODER&=~(3u<<(2*0));						//clear pin functions on GPIOB
	GPIOB->MODER|=(1u<<(2*0));						//set new pin functions on GPIOB
}	
	

void Toggle_LED (void)
{
	GPIOB->ODR^=(1u<<0);								//XOR GPIOB output data register to invert the selected pin
}
