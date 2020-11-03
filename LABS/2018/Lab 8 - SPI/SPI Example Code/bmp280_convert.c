#include "bmp280.h"

int t_fine;
unsigned short dig_T1;
short dig_T2,dig_T3;
unsigned short dig_P1;
short dig_P2,dig_P3,dig_P4,dig_P5,dig_P6,dig_P7,dig_P8,dig_P9;


// Returns temperature in DegC, float precision. Output value of “51.23” equals 51.23 DegC.
// t_fine carries fine temperature as global value
float bmp280_compensate_T_float(int adc_T)
{
	float var1, var2, T;
	var1 = (((float)adc_T)/16384.0f - ((float)dig_T1)/1024.0f) * ((float)dig_T2);
	var2 = ((((float)adc_T)/131072.0f - ((float)dig_T1)/8192.0f) * (((float)adc_T)/131072.0f - ((float) dig_T1)/8192.0f)) * ((float)dig_T3);
	t_fine = (int)(var1 + var2);
	T = (var1 + var2) / 5120.0f;
	return T;
}



// Returns pressure in Pa as float. Output value of “96386.2” equals 96386.2 Pa = 963.862 hPa
float bmp280_compensate_P_float(int adc_P)
{
	float var1, var2, p;
	var1 = ((float)t_fine/2.0f) - 64000.0f;
	var2 = var1 * var1 * ((float)dig_P6) / 32768.0f;
	var2 = var2 + var1 * ((float)dig_P5) * 2.0f;
	var2 = (var2/4.0f)+(((float)dig_P4) * 65536.0f);
	var1 = (((float)dig_P3) * var1 * var1 / 524288.0f + ((float)dig_P2) * var1) / 524288.0f;
	var1 = (1.0f + var1 / 32768.0f)*((float)dig_P1);
	if (var1 == 0.0f)
	{
		return 0; // avoid exception caused by division by zero
	}
	p = 1048576.0f - (float)(adc_P);
	p = (p - (var2 / 4096.0f)) * 6250.0f / var1;
	var1 = ((float)dig_P9) * p * p / 2147483648.0f;
	var2 = p * ((float)dig_P8) / 32768.0f;
	p = p + (var1 + var2 + ((float)dig_P7)) / 16.0f;
	return p;
}
