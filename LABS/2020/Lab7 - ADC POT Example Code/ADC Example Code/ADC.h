#ifndef _ADC_H
#define _ADC_H
#include <stm32f4xx.h>

#define ADC_input_port		GPIOA
#define ADC_input_pin			0
#define PA0_Channel				0


void init_ADC(void);
unsigned short read_adc(void);
#endif 
