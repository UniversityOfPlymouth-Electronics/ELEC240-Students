#include <stm32f4xx.h>		//INCLUDE THE HEADER FILE FOR THIS MCU FAMILY
															//this file contains the definitions for register addresses and values etc...

void delay (void)
{
	volatile int i;																// variable used for counting in delay			
	for(i=0;i<3000000;i++){__NOP();}  		//count up to big number
}

int main(void)
{

		//ENABLE PORT(S)
	RCC->AHB1ENR|=RCC_AHB1ENR_GPIOBEN;		//GPIO B clock enable
	
			//CONFIGURE PORT PIN FUNCTIONS
	GPIOB->MODER |=(1UL<<(2*0));					//set new pin functions on GPIOB0

	while(1)		//ENTER 'FOREVER' LOOP - THIS LOOP WILL NEVER EXIT
	{
		GPIOB->ODR |=(1UL<<0);							//LED ON 
		delay();													  //delay
		GPIOB->ODR &=~(1UL<<0);							//LED OFF
		delay();													  //delay
	}
}
