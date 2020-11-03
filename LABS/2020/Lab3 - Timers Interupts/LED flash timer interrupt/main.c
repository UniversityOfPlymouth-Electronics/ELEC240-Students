#include <stm32f4xx.h>		//INCLUDE THE HEADER FILE FOR THIS MCU FAMILY
													//this file contains the definitions for register addresses and values etc...
#include "PLL_Config.c"
#include "gpio.c"

void Init_Timer2(void)
{
	RCC->APB1ENR|=RCC_APB1ENR_TIM2EN;		//timer 2 clock enabled
	TIM2->DIER|=TIM_DIER_UIE;						//timer uptdate interrupt enabled
																			//APB clock is Fcy/2 = 180MHz/2 = 90MHz
	TIM2->PSC=256-1;										//divide APB clock by 256 = 90MHz/256 = 351kHz
	TIM2->ARR=35156;										//counter reload value, gives a timer period of 100ms when F_APB = 90MHz and PSC = 256
	TIM2->CNT=0;												//zero timer counter
	NVIC->ISER[0]|=(1u<<28);						//timer 2 global interrupt enabled
	TIM2->CR1|=TIM_CR1_CEN;							//start timer counter
}



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


void TIM2_IRQHandler(void)			//TIMER 2 INTERRUPT SERVICE ROUTINE
{
	TIM2->SR&=~TIM_SR_UIF;				//clear interrupt flag in status register
	Toggle_LED();									//FLASH LED
}


