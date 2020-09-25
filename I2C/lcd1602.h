#ifndef __lcd1602_h
#define __lcd1602_h

#include "IIC.h"

void check_busy(void);
void write_command(uchar com);
void write_data(uchar Adata);
void LCD_init(void);
void string(uchar ad ,uchar *s);
void disp(uchar ad, uchar *s);
void lcd_test(void);
void delaym(uint);

#endif  