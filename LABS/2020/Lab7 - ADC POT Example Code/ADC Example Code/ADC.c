#include "ADC.h"



void init_ADC(void)
{
	RCC->AHB1ENR|=RCC_AHB1ENR_GPIOAEN;	//GPIO clock enable
	ADC_input_port->MODER|=(3u<<(2*ADC_input_pin));	//ADC input pin is analogue mode
	
	RCC->APB2ENR|=RCC_APB2ENR_ADC1EN;		//ADC clock enable
	ADC1->SQR1&=~ADC_SQR1_L;						//set number of conversions per sequence to 1
	ADC1->SQR3&=~ADC_SQR3_SQ1;					//clear channel select bits
	ADC1->SQR3|=PA0_Channel;						//set channel

	ADC1->CR2|=ADC_CR2_ADON;						//enable ADC
	
}


unsigned short read_adc(void)
{
	ADC1->CR2|=ADC_CR2_SWSTART;				//start ADC conversion
	while((ADC1->SR&ADC_SR_EOC)==0)		//wait for ADC conversion complete
	{
		__NOP();
	}
	return ADC1->DR;									//return converted value
}

