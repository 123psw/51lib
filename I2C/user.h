#ifndef __user_h
#define __user_h

#include "PCF8563.h"

sbit LED_RED = P3^5;
sbit LED_GREEN = P3^4;

void BCD(uchar *p,bit flag);
uchar Judge(uchar *a,uchar *b,uchar *c);//Led��״̬�ж�
void LedOn(); //����
void LedOff();//����
void Led_Init();
uchar psw(uchar *p,uchar *s);
void usart_back(uchar *p);
#endif
