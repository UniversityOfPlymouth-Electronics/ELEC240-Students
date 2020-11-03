#include <stm32f4xx.h>		//INCLUDE THE HEADER FILE FOR THIS MCU FAMILY
													//this file contains the definitions for register addresses and values etc...
#include "PLL_Config.c"
#include "gpio.c"
#include "timer.c"

int main(void)
{
	PLL_Config();									// Set system clock to 180MHz
	SystemCoreClockUpdate();			// Update SystemCoreClock
	Init_LED();										// Initialise LED
	Init_Timer2();								// Initialise Timer
	
	while(1)											//ENTER 'FOREVER' LOOP - THIS LOOP WILL NEVER EXIT
	{
																//FOREVER LOOP IS NOW EMPTY (MCU CAN BE PUT TO SLEEP HERE)
	}															//END OF FOREVER LOOP
}//end main



