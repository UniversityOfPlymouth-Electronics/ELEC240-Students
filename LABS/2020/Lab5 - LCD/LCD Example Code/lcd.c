#include "lcd.h"

void lcd_delayus(unsigned int us)		//blocking delay for LCD, argument is approximate number of micro-seconds to delay
{
	unsigned char i;
	while(us--)
	{
		for(i=0; i<SystemCoreClock/4000000; i++){__NOP();}
	}
}

void WaitLcdBusy(void)
{
	lcd_delayus(3000);		//3ms blocking delay
}

void set_LCD_data(unsigned char d)
{
	LCD->BSRR=(0xff<<(LCD_D0_pin+16));	//clear data lines
	LCD->BSRR=(d<<LCD_D0_pin);					//put data on lines
}

void LCD_strobe(void)		//10us high pulse on LCD enable line
{
	lcd_delayus(10);
	SETPIN(LCD, E);
	lcd_delayus(10);
	CLRPIN(LCD,E);
}


void cmdLCD(unsigned char cmd)		//sends a byte to the LCD control register
{
	WaitLcdBusy();				//wait for LCD to be not busy
	CLRPIN(LCD, RS);					//control command
	CLRPIN(LCD, R_W);					//write command
	set_LCD_data(cmd);		//set data on bus
	LCD_strobe();					//apply command
}

void putLCD(unsigned char put)	//sends a char to the LCD display
{
	WaitLcdBusy();				//wait for LCD to be not busy
	SETPIN(LCD, RS);				//text command
	CLRPIN(LCD, R_W);				//write command
	set_LCD_data(put);		//set data on bus
	LCD_strobe();					//apply command
}

void initLCD(void)
{
		SystemCoreClockUpdate();
		RCC->AHB1ENR|=RCC_AHB1ENR_GPIODEN;	//enable LCD port clock
	
	
			//CONFIG LCD GPIO PINS
		LCD->MODER&=~(					//clear pin direction settings
			(3u<<(2*RS))
			|(3u<<(2*R_W))
			|(3u<<(2*E))
			|(0xffff<<(2*LCD_D0_pin))
			);
	
	
	LCD->MODER|=(				//reset pin direction settings to digital outputs
			(1u<<(2*RS))
			|(1u<<(2*R_W))
			|(1u<<(2*E))
			|(0x5555<<(2*LCD_D0_pin))
		);

	
			//LCD INIT COMMANDS

			
	//GPIOD->BSRR=(1u<<(11+16));									//MAKE THE LCD RS PIN = 0
	//GPIOD->BSRR=(1u<<(RS_pin+16));
	//LCD->BSRR=(1u<<(RS_pin+16));
	CLRPIN(LCD, RS);
	CLRPIN(LCD, R_W);
	CLRPIN(LCD, E);					//all lines default low

	
	lcd_delayus(25000);		//25ms startup delay
	cmdLCD(0x38);	//Function set: 2 Line, 8-bit, 5x7 dots
	cmdLCD(0x0c);	//Display on, Cursor blinking command
	cmdLCD(0x01);	//Clear LCD
	cmdLCD(0x06);	//Entry mode, auto increment with no shift
}
