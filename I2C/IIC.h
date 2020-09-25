#ifndef _IIC_H
#define _IIC_H

#include <reg51.h>
#include <intrins.h>

sbit SCL = P1^4;
sbit SDA = P1^5;

typedef unsigned char uchar;
typedef unsigned int  uint;

void Delay1us();	
void IIC_Start();
void IIC_Stop();
void IIC_Ack(uchar ack);
bit IIC_WaitAck();
void IIC_SendByte(uchar dat);
uchar IIC_ReadByte();
void Delay101ms();
#endif