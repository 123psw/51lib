#ifndef __user_h_
#define __user_h_

#include "SEGLED.h"
#include "DS18B20.h"
#include "DS1302.h"
#include "bsp_key.h"
#include <STC15F2K60S2.h>
typedef struct{
  u8 S4; 
  u8 S5;
  u8 S6;
} KeyCount;

void init_IO();
void BCD_conversion(u8 *time,u8 *dbuf);
void ExecTemperature(u8 KeyNum ,TemperatureRecordStatus *tr , KeyCount *keycount);
void display(u8 KeyNum , KeyCount *keycount);
void LedOff();
void LedFlash(u8 flash);
void ParameterSettingInterface(u8 S4);
void TemperatureAcquisitionDisplayInterface(u8 S6 , u8 *a ,u8 *wendu);
void TimeShow(u8 *time ,u8 *dbuf , KeyCount keyout , u8 *wendu , TemperatureRecordStatus *tr);

#endif