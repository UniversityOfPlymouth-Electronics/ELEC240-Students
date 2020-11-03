#include "usart.h"
#include "PLL_Config.c"

int main(void)
{
		unsigned int i;
//	PLL_Config();
//	SystemCoreClockUpdate();
	init_USART();

	while(1)
	{
		send_usart('A');
		for(i=0; i<1000; i++)		// leaves a gap between transmissions ... NOT NEEDED for normal operation
		{
			__NOP();
		}
	}
}

