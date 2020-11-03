#include <stm32f4xx.h>		//INCLUDE THE HEADER FILE FOR THIS MCU FAMILY
													//this file contains the definitions for register addresses and values etc...

void delay (void)
{	
	unsigned int i;		//create variable
	for (i=0; i<1000000; i++);		//WAIT count to 1 million 
}

void LED_INIT (void)
{
	//ENABLE PORT(S)
	//RCC->AHB1ENR |= 0x02;						//use label defined in stm32f4.h instead of hex value: easier to read and change
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;	//ONLY GPIO B clock enable
	
	//CONFIGURE PORT:GPIOB  PIN:0 TO OUTPUT for LED1
	GPIOB->MODER |= 0x01;						//ONLY set  GPIOB0
	// the above assumes that bit 1 is to zero to make port output (ie 01 in MODER0 bits)
	GPIOB->MODER &= ~0x02;					//ONLY clear GPIOB1 : lets not make assumptions!!!!
}	

void LED_ON (void)
{
			GPIOB->ODR |= 1;							//ONLY TURN LED ON
}

void LED_OFF (void)
{
			GPIOB->ODR &= ~1;							//ONLY TURN LED ON
}



int main(void)					// MAIN PROGRAM
{
	LED_INIT();

	while(1)		//ENTER 'FOREVER' LOOP - THIS LOOP WILL NEVER EXIT
	{
		LED_ON();												//ONLY TURN LED ON
		delay();											// DELAY
		LED_OFF();											//ONLY TURN LED OFF
		delay();											// DELAY
	}
}
