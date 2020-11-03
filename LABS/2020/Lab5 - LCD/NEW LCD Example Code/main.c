#include <stm32f4xx.h>
#include "PLL_Config.c"
#include "delay.c"
#include "lcd.c"


#define LED_PORT  (GPIOB)
#define GREEN (14)
#define BLUE (7)
#define RED (0)

#define LED_ON(colour)		(LED_PORT->BSRR=(1u<<colour))
#define LED_OFF(colour)		(LED_PORT->BSRR=(1u<<(colour+16)))
#define InitLED(colour)   (LED_PORT->MODER = ((LED_PORT->MODER & ~(3u<<(2*colour))) | (1u<<(2*colour))))


void Init_LED (void){
			//ENABLE PORT(S)
		RCC->AHB1ENR|=RCC_AHB1ENR_GPIOBEN;		//GPIO B clock enable
	
			//CONFIGURE PORT PIN FUNCTIONS
		InitLED(RED);
		InitLED(BLUE);
		InitLED(GREEN);
}


int main(void)
{
	PLL_Config();
	SystemCoreClockUpdate();
	Init_Systick();
	Init_Timer3();
	Init_LED();
	initLCD();
	cmdLCD(LCD_LINE1);
	putLCD('H');
	putLCD('e');
	putLCD('l');
	putLCD('l');
	putLCD('o');
	
	while(1){
		LED_ON(BLUE);
//		Delay(100);
		delayms(100);
		LED_OFF(BLUE);
//		Delay(100);
		delayms(100);
	}
}
