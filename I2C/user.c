#include "user.h"
#include "lcd1602.h"
#include "uart0.h"

void BCD(uchar *p,bit flag)  
{
	char i,j = 0;
	char s[9],a[6];
	if(flag == 1)
	{
	 p[2] = p[2] & 0x3f;
	 p[1] = p[1] & 0x7f;
	 p[0] = p[0] & 0x7f;
	}
	else
	{
		p[2] = p[2] & 0xff;
	  p[1] = p[1] & 0x1f;
	  p[0] = p[0] & 0x3f;
	}
	for(i = 0 ; i < 3 ; i++ )
	{
		a[j++] = p[i]& 0x0f;
		a[j++] = p[i]>>4;
	}
	if(flag == 1)
	{
	  for(i = 7 , j = 0; i >=0 ; i-- )
	  {
		  if(i == 2 || i == 5)  s[i--] = '-';
		  s[i] = a[j++] + 0x30;
	  }
		s[8] = '\0';
	}
	else
	{
	 for(i = 5,j = 0 ; i >= 0 ; i--) 
			s[i] = a[j++] + 0x30;
	 s[6] = '\0';
	}
	
	if(flag == 1)
	  disp(0x88,s);
	else
		disp(0x82,s);
}

uchar Judge(uchar *a,uchar *b,uchar *c)//ÅÐ¶Ï240c02
{
	unsigned long m=0,n=0,time=0;
	m=(unsigned long)((a[2]>>4)*10+(a[2]&0x0f))*3600 + ((a[1]>>4)*10+(a[1]&0x0f))*60 + ((a[0]>>4)*10+(a[0]&0x0f));
  n=(unsigned long)((c[2]>>4)*10+(c[2]&0x0f))*3600 + ((c[1]>>4)*10+(c[1]&0x0f))*60 + ((c[0]>>4)*10+(c[0]&0x0f));	
	time = (unsigned long)((b[2]>>4)*10+(b[2]&0x0f))*3600 + ((b[1]>>4)*10+(b[1]&0x0f))*60 + ((b[0]>>4)*10+(b[0]&0x0f));	
	if(m>n) return 2; //´íÎó£¬·µ»Ø2
	if(time>=m && time<n) return 1; //ÔÚÕâÊ±¼äÄÚ·µ»Ø1£¬µÆÁÁ
	else return 0; //
}

void LedOn() //µÆÁÁ
{
	LED_RED = 0;
	LED_GREEN = 0;
	disp(0xc4,"LED On");
}

void LedOff()//µÆÃð
{
	LED_RED = 1;
	LED_GREEN = 1;
	disp(0xc4,"LedOff");
}

void Led_Init()
{
	LED_RED = 1;
	LED_GREEN = 1;
}

uchar psw(uchar *p,uchar *s)
{
	s[2] = p[3]-0x30;
	s[2] = s[2] << 4;
  s[2] = s[2] + (p[4]-0x30);	
	
	s[1] = p[5]-0x30;
	s[1] = s[1] << 4;
	s[1] = s[1] + (p[6]-0x30);
		
	s[0] = p[7]-0x30;
	s[0] = s[0] << 4;
	s[0] = s[0] + (p[8]-0x30);
	
	if(p[0]=='T'&&p[1]=='T'&&p[2]=='C') return 0;
	else if(p[0]=='L'&&p[1]=='O'&&p[2]=='T') return 1;
	else if(p[0]=='L'&&p[1]=='F'&&p[2]=='T') return 2;
	else return 3;
}

void usart_back(uchar *p)	
{
	  uchar i;
	  for(i = 0 ; i < 9 ; i++)
	    p[i] = 0;
		putall("error\n",7);
}