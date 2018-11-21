#include "usart.h"
#include "PLL_Config.c"

int main(void)
{
//	PLL_Config();
	SystemCoreClockUpdate();

	unsigned int i;

	init_USART();

	while(1)
	{
		send_usart('A');
		for(i=0; i<100000; i++);
	}
}

