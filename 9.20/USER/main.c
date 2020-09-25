#include <STC15F2K60S2.h>
#include "DS1302.h"
#include "SEGLED.h"
#include "common.h"
#include "GPIO.h"
#include "bsp_key.h"
#include "user.h"

#define TIME1S  25
u8 flash = 0x01;
TimeStatus blink = WalkTime;
u8 isTime2GetKeyVal = 0;
u8 flash_hour = 0x01;
u8 flash_min = 0x01;
u8 flash_sec = 0x01;
KeyState keystate = NoKey;
ClockStatus clockState = ShowTime;
void Timer0Init(void)		//20ms@12.000MHz
{
	AUXR &= 0x7F;	 //	定时器时钟12T模式
	TMOD &= 0xF0;	 // 设置定时器模式
	TL0 = 0xE0;		 //设置定时初值
	TH0 = 0xB1;	   //设置定时初值
	TF0 = 0;		   //清除TF0标志
	TR0 = 1;		   //定时器0开始计时
}
void Copy(u8 *a , u8 *b) //复制函数
{
	a[0] = b[0];
	a[1] = b[1];
	a[2] = b[2];
}
void timer0() interrupt 1
{
	static u16 cnt = 0;
	cnt++;
	ReadLine(&keystate ,&isTime2GetKeyVal);
	if(cnt % TIME1S == 0) 
	{
		flash = ~flash;
		flash_hour = ~flash_hour;
		flash_min = ~flash_min;
		flash_sec = ~flash_sec;
	}
	if(cnt >= 4000) cnt = 0;
}

void main()
{
  u8 dbuf[]={0,0,0,0,0,0};
  u8 time[] ={45,23,10};
	u8 time_Buf[] = {0,0,0};
  init_IO();
  Timer0Init();
	writetime(time);
  EA = 1;
  ET0 = 1;
  while(1)
  {
		if(isTime2GetKeyVal)
		{
			isTime2GetKeyVal=0;
			ExecClock(GetKeyNum(),&clockState,&blink);
		}
		switch(blink)
		{
			case FlashHour: //小时闪烁
					HourFlash(dbuf,&flash_hour);
				  break;
			case FlashMin: //分时闪烁
				  MinFlash(dbuf,&flash_min);
			    break;
			case FlashSec: //秒时闪烁
				  SecFlash(dbuf,&flash_sec);
			    break;
			case ModifyTheTime://校时修改后读取
				  blink = WalkTime;
	        writetime(time);
			    break;
			case UnmodifiedTime: //未修改后读取
				  blink = WalkTime;
					Copy(time,time_Buf);
			    writetime(time);
			    break;
		  case ChangeHour:	//小时加1
				 TimeChange(time,&blink);
	       BCD_conversion(time,dbuf);
			   blink = FlashHour;
			   break;
			case ChangeMin: //分时加1
				 TimeChange(time,&blink);			
	       BCD_conversion(time,dbuf);
			   blink = FlashMin;
			   break;
			case ChangeSec: //秒时加1
				 TimeChange(time,&blink);		
	       BCD_conversion(time,dbuf);
			   blink = FlashSec;			
			   break;
			case SaveTime: //进入校时状态下对time值进行复制,进入小时闪烁状态
				 blink = FlashHour;
				 Copy(time_Buf,time);
				 break;
		  default: //Walktime 
			   readtime(time);  
         BCD_conversion(time,dbuf);
         segdisp(dbuf,&flash);	
				 break;
				}
  }
}