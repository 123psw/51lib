#include "uart0.h"

void InitUART(void)
{
	TH1=0XFD;
	TL1=TH1;
	TMOD |= 0x20;
	SCON = 0X50;
	ES=1;
	TR1=1;
	TI=0;
	RI=0;
	EA = 1;
}
	
void putbuf(char c)
{
	SBUF = c;
	while(!TI)
	{
	}
	TI =0;
}

void putall(char *s,unsigned int con)
{
	unsigned int ab=0;
	while(ab < con)
	{
		putbuf(*s);
		s++;
		ab++;
	}
}