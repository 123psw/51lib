#include "user.h"

void init_IO()
{
	P2 = P2&0x1f|0xa0; //??Y5
	P0 = 0x00; 
	P2 &= 0x1f; //????

	P2 = P2&0x1f|0x80; //??Y4
	P0 = 0xff;
	P2 &= 0x1f; //????
}


void BCD_conversion(u8 *time,u8 *dbuf)
{
   time[0] &= 0x7f; //?
   time[1] &= 0x7f; //?
   time[2] &= 0x3f; //?
   
   dbuf[0] = time[2]/10;
   dbuf[1] = time[2]%10;
   dbuf[2] = 11;
   dbuf[3] = time[1]/10;
   dbuf[4] = time[1]%10;
   dbuf[5] = 11;
   dbuf[6] = time[0]/10;
   dbuf[7] = time[0]%10;
}

void ExecTemperature(u8 KeyNum ,TemperatureRecordStatus *tr , KeyCount *keyout)
{
	switch(*tr)
	{
		case ParameterSettings:
		 if(KeyNum == 4)   //S4
		 {
		   *tr = ParameterSettings;
		 } 
		 if(KeyNum == 3)  //S5
		 {
		   *tr = ConfirmTheAcquisition; 
        keyout->S5 = 0;      
		 }  
    break;     
    case TemperatureDisplay:
     if(KeyNum == 2)  //S6
		 {
       LedOff();
		   *tr = TemperatureDisplay;
	   } 
     if(KeyNum == 1)  
		 {
		   *tr = ParameterSettings;
	   }          
		break; 
	}
}

void display(u8 KeyNum, KeyCount *keycount)
{
  switch(KeyNum)
	{
		case 4:
		   (keycount->S4)++;
       if((keycount->S4)>=4)
         (keycount->S4)=0;
		break;
     
    case 2:
       (keycount->S6)++;
       if((keycount->S6)>=10)
         (keycount->S6)=0;
    break;
	}
}

void LedOff()
{
  P2 = P2&0x1f|0x80; //??Y4
	P0 = 0xFF;
	P2 &= 0x1f; //????
}

void LedFlash(u8 flash)
{
 switch(flash)
 {
   case 0: P2 = P2&0x1f|0x80; P0 = 0xFE; P2 &= 0x1f; break;
   case 1: P2 = P2&0x1f|0x80; P0 = 0xFF; P2 &= 0x1f; break;
 }
}

void ParameterSettingInterface(u8 S4)
{
  static u8 a[]={10,10,10,10,10,11,0,1};
  switch(S4)
  {
    case 0: a[6]=0; a[7]=1; segdisp(a); break;
    case 1: a[6]=0; a[7]=5; segdisp(a); break;
    case 2: a[6]=3; a[7]=0; segdisp(a); break;
    case 3: a[6]=6; a[7]=0; segdisp(a); break;
  }    
}

void TemperatureAcquisitionDisplayInterface(u8 S6 , u8 *a ,u8 *wendu)
{
  a[0] = 0;
  a[2] = 11;
  a[3] = 10;
  a[4] = 10;
  a[5] = 11;
  switch(S6)
  {
    case 0: a[1]=0; a[6] = wendu[0]/10; a[7] = wendu[0] %10; segdisp(a); break;
    case 1: a[1]=1; a[6] = wendu[1]/10; a[7] = wendu[1] %10; segdisp(a); break;
    case 2: a[1]=2; a[6] = wendu[2]/10; a[7] = wendu[2] %10; segdisp(a); break;
    case 3: a[1]=3; a[6] = wendu[3]/10; a[7] = wendu[3] %10; segdisp(a); break;
    case 4: a[1]=4; a[6] = wendu[4]/10; a[7] = wendu[4] %10; segdisp(a); break;
    case 5: a[1]=5; a[6] = wendu[5]/10; a[7] = wendu[5] %10; segdisp(a); break;
    case 6: a[1]=6; a[6] = wendu[6]/10; a[7] = wendu[6] %10; segdisp(a); break;
    case 7: a[1]=7; a[6] = wendu[7]/10; a[7] = wendu[7] %10; segdisp(a); break;
    case 8: a[1]=8; a[6] = wendu[8]/10; a[7] = wendu[8] %10; segdisp(a); break;
    case 9: a[1]=9; a[6] = wendu[9]/10; a[7] = wendu[9] %10; segdisp(a); break; 
  }    
} 

void Copy(u8 *a , u8 c , unsigned long *m , unsigned long *n) //????
{
  static u8 b[3];
  if(c == 0)
  {
	 b[0] = a[0];
	 b[1] = a[1];
	 b[2] = a[2];
   *m = (unsigned long)b[2]*3600+(unsigned long)b[1]*60+(unsigned long)b[0];
  }
	
	*n = (unsigned long)a[2]*3600+(unsigned long)a[1]*60+(unsigned long)a[0];
}
void TimeShow(u8 *time ,u8 *dbuf , KeyCount keyout , u8 *wendu , TemperatureRecordStatus *tr)
{
  static unsigned long m = 0;
  unsigned long n = 0;
  static u8 i = 0,j = 0,k = 0,l = 0;
  u16 min = 0;
  readtime(time);  
  BCD_conversion(time,dbuf);
  Copy(time,keyout.S5,&m,&n);
  switch(keyout.S4)
  {
    case 0: 
    {
      if(n - m == 1)
      {
        m = n;
        wendu[i++] = temget();
        if(i >= 10)
         {
          i=0;
          *tr = TemperatureDisplay;    
         }
      }
    }
    break;
    case 1:
    {
      if(n - m == 5)
      {
        m = n;
        wendu[j++] = temget();
        if(j >= 10)
         {
          j=0;
          *tr = TemperatureDisplay;    
         }
      }
    }
      break;
    case 2: 
    {
      if(n - m == 30)
      {
        m = n;
        wendu[k++] = temget();
        if(k >= 10)
         {
          k=0;
          *tr = TemperatureDisplay;    
         }
      }
    }
    break;
    case 4:
    {
      if(n - m == 60) 
      {
        m = n;
        wendu[l++] = temget();
        if(l >= 10)
         {
          l=0;
          *tr = TemperatureDisplay;    
         }
      }
    }     
    break;
  }
}
  