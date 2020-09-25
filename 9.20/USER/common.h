# ifndef __common_h__
# define __common_h__
#include <STC15F2K60S2.h>
typedef enum{NoKey, KeyDn, KeyHd, KeyUp}KeyState;		
typedef enum{ShowTime, ShowTemperature, ChangeClockHour, ChangeClockMinute, 
		ChangeClockSecond, ChangeAlertHour, ChangeAlertMinute, 
		ChangeAlertSecond}ClockStatus;
typedef enum{WalkTime,FlashHour,FlashMin,FlashSec,
	         ModifyTheTime,UnmodifiedTime,ChangeHour,ChangeMin,
	         ChangeSec,SaveTime}TimeStatus;
typedef enum{FALSE,TRUE} BOOL;

# endif