#include "spi.h"
#include "bmp280.h"



unsigned char cmd_bmp280(unsigned char cmd,unsigned char send_val)
{
	unsigned char read_val;
	clr_CS();
	transfer_spi(cmd);								//send cmd/reg address
	read_val=transfer_spi(send_val);	//send value to be written, if value is being returned this will be loaded into read_val
	set_CS();
	return read_val;						//return value passed back to main code
}

unsigned int read_bmp280_temp(void)
{
	unsigned char read_data[3];
	unsigned char i;
	unsigned int result;
	
	while(cmd_bmp280(0xf3,0)&0x09);		//wait for data ready, read status register
	
	clr_CS();
	transfer_spi(0xfa);					//read pressure register (address 0xfa)
	for(i=0; i<3; i++) 
	{
	//	transfer_spi(addr[i]);
		read_data[i]=transfer_spi(0);				//3 byte value
	}
	set_CS();
	
	result=(								//construct value
			(read_data[0]<<12)				//high byte
			|(read_data[1]<<4)				//mid byte
			|((read_data[2]&0xf0)>>4)	//low byte
		);
	
	return result;
}

unsigned int read_bmp280_press(void)
{
	unsigned char read_data[3];
	unsigned char i;
	unsigned int result;
	
	while(cmd_bmp280(0xf3,0)&0x09);			//wait for data ready, read status register
	
		clr_CS();
	transfer_spi(0xf7);			//read pressure register (address 0xf7)
	for(i=0; i<3; i++) 
	{
	//	transfer_spi(addr[i]);
		read_data[i]=transfer_spi(0);	//3 byte value
	}
	set_CS();
	
	result=(								//construct value
			(read_data[0]<<12)				//high byte
			|(read_data[1]<<4)				//mid byte
			|((read_data[2]&0xf0)>>4)	//low byte
		);
	
	return result;
}


void init_bmp280(void)
{
	unsigned char rxdata[24],i;
	cmd_bmp280(0x74,0x27);		//config measurement settings
	
	
		//READ CALIBRATION ADDRESSES FROM MODULE
	clr_CS();
	transfer_spi(0x88);		//starts at address 0x88 (see Table 17 in datasheet)
	for(i=0; i<24; i++)	rxdata[i]=transfer_spi(0);
	set_CS();
	
		//STORE CALIBRATION VALUES FOR USE IN CONVERSION FORMULAS
	dig_T1=((rxdata[1]<<8)|rxdata[0]);
	dig_T2=((rxdata[3]<<8)|rxdata[2]);
	dig_T3=((rxdata[5]<<8)|rxdata[4]);
	dig_P1=((rxdata[7]<<8)|rxdata[6]);
	dig_P2=((rxdata[9]<<8)|rxdata[8]);
	dig_P3=((rxdata[11]<<8)|rxdata[10]);
	dig_P4=((rxdata[13]<<8)|rxdata[12]);
	dig_P5=((rxdata[15]<<8)|rxdata[14]);
	dig_P6=((rxdata[17]<<8)|rxdata[16]);
	dig_P7=((rxdata[19]<<8)|rxdata[18]);
	dig_P8=((rxdata[21]<<8)|rxdata[20]);
	dig_P9=((rxdata[23]<<8)|rxdata[22]);
}
