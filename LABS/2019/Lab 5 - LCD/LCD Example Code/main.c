#include "lcd.h"

int main(void)
{
	initLCD();
	cmdLCD(LCD_LINE1);
	putLCD('A');
	
	while(1);
}
