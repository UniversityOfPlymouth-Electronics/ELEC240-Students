#include <stm32f4xx.h>		//INCLUDE THE HEADER FILE FOR THIS MCU FAMILY
													//this file contains the definitions for register addresses and values etc...


int main(void)					// MAIN PROGRAM
{
	unsigned int i;		//create variable
	
	//ENABLE PORT(S)
	RCC->AHB1ENR = 0x02;		//GPIO B clock enable
	
	//CONFIGURE PORT:GPIOB  PIN:0 TO OUTPUT for LED1
	GPIOB->MODER = 0x01;	//set new pin functions on GPIOB0

	while(1)		//ENTER 'FOREVER' LOOP - THIS LOOP WILL NEVER EXIT
	{
		GPIOB->ODR = 1;								//TURN LED ON
		for (i=0; i<1000000; i++){__NOP();}		//WAIT count to 1 million 
		GPIOB->ODR=0;									//TURN L£ED OFF
		for (i=0; i<1000000; i++){__NOP();}		//WAIT by count to 1 million 
	}
}
