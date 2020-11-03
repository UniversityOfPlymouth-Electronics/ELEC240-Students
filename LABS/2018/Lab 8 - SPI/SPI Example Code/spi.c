#include "spi.h"

unsigned char transfer_spi(unsigned char send_val)
{
	unsigned char return_val;
	
	SPI1->DR=send_val;
	while((SPI1->SR&0x81)!=0x01);		//wait while BSY bit set and RXNE bit clear, when BSY bit clears spi bus is no longer busy, when valid data arrives in the buffer RXNE bit sets
	return_val=SPI1->DR;
	
	return return_val;
}


void init_spi_ports(void)
{
	RCC->AHB1ENR|=(RCC_AHB1ENR_GPIOAEN|RCC_AHB1ENR_GPIOBEN);		//GPIO A,B clock enable
	
			//CONFIG GPIOS
	CS_PORT->MODER&=~((3u<<(2*CS_pin)));			//clear GPIOA pin mode
	CS_PORT->MODER|=((1u<<(2*CS_pin)));				//reset GPIOA pin mode to digital output
	
	SPI_PORT->MODER&=~(				//clear GPIOB 0,3,4,5 pin modes
			(3u<<(2*SCK_pin))
			|(3u<<(2*MISO_pin))
			|(3u<<(2*MOSI_pin))
			|0x03
				);
	SPI_PORT->MODER|=(		//reset GPIOB pins 3,4,5 mode to alternate function, pin 0 to digital output
			(2u<<(2*SCK_pin))
			|(2u<<(2*MISO_pin))
			|(2u<<(2*MOSI_pin))
			|0x01
				);
	SPI_PORT->AFR[0]&=~(						//clear alternate function selector bits
			(0x0f<<(4*SCK_pin))
			|(0x0f<<(4*MISO_pin))
			|(0x0f<<(4*MOSI_pin))
				);
	SPI_PORT->AFR[0]|=(						//reset alternate function selector bits to SPI1
			(5u<<(4*SCK_pin))
			|(5u<<(4*MISO_pin))
			|(5u<<(4*MOSI_pin))
				);
				
		set_CS();
}

void init_spi(void)
{
	init_spi_ports();
	
	
				//CONFIG SPI MODULE
	RCC->APB2ENR|=RCC_APB2ENR_SPI1EN;
	SPI1->CR1&=~(				//module disabled, clear bad rate bits
			SPI_CR1_SPE
			|SPI_CR1_BR
				);
	SPI1->CR1|=(			//spi config
			SPI_CR1_SSI
			|SPI_CR1_SSM		//SS control set
			|SPI_CR1_MSTR		//master mode
			|SPI_CR1_SPE		//module enabled
			|(3u<<3)			//baud rate bits set /16 giving 1MHz SCK frequency
				);
}
