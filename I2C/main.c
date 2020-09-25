#include <reg51.h>
#include "PCF8563.h"
#include "lcd1602.h"
#include "uart0.h"
#include "user.h"

uchar Rs[9];
uchar u_flag = 0;
uchar u_i = 0;

void UART0_isr(void) interrupt 4
{
	if(RI)
	{
		if(u_i<9)
		{
			Rs[u_i] = SBUF;
			u_i++;
		}
		if(u_i==9)
		{
			u_flag = 1;
			ES=0;
		}
		RI=0;
	}
}
void main()
{
	uchar a[3],b[3],c[3],s[3];  //存放时间，秒分时
	uchar date[3];
	void (*LED[3])()={LedOff,LedOn,Led_Init};
	void (*uart_enter[4])(uchar *p) = {PCF8563_WritePage_Time,AT_WritePage_LedOn,AT_WritePage_LedOff,usart_back};
	Delay101ms();
	InitUART();
	LCD_init();
	while(1)
	{
		if(u_flag == 1)
		{
			u_flag=0;
			u_i=0;
			ES = 1;
			uart_enter[psw(Rs,a)](a);
		}	
		PCF8563_Read_Date(date);
	  disp(0x80,"20");
	  BCD(date,0);
		PCF8563_ReadPage_Time(s);
		Delay40ms();
		BCD(s,1);
		AT24c02_ReadPage(0xa0,0x08,0xa1,b,3);
		AT24c02_ReadPage(0xa0,0x10,0xa1,c,3);
		LED[Judge(b,s,c)]();
		
		
	}
}