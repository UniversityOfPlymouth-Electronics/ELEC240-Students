#include <stm32f4xx.h>
#include "PLL_Config.c"
#include "ADC.h"
#include "DAC.h"


unsigned short ADC_DATA;
int main(void)
{
	//PLL_Config();
	SystemCoreClockUpdate();
	
	init_ADC();		//config ADC
	init_DAC();		//config DAC
	
	
	while(1)
	{
		ADC_DATA=read_adc();			//read value from ADC
		output_dac(ADC_DATA<<1);			//send straight to DAC (DAC pin should replicate ADC pin)
	}
}

