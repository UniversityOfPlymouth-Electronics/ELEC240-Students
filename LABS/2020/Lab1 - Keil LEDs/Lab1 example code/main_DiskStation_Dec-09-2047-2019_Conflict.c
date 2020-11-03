#include <stm32f4xx.h>		//INCLUDE THE HEADER FILE FOR THIS MCU FAMILY
															//this file contains the definitions for register addresses and values etc...


int main(void)
{
	int i;																// variable used for counting in delay
	unsigned char value=0;								// variable to use in watch window {local to main}
																				// if this variable is outside main then you will not be able to view
	
		//ENABLE PORT(S)
	RCC->AHB1ENR|=RCC_AHB1ENR_GPIOBEN;		//GPIO B clock enable
	
			//CONFIGURE PORT PIN FUNCTIONS
	GPIOB->MODER =(1<<(2*0));							//set new pin functions on GPIOB0

	while(1)		//ENTER 'FOREVER' LOOP - THIS LOOP WILL NEVER EXIT
	{
		GPIOB->ODR=(1<<0);									//LED ON 
		for(i=0;i<3000000;i++);  						//delay
		GPIOB->ODR=0;												//LED OFF
		for(i=0;i<3000000;i++);  						//delay
		
		value++;
		if (value > 10)
		{
			value=0;
		}
	}
}
