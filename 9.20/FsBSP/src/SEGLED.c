#include "SEGLED.h"

u8 code segtab[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};

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

void segdisp(u8 *process , u8 *flash)
{
	u8 bsel=0x01,j;
	P2&=0x1f; //释放片选
	for(j=0;j<6;j++)
	{
		P0 = bsel; //选择com
		P2 = P2&0x1f|0xc0; //选择Y6
		P2&=0x1f; //释放片选
		P0 = segtab[process[j]]; //显示数码管段码值
		if((j == 1 || j == 3) && *flash == 0x01) //小数点闪烁
			P0 &= 0x7f; 
		P2 = P2&0x1f|0xe0;//选择Y7
		Delay1ms();
		bsel = _crol_(bsel,1); //向左移一位
		P0 |= 0xff;
		P2&=0x1f; //释放片选
	}
}

void HourFlash(u8 *process , u8 *flash_time)
{
	 u8 bsel=0x01,j;
	P2&=0x1f; 
	for(j=0;j<6;j++)
	{
		P0 = bsel; 
		P2 = P2&0x1f|0xc0;
		P2&=0x1f; 
		P0 = segtab[process[j]];
		if((j == 0 || j == 1) && *flash_time == FLASH_FLAG) //小时闪烁
		  P0 |= 0xff; 
		P2 = P2&0x1f|0xe0; 
		Delay1ms();
		bsel = _crol_(bsel,1); 
		P0 |= 0xff;
		P2&=0x1f; 
  }  
}

void MinFlash(u8 *process , u8 *flash_time)
{
	 u8 bsel=0x01,j;
	P2&=0x1f; 
	for(j=0;j<6;j++)
	{
		P0 = bsel; 
		P2 = P2&0x1f|0xc0; 
		P2&=0x1f; 
		P0 = segtab[process[j]];
		if((j == 2 || j == 3) && *flash_time == FLASH_FLAG) //分时闪烁
		 P0 |= 0xff; 
		P2 = P2&0x1f|0xe0; 
		Delay1ms();
		bsel = _crol_(bsel,1); 
		P0 |= 0xff;
		P2&=0x1f; 
  }  
}

void SecFlash(u8 *process , u8 *flash_time)
{
	 u8 bsel=0x01,j;
	P2&=0x1f;
	for(j=0;j<6;j++)
	{
		P0 = bsel; 
		P2 = P2&0x1f|0xc0; 
		P2&=0x1f; 
		P0 = segtab[process[j]];
        if((j == 4 || j == 5) && *flash_time == FLASH_FLAG) //秒时闪烁
		 P0 |= 0xff; 
		P2 = P2&0x1f|0xe0; 
		Delay1ms();
		bsel = _crol_(bsel,1); 
		P0 |= 0xff;
		P2&=0x1f; 
  }  
}
