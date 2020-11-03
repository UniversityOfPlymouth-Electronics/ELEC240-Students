#ifndef _LCD_H_
#define _LCD_H_
#define LCD_PORT	GPIOD
#define LCD_RS_pin	11
#define LCD_RW_pin	12
#define LCD_E_pin		13
#define LCD_BKL_pin	14
#define LCD_MODE_pin	15

#define LCD_D0_pin	0



#define LCD_LINE1		0x80
#define LCD_LINE2		0xc0

#define set_LCD_RS()	LCD_PORT->BSRR=(1u<<LCD_RS_pin)
#define clr_LCD_RS()	LCD_PORT->BSRR=(1u<<(LCD_RS_pin+16))
#define set_LCD_RW()	LCD_PORT->BSRR=(1u<<LCD_RW_pin)
#define clr_LCD_RW()	LCD_PORT->BSRR=(1u<<(LCD_RW_pin+16))
#define set_LCD_E()		LCD_PORT->BSRR=(1u<<LCD_E_pin)
#define clr_LCD_E()		LCD_PORT->BSRR=(1u<<(LCD_E_pin+16))

#define LCD_CLR()		cmdLCD(0x01)

#define set_LCD_bus_input()		LCD_PORT->MODER&=~(0xffff<<(2*LCD_D0_pin))
#define set_LCD_bus_output()	LCD_PORT->MODER|=(0x5555<<(2*LCD_D0_pin))

#include <stm32f4xx.h>

void lcd_delayus(unsigned int us);
void WaitLcdBusy(void);
void set_LCD_data(unsigned char d);
void LCD_strobe(void);
void cmdLCD(unsigned char cmd);
void putLCD(unsigned char put);
void initLCD(void);

#endif
