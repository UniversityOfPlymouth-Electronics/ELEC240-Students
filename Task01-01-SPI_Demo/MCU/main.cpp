#include "mbed.h"

SPI spi(PA_7, PA_6, PA_5);      // Ordered as: mosi, miso, sclk could use forth parameter ssel
DigitalOut cs(PC_6);            // Chip Select for Basic Outputs to illuminate Onboard FPGA DEO nano LEDs CN7 pin 1
DigitalOut pulse(LED1);

int32_t read_switches(void);    //Read 4 Sliding switches on FPGA (Simulating OPTO-Switches from Motor(s)

//NBB the following line for F429ZI !!!!
DigitalIn DO_NOT_USE(PB_12);    // MAKE PB_12 (D19) an INPUT do NOT make an OUTPUT under any circumstances !!!!! ************* !!!!!!!!!!!
                                // This Pin is connected to the 5VDC from the FPGA card and an INPUT is 5V Tolerant

//Ticker ticktock;
  
int main() {
    cs = 1;                     // Chip must be deselected, Chip Select is active LOW
    spi.format(8,0);            // Setup the DATA frame SPI for 16 bit wide word, Clock Polarity 0 and Clock Phase 0 (0)
    spi.frequency(1000000);     // 1MHz clock rate

    while(true)                 //Loop forever Knight Rider Display on FPGA
    {
        read_switches();
            
        //LED Chaser display KIT lives on!
        pulse = !pulse;
        for (uint32_t i=1;i<=128;i*=2)
        {
            cs = 0;             //Select the device by seting chip select LOW
            spi.write(i);               //Send the data - ignore the return data
            cs = 1;             //De-Select the device by seting chip select HIGH
            wait_ms(40);
        }
        for (uint32_t i=128;i>=1;i/=2)
        {
            cs = 0;             //Select the device by seting chip select LOW
            spi.write(i);               //Send the data - ignore the return data
            cs = 1;             //De-Select the device by seting chip select HIGH
            wait_ms(40);
        }
        wait_ms(1000);
    }
}

//Function to read back the state of the switches
int read_switches(void){
    int sw_val = 0;
    cs = 0;             //Select the device by seting chip select LOW
    sw_val = spi.write(0x00);
    cs = 1 ;            //De-select the device by seting chip select HIGH
    printf("Valued received: %X\n\r", sw_val);
    if (sw_val&(1<<0)){ printf("Switch 0 :"); }
    if (sw_val&(1<<1)){ printf("Switch 1 :"); }
    if (sw_val&(1<<2)){ printf("Switch 2 :"); }
    if (sw_val&(1<<3)){ printf("Switch 3 :"); }
    if (sw_val>0)     { printf("\r\n");       }
    return sw_val;    
}

