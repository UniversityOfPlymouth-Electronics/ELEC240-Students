#include <stm32f4xx.h>		//INCLUDE THE HEADER FILE FOR THIS MCU FAMILY
															//this file contains the definitions for register addresses and values etc...


int main(void)
{
volatile	int i;												// variable used for counting in delay
	
		//ENABLE PORT(S)
	RCC->AHB1ENR|=RCC_AHB1ENR_GPIOBEN;		//TURN ON ONLY GPIO B clock enable (LED on PB0)
	
			//CONFIGURE PORT PIN FUNCTIONS
	GPIOB->MODER =(1<<(2*0));							//set new pin functions on GPIOB  PB0

	while(1)															//ENTER 'FOREVER' LOOP - THIS LOOP WILL NEVER EXIT (otherwise CPU resets)
	{
		GPIOB->ODR=(1<<0);									//LED ON 
		for(i=0;i<1000000;i++)							//delay
			{__nop();} 												// put assembly language nooperation in body of loop else compiler removes loop
		GPIOB->ODR=0;												//LED OFF
		for(i=0;i<1000000;i++) {__NOP();} 	//delay: NOP case insensative else compiler optimises empty loop and removes delay
	
	}
}
