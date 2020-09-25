#ifndef __user_h
#define __user_h

#include <STC15F2K60S2.h>
#include "SEGLED.h"
#include "DS1302.h"
#include "common.h"
void init_IO();
void writetime(u8 *ds);
void readtime(u8 *time);
void Time(u8 *time);
void BCD_conversion(u8 *time,u8 *dbuf);
void ExecClock(u8 KeyNum ,ClockStatus *clockState , TimeStatus *blink);
void TimeChange(u8 *time ,TimeStatus *blink);
#endif