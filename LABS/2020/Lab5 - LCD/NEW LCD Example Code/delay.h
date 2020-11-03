#ifndef __DELAY_H
#define __DELAY_H
//#include <stm32f4xx.h>

#define timer_clk  SystemCoreClock/2
#define ms_count 	SystemCoreClock/1000   
#define	us_count 		timer_clk/1000000

void Init_Timer3(void);
void delayus(unsigned int n);
void Delay(uint32_t dlyTicks);

#endif

