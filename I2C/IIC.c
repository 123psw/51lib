#include "IIC.h"
#include "intrins.h"
void Delay1us()		//@12.000MHz
{
	_nop_();
}
 
void IIC_Start()
{
   SDA = 1;
	 SCL = 1;
	 Delay1us();
	 SDA = 0;
	 Delay1us();
	 SCL = 0;
	 Delay1us();
}	

void IIC_Stop()
{
	 SDA = 0;
	 SCL = 1;
	 Delay1us();
	 SDA = 1;
	 Delay1us();
}

void IIC_Ack(uchar ack)
{
	if(ack)
		SDA=1;
	else
		SDA=0;
	SCL=0;
	Delay1us();
	SCL=1;
	Delay1us();
	SCL=0;
}

bit IIC_WaitAck()
{
	uchar i=200;
	SDA=1;
	Delay1us();
	SCL=1;
	while(SDA)
	{
		i--;
		if(!i)
		{
			IIC_Stop();
			return 0;
		}
	}
	SCL=0;
	SDA=1;
	return 1;
}

void IIC_SendByte(uchar dat)
{
	uchar a=0;
	EA = 0;
	for(a=0;a<8;a++)
	 {	 
		 SDA=dat&0x80;
		 dat=dat<<1; 
		 Delay1us();
		 SCL = 1;
		 Delay1us();
		 SCL = 0;
		 Delay1us();
	 }
	 EA = 1;
}

uchar IIC_ReadByte()
{
	uchar a=0,dat=0;
	EA = 0;
	SDA = 1;
	Delay1us();
	for(a=0;a<8;a++)
	{
		SCL = 1;
		Delay1us();
		dat<<=1;
		dat|=SDA;
		Delay1us();
		SCL = 0;
		Delay1us();
	}
	EA = 1;
	return dat;
}

void Delay101ms()		//@12.000MHz
{
	uchar i, j, k;
	_nop_();
	_nop_();
	i = 5;
	j = 155;
	k = 244;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}
