#include "PLL_Config.c"
#include <stm32f4xx.h>		//INCLUDE THE HEADER FILE FOR THIS MCU FAMILY
															//this file contains the definitions for register addresses and values etc...

		//100ms BLOCKING DELAY
void delay_100ms_blocking(void)
{
	unsigned int i;				//increment a variable to waste time
	for(i=0; i<SystemCoreClock/40; i++);		//incrementing a variable from 0 to 3,000,000 takes 100ms when MCU speed is 180MHz
}

int main(void)
{
	PLL_Config();
	SystemCoreClockUpdate();
	
		//ENABLE PORT(S)
	RCC->AHB1ENR|=RCC_AHB1ENR_GPIOBEN;		//GPIO B clock enable
	
			//CONFIGURE PORT PIN FUNCTIONS
	GPIOB->MODER&=~(3u<<(2*0));	//clear pin functions on GPIOB0
	GPIOB->MODER=(1u<<(2*0));	//set new pin functions on GPIOB0

	while(1)		//ENTER 'FOREVER' LOOP - THIS LOOP WILL NEVER EXIT
	{
		GPIOB->ODR=(1u<<0);				//set GPIOB pins high (write to lower bit0 of ODR register and set it high)
		delay_100ms_blocking();		//call the delay subroutine (defined above)
		GPIOB->ODR=0;							//set GPIOB pins low
		delay_100ms_blocking();		//call the delay subroutine (defined above)
	}
}
