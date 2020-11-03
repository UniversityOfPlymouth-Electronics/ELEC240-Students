#include "lcd.h"

int main(void)
{																				//no PLLCONFIG so SysClock = 16Mhz
	initLCD();
	cmdLCD(LCD_LINE1);
	putLCD('A');
	
	while(1);
}
