#ifndef __24c02_H
#define __24c02_H

#include <reg51.h>
#include "IIC.h"

void AT24c02_Write(uchar addw,uchar add,uchar dat);
unsigned char AT24c02_Read(uchar addw,uchar add,uchar addr);
void AT24c02_WritePage(uchar addw,uchar add,uchar *p,uchar count);
void AT24c02_ReadPage(uchar addw,uchar add,uchar addr,uchar *a,uchar count);
void AT_WritePage_LedOn(uchar *p);
void AT_WritePage_LedOff(uchar *p);
#endif