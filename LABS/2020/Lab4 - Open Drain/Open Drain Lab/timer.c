


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

void TIM2_IRQHandler(void)			//TIMER 2 INTERRUPT SERVICE ROUTINE
{
	TIM2->SR&=~TIM_SR_UIF;				//clear interrupt flag in status register
	Toggle_LED();									//FLASH LED
}


#define T3ARR  1000

void Init_Timer3(void)
{
	RCC->APB1ENR|=RCC_APB1ENR_TIM3EN;		//timer 2 clock enabled
	TIM3->DIER|=TIM_DIER_UIE;						//timer uptdate interrupt enabled
	TIM3->PSC = 90-1;					// 
	TIM3->ARR = T3ARR;						//counter reload value, gives a timer period of 1s when F_APB = 90MHz and PSC = 89
	TIM3->CNT = 0;									//zero timer counter
	TIM3->CR1 &= ~TIM_CR1_DIR;		//SET COUNT UP    0: upcounter 1: downcounter
	NVIC_EnableIRQ(TIM3_IRQn);
//	NVIC_SetPriority(TIM3_IRQn,3);
	TIM3->CR1|=TIM_CR1_CEN;				//start timer counter
}
void TIM3_IRQHandler(void)			//TIMER 2 INTERRUPT SERVICE ROUTINE
{
	static unsigned int timer3cnt = 0;
	TIM3->SR&=~TIM_SR_UIF;				//clear interrupt flag in status register
	timer3cnt++;
	if (timer3cnt==100)
	{		
//		tune_update();
		Toggle_LED();
		timer3cnt =0;
	}
}


void delay (void)
{	
	unsigned int i;													//create variable
	for (i=0; i<1000000; i++);							//WAIT count to 1 million 
}

		//100ms BLOCKING DELAY
void delay_100ms_blocking(void)
{
	unsigned int i;													//increment a variable to waste time
	for(i=0; i<SystemCoreClock/180; i++);		//incrementing a variable from 0 to 4,500,000 takes 100ms when MCU speed is 180MHz
}




void delayT3_us(uint32_t time) {
		volatile uint32_t start;
		start = TIM3->CNT;
		while (((TIM3->CNT - start)&0xFFFF) < time) 
		{
//			__NOP();
		}
}


void delayT3_ms(unsigned int n)
{
 while(n)
 {
	 delayT3_us(1000);
	 n--;
 }
}
void waitT3_us (unsigned int amount){ //Uses Timer 3 counting up at 1Mhz to T3ARR

	int start =  TIM3->CNT;
	volatile int current;
	int elapsed;
	int rollover=0;
	int last = start;
	
	do
	{
		current = TIM3->CNT;
		if (last > current)											
//		if ((last-current)>0)
		{
			rollover += T3ARR - start;
			start = 0;
		}
		elapsed = (current-start) + rollover;
		last = current;
	}while (elapsed < amount);
}
	
