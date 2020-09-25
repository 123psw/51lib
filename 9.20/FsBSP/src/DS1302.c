#include "DS1302.h"

void Delay2us()		//@12.000MHz
{
	unsigned char i;

	_nop_();
	_nop_();
	i = 3;
	while (--i);
}

void writebyte(u8 dat) 
{
	u8 i;
	EA = 0;
	for(i=0;i<8;i++)
	{
		SCL=0;
		SDA=dat&0x01;
		SCL=1;
		dat>>=1;
	}
	EA = 1;
}

u8 read(u8 add)
{
	u8 i,temp;
	u8 dat1,dat2;
	RST=0;
	SCL=0;
	RST=1;
	writebyte(add);
	EA = 0;
	for(i=0;i<8;i++)
	{
		SCL=0;
		temp>>=1;
		if(SDA)
		{
			temp|=0x80;
		}
		SCL=1;
	}	
	SDA=0;
	EA = 1;
	dat1=temp/16;
	dat2=temp%16;
	temp=dat1*10+dat2;
	return temp;
}

void write(u8 add,u8 dat)
{
	u8 num;
	RST=0;
	SCL=0;
	RST=1;
	writebyte(add);
	num=(dat/10<<4)|(dat%10);
	writebyte(num);
	RST=0;
}


