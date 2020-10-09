#include "SEGLED.h"

u8 code segtab[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0xff,0xbf};

void Delay1ms()		//@12.000MHz
{
	unsigned char i, j;
	i = 12;
	j = 169;
	do
	{
		while (--j);
	} while (--i);
}

void segdisp(u8 *process)
{
	u8 bsel=0x01,j;
	P2&=0x1f; //释放片选
	for(j=0;j<8;j++)
	{
		P0 = bsel; //选择com
		P2 = P2&0x1f|0xc0; //选择Y6
		P2&=0x1f; //释放片选
		P0 = segtab[process[j]]; //显示数码管段码值
		P2 = P2&0x1f|0xe0;//选择Y7
		Delay1ms();
		bsel = _crol_(bsel,1); //向左移一位
		P0 |= 0xff;
		P2&=0x1f; //释放片选
	}
}

void TimeFlash(u8 *process , bit flash)
{
  u8 bsel=0x01,j;
	P2&=0x1f; //释放片选
	for(j=0;j<8;j++)
	{
		P0 = bsel; //选择com
		P2 = P2&0x1f|0xc0; //选择Y6
		P2&=0x1f; //释放片选
		P0 = segtab[process[j]]; //显示数码管段码值
    if((j ==2 || j == 5) && flash == 1 )
      P0 |= 0xff;
		P2 = P2&0x1f|0xe0;//选择Y7
		Delay1ms();
		bsel = _crol_(bsel,1); //向左移一位
		P0 |= 0xff;
		P2&=0x1f; //释放片选
	} 
}
