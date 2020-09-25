#include "PCF8563.h"

void Delay40ms()		//@11.0592MHz
{
	unsigned char i, j, k;
	_nop_();
	_nop_();
	i = 2;
	j = 175;
	k = 75;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}

void PCF8563_Write_Date(Date date)
{
	AT24c02_Write(0xa2,0x05,date.day);
	AT24c02_Write(0xa2,0x07,date.mouth);
	AT24c02_Write(0xa2,0x08,date.year);
}

void PCF8563_Read_Date(uchar *p)
{
  p[0] = AT24c02_Read(0xa2,0x05,0xa3);
	p[1] = AT24c02_Read(0xa2,0x07,0xa3);
	p[2] = AT24c02_Read(0xa2,0x08,0xa3);
}

void PCF8563_WritePage_Time(uchar *p)
{
	AT24c02_WritePage(0xa2,0x02,p,3);
}

void PCF8563_ReadPage_Time(uchar *p)
{
	AT24c02_ReadPage(0xa2,0x02,0xa3,p,3);
}
