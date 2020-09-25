#ifndef _SEGLED_H
#define _SEGLED_H

#include <STC15F2K60S2.h>
#include <intrins.h>

#define FLASH_FLAG  0x01 //闪烁标志

void segdisp(u8 *process , u8 *flash);
extern void HourFlash(u8 *process , u8 *flash_time);//小时闪烁
void MinFlash(u8 *process , u8 *flash_time);//分时闪烁
void SecFlash(u8 *process , u8 *flash_time);//秒时闪烁

#endif