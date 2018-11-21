#ifndef _SPI_H_
#define _SPI_H_

#define SPI_PORT	GPIOB
#define SCK_pin		3		//on GPIOB
#define MISO_pin	4		//on GPIOB
#define MOSI_pin	5		//on GPIOB

#define CS_PORT		GPIOA
#define CS_pin		4		//on GPIOA

#define clr_CS()	GPIOA->BSRR=(1u<<(CS_pin+16))
#define set_CS()	GPIOA->BSRR=(1u<<CS_pin)

#include <stm32f4xx.h>

unsigned char transfer_spi(unsigned char send_val);
void init_spi(void);

#endif
