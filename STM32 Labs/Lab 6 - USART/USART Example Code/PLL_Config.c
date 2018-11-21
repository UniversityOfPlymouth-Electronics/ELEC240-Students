#include <stm32f4xx.h>

void PLL_Config(void)
{
	

//*******************************************************************************
//*            PLL (clocked by HSI) used as System clock source                	*
//*							By Stuart MacVeigh									*
//*******************************************************************************

    RCC->APB1ENR |= RCC_APB1ENR_PWREN;	//enable power interface clock source
    PWR->CR |= PWR_CR_VOS;

	
		#define PLL_N	180			//SYSTEM CLOCK SPEED (FCY (MHz))
		#define HSI		16000000	//INTERAL OSC FREQUENCY
		
		#define PLL_M	(HSI/2000000)		//Fcy = Fxtal x PLL_N/(PLL_P x PLL_M)
		#define PLL_P	2
		#define PLL_Q	7
    // HCLK = SYSCLK / 1
    RCC->CFGR |= RCC_CFGR_HPRE_DIV1;		//CORE CLOCK = 180MHZ
    
    // PCLK2 = HCLK / 2
    RCC->CFGR |= RCC_CFGR_PPRE2_DIV4;		//PERIPHERAL CLOCK 2 = 180MHZ/4 = 45MHZ, THIS IS BECAUSE THE SPI MODULES (AND POSSIBLY OTHERS) DO NOT OPERATE PROPERLY WHEN PCLK > 42MHZ
    
    // PCLK1 = HCLK / 4
    RCC->CFGR |= RCC_CFGR_PPRE1_DIV4;		//PERIPHERAL CLOCK 1 = 180MHZ/4 = 45MHZ, THIS IS BECAUSE THE SPI MODULES (AND POSSIBLY OTHERS) DO NOT OPERATE PROPERLY WHEN PCLK > 42MHZ

    // Configure the main PLL
    RCC->PLLCFGR = PLL_M | (PLL_N << 6) | (((PLL_P >> 1) -1) << 16) | (PLL_Q << 24);

    // Enable the main PLL
    RCC->CR |= RCC_CR_PLLON;

    // Wait till the main PLL is ready
    while(!(RCC->CR & RCC_CR_PLLRDY));
   
    // Configure Flash prefetch, Instruction cache, Data cache and wait state
    FLASH->ACR = FLASH_ACR_ICEN |FLASH_ACR_DCEN |FLASH_ACR_LATENCY_5WS;

    // Select the main PLL as system clock source
    RCC->CFGR &=~ RCC_CFGR_SW;
    RCC->CFGR |= RCC_CFGR_SW_PLL;

    // Wait till the main PLL is used as system clock source
    while ((RCC->CFGR & RCC_CFGR_SWS ) != RCC_CFGR_SWS_PLL);
	
//******************************************************************************
//*            END PLL (CLOCKED BY HSI) SETUP CODE                             *
//******************************************************************************
	
}
