#ifndef __i2c_h
#define __i2c_h
#include <STC15F2K60S2.h>
#include "intrins.h"

sbit SCL = P1^7;
sbit SDA = P2^3;
sbit RST = P1^3;

void I2C_Start();
void I2C_Stop();
void I2C_Ack(u8 ack);
bit I2C_WaitAck();
void I2C_SendByte(u8 dat);
u8 I2C_ReadByte();

#endif