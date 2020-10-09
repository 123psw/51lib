#include <STC15F2K60S2.h>
#include "user.h"
#include "bsp_key.h"
#include "DS1302.h"
bit flash = 0;
bit ledflash = 0;
TemperatureRecordStatus tr = ParameterSettings;
KeyCount keyout;
KeyState keystate = NoKey;
u8 isTime2GetKeyVal = 0;

void Timer0Init(void)		//20??@12.000MHz
{
	AUXR &= 0x7F;		//?????12T??
	TMOD &= 0xF0;		//???????
	TL0 = 0xE0;		//??????
	TH0 = 0xB1;		//??????
	TF0 = 0;		//??TF0??
	TR0 = 1;		//???0????
}

void init_EA()
{
  EA = 1;
  ET0 = 1;
}

void timer0() interrupt 1
{
  static u8 cnt = 0;
  cnt++;
  ReadLine(&keystate ,&isTime2GetKeyVal);
  if(cnt % 10 == 0) ledflash = ~ledflash;
  if(cnt % 25 == 0) flash = ~ flash;
  if(cnt >= 250) cnt = 0;
}
void main()
{
  u8 time[] ={45,23,10};
  u8 dbuf[]={0,0,0,0,0,0,0,0};
  u8 wendu[] = {0,0,0,0,0,0,0,0,0,0};
	init_IO();
  Timer0Init();
  init_EA();
  writetime(time);
	while(1)
  {
    if(isTime2GetKeyVal)
		{
			isTime2GetKeyVal=0;
			ExecTemperature(GetKeyNum(),&tr,&keyout);
      display(GetKeyNum(),&keyout);
		}
    switch(tr)
    {
      case ParameterSettings: ParameterSettingInterface(keyout.S4); break;
      case ConfirmTheAcquisition: TimeShow(time,dbuf,keyout,wendu,&tr); keyout.S5 = 1;TimeFlash(dbuf,flash); break;
      case TemperatureDisplay: 
        if(GetKeyNum() == 3)
         LedFlash(ledflash);
        TemperatureAcquisitionDisplayInterface(keyout.S6,dbuf,wendu); break;
    }
  }
}