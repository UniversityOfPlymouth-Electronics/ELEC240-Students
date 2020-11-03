#include "delay.h"

#define DEBUG_BREAK           __asm__("BKPT #0");
/* Counts 1ms timeTicks */


volatile uint32_t msTicks = 0;


void Init_Timer3(void){
	RCC->APB1ENR|=RCC_APB1ENR_TIM3EN;		//timer 3 clock enabled
	TIM3->DIER|=TIM_DIER_UIE;						//timer uptdate interrupt enabled
	TIM3->PSC= us_count-1;							// Timer 3 with 1Mhz so count is in us
	TIM3->ARR=0xffff;										//counter reload value, gives a timer period 
	TIM3->CNT=0;												//zero timer counter
	TIM3->CR1 &= ~TIM_CR1_DIR;					//0: upcounter 1: downcounter
//	NVIC->ISER[0]|=(1u<<29);					//timer 3 global interrupt enabled
	TIM3->CR1|=TIM_CR1_CEN;		//start timer counter
}


void delayus(unsigned int n) {
		uint32_t start;
		start = TIM3->CNT;
		while (((TIM3->CNT - start)&0xFFFF) < n);
}

void delayms(unsigned int n) {

		while (n){
			delayus(1000);
			n--;
		}
}

void Init_Systick (void) {
	 if (SysTick_Config(ms_count))					// One SysTick interrupt now equals 1ms
      {
            DEBUG_BREAK;
      }
}

void Delay(uint32_t dlyTicks)
{
      uint32_t curTicks;
 
      curTicks = msTicks;
      while ((msTicks - curTicks) < dlyTicks)
			{
			//	__WFI();
			}
}
 
void SysTick_Handler(void)
{
      /* Increment counter necessary in Delay()*/
      msTicks++;
}

