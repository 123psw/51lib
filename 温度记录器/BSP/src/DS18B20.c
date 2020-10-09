#include "DS18B20.h"

void Delay100us()		//@11.0592MHz
{
	unsigned char i, j;

	_nop_();
	_nop_();
	i = 2;
	j = 15;
	do
	{
		while (--j);
	} while (--i);
}

void Delay500us()		//@11.0592MHz
{
	unsigned char i, j;

	_nop_();
	_nop_();
	i = 6;
	j = 93;
	do
	{
		while (--j);
	} while (--i);
}

void dsinit()
{
	DQ=0;
	Delay500us();
	DQ=1;
	Delay500us();
}

u8 read1()
{
	u8 i;
	u8 dat;
	for(i=0;i<8;i++)
	{
		DQ=0;
		_nop_();
		dat>>=1;
		DQ=1;
		if(DQ==1)
		{
			dat |= 0x80;// dat=dat|0x80;   0000 0000 | 1000 0000 =1000 0000
		}
		Delay100us();
	}
	return dat;
}

void write1(u8 dat)
{
	u8 i;
	for(i=0;i<8;i++)
	{
		DQ=0;
		DQ=dat&0x01;//0100 0100 & 0000 0001 // 0000 0001
		Delay100us();
		DQ=1;
		dat>>=1;//dat=dat>>1;//1001 0000//0010 0001
	}
}

u8 temget()
{
	u8 temp;
	u8 low,high;
	
	dsinit();
	write1(0xcc);
	write1(0x44);
	Delay500us();	Delay500us();	

	dsinit();
	write1(0xcc);
	write1(0xbe);
	
	low=read1();
	high=read1();
	
	temp=high<<4;//0000 0101  =0101 0000
	temp |= (low>>4); //  1010 0110   0000 0110 | 0101 0000=0101 0110
	
	return temp;
}

