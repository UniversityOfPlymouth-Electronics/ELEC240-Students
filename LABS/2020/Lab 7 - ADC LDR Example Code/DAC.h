#ifndef _DAC_H
#define _DAC_H
#include <stm32f4xx.h>

#define DAC_port	GPIOA
#define DAC_pin		5

void init_DAC(void);
void output_dac(unsigned short d);

#endif
