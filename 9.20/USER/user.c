#include "user.h"

void init_IO()
{
	//关闭蜂鸣器
	P2 = P2&0x1f|0xa0; //打开Y5
	P0 = 0x00; 
	P2 &= 0x1f; //释放片选
	//关闭LED
	P2 = P2&0x1f|0x80; //打开Y4
	P0 = 0xff;
	P2 &= 0x1f; //释放片选
}

void writetime(u8 *ds)
{
	u8 i;     
	u8 add=0x80; //DS1302 秒时寄存器（写）地址
	write(0x8e,0x00); //写保护关 
	for(i=0;i<3;i++)
	{
	  write(add,ds[i]);   
	  add=add+2;
	}
	write(0x8e,0x80);
}

void readtime(u8 *time)
{
	u8 i;
	u8 add=0x81; //DS1302 秒时寄存器（读）地址
	write(0x8e,0x00); 
	for(i=0;i<3;i++)
	{
	  time[i]=read(add);
	  add=add+2;
	}
	write(0x8e,0x80);	
}

void BCD_conversion(u8 *time,u8 *dbuf)
{
   u8 i ,j=2;
   time[0] &= 0x7f; //秒
   time[1] &= 0x7f; //分
   time[2] &= 0x3f; //时
   for(i = 0 ; i < 6 ; i++ )
   {
	 dbuf[i++] = time[j]/10;
	 dbuf[i] = time[j--]%10;
   }
}

void ExecClock(u8 KeyNum ,ClockStatus *clockState , TimeStatus *blink)
{
	switch(*clockState)
	{
		case ShowTime:
		 if(KeyNum == 1)  //按下S7进入校时状态
		 {
		   *clockState = ChangeClockHour; //进入校时小时状态
		   *blink = SaveTime; //	对当前时间进行复制
		 }
		break;
		case ChangeClockHour: 
         if(KeyNum == 1)  //按下S7,回到ShowTime 状态
		 {
		   *clockState = ShowTime;  
           *blink = ModifyTheTime; //将修改后时间写入DS1302 					
		 }				
		 if(KeyNum == 2)  //按下S6进入分时闪烁状态
		 {
		   *clockState = ChangeClockMinute;  
		   *blink = FlashMin; //	分时闪烁标志
		 }	  
         if(KeyNum == 3)  //按下S5小时加1
		 {
		   *clockState = ChangeClockHour; 
		   *blink = ChangeHour; //小时加1标志
		 }	
         if(KeyNum == 4)  //按下S4，不修改time回到showtime
		 {
		   *clockState = ShowTime; 
		   *blink = UnmodifiedTime; //回到进入校时状态下的时间
		 }		
		 break;
		case ChangeClockMinute:
		 if(KeyNum == 1)  
		 {
		   *clockState = ShowTime;
		   *blink = ModifyTheTime; 	
	     }				
		 if(KeyNum == 2) //进入秒时状态
		 {
		   *clockState = ChangeClockSecond;
		   *blink = FlashSec; //秒时闪烁状态标志	
		 }
		 if(KeyNum == 3)  //分时加1
		 {
		   *clockState = ChangeClockMinute; 
           *blink = ChangeMin;						
		 }	
		 if(KeyNum == 4)  
		 {
		   *clockState = ShowTime;
           *blink = UnmodifiedTime; 							
		 }				
		break;
	    case ChangeClockSecond:
		 if(KeyNum == 1)  
		 {
		   *clockState = ShowTime;  
		   *blink = ModifyTheTime; 	
		 }				
		 if(KeyNum == 2)//进入小时状态
		 {
		   *clockState = ChangeClockHour;
		   *blink = FlashHour;
		 }	
         if(KeyNum == 3)  //秒时加1
		 {
		   *clockState =ChangeClockSecond; 
           *blink = ChangeSec;	//秒时加1标志				
		 }	
         if(KeyNum == 4)  
		 {
		   *clockState = ShowTime; 
           *blink = UnmodifiedTime; 							
		 }				
		break;					
		default:	
		 {
		    *clockState = ShowTime;
			*blink = WalkTime; 
		 }
		break;
	}
}

void TimeChange(u8 *time,TimeStatus *blink)
{
	switch(*blink)
	{
	  case ChangeHour: //小时加1
		if(++time[2]>=24)time[2]=0;break;	
	  case ChangeMin: //分时加1
		if(++time[1]>=60)time[1]=0;break;	
	  case ChangeSec: //秒时加1
		if(++time[0]>=60)time[0]=0;break;	
	  default: break;
	}
}