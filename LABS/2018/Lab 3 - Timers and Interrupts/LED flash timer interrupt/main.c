#include <stm32f4xx.h>		//INCLUDE THE HEADER FILE FOR THIS MCU FAMILY
															//this file contains the definitions for register addresses and values etc...
#include "PLL_Config.c"
int main(void)
{
	PLL_Config();
	SystemCoreClockUpdate();
		//ENABLE PORT(S)
	RCC->AHB1ENR|=RCC_AHB1ENR_GPIOBEN;		//GPIO B clock enable
	
			//CONFIGURE PORT PIN FUNCTIONS
	GPIOB->MODER&=~(3u<<(2*0));		//clear pin functions on GPIOB
	GPIOB->MODER|=(1u<<(2*0));		//set new pin functions on GPIOB
	
	RCC->APB1ENR|=RCC_APB1ENR_TIM2EN;		//timer 2 clock enabled
	TIM2->DIER|=TIM_DIER_UIE;						//timer uptdate interrupt enabled
			//APB clock is Fcy/2 = 180MHz/2 = 90MHz
	TIM2->PSC=256-1;						//divide APB clock by 256 = 90MHz/256 = 351kHz
	TIM2->ARR=35156;					//counter reload value, gives a timer period of 100ms when F_APB = 90MHz and PSC = 256
	TIM2->CNT=0;							//zero timer counter
	NVIC->ISER[0]|=(1u<<28);		//timer 2 global interrupt enabled
	TIM2->CR1|=TIM_CR1_CEN;		//start timer counter
	
	while(1)		//ENTER 'FOREVER' LOOP - THIS LOOP WILL NEVER EXIT
	{
				//FOREVER LOOP IS NOW EMPTY (MCU CAN BE PUT TO SLEEP HERE)
	}//END OF FOREVER LOOP
}//end main


void TIM2_IRQHandler(void)			//TIMER 2 INTERRUPT SERVICE ROUTINE
{
	TIM2->SR&=~TIM_SR_UIF;			//clear interrupt flag in status register
	
	GPIOB->ODR^=(1u<<0);		//XOR GPIOB output data register to invert the selected pin
}

