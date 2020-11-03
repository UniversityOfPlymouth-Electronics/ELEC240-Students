#ifndef _LCD_H_
#define _LCD_H_
#define LCD	GPIOD
#define RS	11
#define R_W	12
#define E		13

#define LCD_D0_pin	0



#define LCD_LINE1		0x80
#define LCD_LINE2		0xc0

// defined in stm32f4xx.h
//#define SET_BIT(REG, BIT)     ((REG) |= (BIT))
//#define CLEAR_BIT(REG, BIT)   ((REG) &= ~(BIT))
//#define READ_BIT(REG, BIT)    ((REG) & (BIT))
//#define CLEAR_REG(REG)        ((REG) = (0x0))
//#define WRITE_REG(REG, VAL)   ((REG) = (VAL))
//#define READ_REG(REG)         ((REG))
//#define MODIFY_REG(REG, CLEARMASK, SETMASK)  WRITE_REG((REG), (((READ_REG(REG)) & (~(CLEARMASK))) | (SETMASK)))
//#define POSITION_VAL(VAL)     (__CLZ(__RBIT(VAL))) 


#define SETPIN(port, pin)		port->BSRR=(1u<<pin)
#define CLRPIN(port, pin)		port->BSRR=(1u<<(pin+16))

#define LCD_CLR()		cmdLCD(0x01)

#define set_LCD_bus_input()		LCD->MODER&=~(0xffff<<(2*LCD_D0_pin))
#define set_LCD_bus_output()	LCD->MODER|=(0x5555<<(2*LCD_D0_pin))

#include <stm32f4xx.h>

void lcd_delayus(unsigned int us);
void WaitLcdBusy(void);
void set_LCD_data(unsigned char d);
void LCD_strobe(void);
void cmdLCD(unsigned char cmd);
void putLCD(unsigned char put);
void initLCD(void);

#endif
