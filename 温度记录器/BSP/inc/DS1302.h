#ifndef __DS1302_h
#define __DS1302_h

#include <STC15F2K60S2.h>
#include "intrins.h"

sbit SCL = P1^7;
sbit SDA = P2^3;
sbit RST = P1^3;

u8 read(u8 add);
void write(u8 add,u8 dat);
void writetime(u8 *ds);
void readtime(u8 *time);

#endif