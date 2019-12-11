#include <stm32f4xx.h>		//INCLUDE THE HEADER FILE FOR THIS MCU FAMILY
													//this file contains the definitions for register addresses and values etc...

void delay (void)
{	
	unsigned int i;		//create variable
	for (i=0; i<1000000; i++){__NOP();}		//WAIT count to 1 million 
}

int main(void)					// MAIN PROGRAM
{
	//ENABLE PORT(S)
	RCC->AHB1ENR |= 0x02;						//ONLY GPIO B clock enable
	
	//CONFIGURE PORT:GPIOB  PIN:0 TO OUTPUT for LED1
	GPIOB->MODER |= 0x01;						//ONLY set new pin functions on GPIOB0

	while(1)		//ENTER 'FOREVER' LOOP - THIS LOOP WILL NEVER EXIT
	{
		GPIOB->ODR |= 1;							//ONLY TURN LED ON
		delay();											// DELAY
		GPIOB->ODR &= ~1;							//ONLY TURN LED OFF
		delay();											// DELAY
	}
}
