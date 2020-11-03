#include "usart.h"

void send_usart(unsigned char d)
{
	while(!(USART_MODULE->SR&USART_SR_TC));		//wait for transmission complete
	USART_MODULE->DR=d;		//write byte to usart data register
}

void init_USART(void)
{
	unsigned char i1,i2;
		RCC->AHB1ENR|=RCC_AHB1ENR_GPIODEN;		//usart port clock enable
	
	USART_PORT->MODER&=~(				//clear pin function bits
		(3u<<(2*USART_TX_pin))
		|(3u<<(2*USART_RX_pin))
			);
	USART_PORT->MODER|=(			//reset pin function bits (alternate function)
		(2u<<(2*USART_TX_pin))
		|(2u<<(2*USART_RX_pin))
			);
	
	i1=USART_TX_pin/8;
	i2=USART_RX_pin/8;

		// ALTERNATE FUNCTION SELECT BITS
	USART_PORT->AFR[i1]&=~(0x0f<<(4*(USART_TX_pin-(i1*8))));
	USART_PORT->AFR[i1]|=(0x07<<(4*(USART_TX_pin-(i1*8))));
	USART_PORT->AFR[i2]&=~(0x0f<<(4*(USART_RX_pin-(i2*8))));
	USART_PORT->AFR[i2]|=(0x07<<(4*(USART_RX_pin-(i2*8))));
	
	RCC->APB1ENR|=RCC_APB1ENR_USART3EN;		//usart clock enable
	USART_MODULE->CR1|=(		//USART CONFIG
			USART_CR1_TE		//transmit enable
			|USART_CR1_RE		//receive enable
			|USART_CR1_UE		//usart main enable bit
				);
	USART_MODULE->BRR=SystemCoreClock/(BAUDRATE);		//set baud rate
}
