#ifndef _MBP280_H
#define _MBP280_H


unsigned char cmd_bmp280(unsigned char cmd,unsigned char send_val);
unsigned int read_bmp280_temp(void);
unsigned int read_bmp280_press(void);
void init_bmp280(void);
float bmp280_compensate_T_float(int adc_T);
float bmp280_compensate_P_float(int adc_P);


extern int t_fine;
extern unsigned short dig_T1;
extern short dig_T2,dig_T3;
extern unsigned short dig_P1;
extern short dig_P2,dig_P3,dig_P4,dig_P5,dig_P6,dig_P7,dig_P8,dig_P9;



#endif
