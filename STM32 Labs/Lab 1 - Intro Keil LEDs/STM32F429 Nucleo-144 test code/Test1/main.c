#include <stm32f4xx.h>		//INCLUDE THE HEADER FILE FOR THIS MCU FAMILY
															//this file contains the definitions for register addresses and values etc...


int main(void)
{
	volatile int i;																// variable used for counting in delay
		//ENABLE PORT(S)
	RCC->AHB1ENR|=RCC_AHB1ENR_GPIOBEN;		//GPIO B clock enable
	
			//CONFIGURE PORT PIN FUNCTIONS
	GPIOB->MODER =(1<<(2*0));							//set new pin functions on GPIOB0

	while(1)		//ENTER 'FOREVER' LOOP - THIS LOOP WILL NEVER EXIT
	{
		GPIOB->ODR=(1<<0);					//LED ON 
		for(i=0;i<3000000;i++){__NOP();}  	//delay
		GPIOB->ODR=0;						//LED OFF
		for(i=0;i<3000000;i++){__NOP();} 	//delay
	}
}
