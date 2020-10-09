#ifndef __DS18B20_H_
#define __DS18B20_H_

#include <STC15F2K60S2.h>
#include "intrins.h"
#include "common.h"

sbit DQ=P1^4;

u8 read1();
void write1(u8 dat);
u8 temget();

#endif