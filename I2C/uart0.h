#ifndef __uart0_h
#define __uart0_h

#include <reg51.h>

void InitUART(void);
void putbuf(char c);
void putall(char *s,unsigned int con);

#endif