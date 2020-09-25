#ifndef __PCF8563_H
#define __PCF8563_H

#include "24c02.h"

typedef struct{
	unsigned char day;
	unsigned char mouth;
	unsigned char year;
}Date;

void Delay40ms();
void PCF8563_Write_Date(Date date);
void PCF8563_Read_Date(uchar *p);
void PCF8563_ReadPage_Time(uchar *p);
void PCF8563_WritePage_Time(uchar *p);
#endif