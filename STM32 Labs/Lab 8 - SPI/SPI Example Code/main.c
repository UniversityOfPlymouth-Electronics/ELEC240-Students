#include "PLL_Config.c"
#include "spi.h"
#include "bmp280.h"


void delayms(unsigned int ms)
{
	unsigned int i;
	while(ms--)				//n x 1ms
	{
		for(i=0; i<(SystemCoreClock/4000); i++);		//blocking delay, approx 1ms
	}
}




unsigned int temp,press;
float temp_comp,press_comp, press_hPa;
int main(void)
{
//	PLL_Config();
	SystemCoreClockUpdate();

	init_spi();
	delayms(50);
	init_bmp280();
	
	while(1)
	{
		temp=read_bmp280_temp();
		press=read_bmp280_press();
		
		temp_comp=bmp280_compensate_T_float(temp);
		press_comp=bmp280_compensate_P_float(press);
		press_hPa=press_comp/100.0f;
		
		delayms(10);
		GPIOB->ODR^=0x01;
	}
}
