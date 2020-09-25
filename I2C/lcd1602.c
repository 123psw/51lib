/********************************
FILE NAME:        lcd1602.c
CHIP TYPE:        AT89C51
CLOCK FREQUENCY:  12MHZ
IDE:              VSMStudio
COMPILER:         IAR for 8051
TIME:             September 2010
********************************/

#include <reg51.h>
#include "IIC.h"
#include <intrins.h> 
#include "lcd1602.h"
#define DATA_BUS  P0 

sbit RS=P2^0;
sbit RW=P2^1; 
sbit E=P2^2;


/*******************************************
    LCD1602 Driver mapped as IO peripheral
*******************************************/
// delaym
void delaym(uint j)
 { uchar i = 60;
   for(; j>0; j--)
    { while(--i);
      i = 59;
      while(--i);
      i = 60;
    }
 }

// Test the Busy bit
void check_busy(void)
 { do
    { DATA_BUS = 0xff;
      E = 0;
      RS = 0; 
      RW = 1;
      E = 1;
      _nop_();
    } while(DATA_BUS & 0x80);
   E = 0;
 }

// Write a command
void write_command(uchar com)
 { check_busy();
   E = 0;
   RS = 0;
   RW = 0;
   DATA_BUS = com;
   E = 1;
   _nop_();
   E = 0;
   delaym(1);
 }

// Write Data
void write_data(uchar Adata)
 { check_busy();
   E = 0;
   RS = 1;
   RW = 0;
   DATA_BUS = Adata;
   E = 1;
   _nop_();
   E = 0;
   delaym(1);
 }

// Initialize LCD controller
void LCD_init(void)
 { write_command(0x38); // 8-bits, 2 lines, 7x5 dots
   write_command(0x0C); // no cursor, no blink, enable display
   write_command(0x06); // auto-increment on
   write_command(0x01); // clear screen
   delaym(1);
 }

// Display a string
void string(uchar ad, uchar *s)
 { write_command(ad);
   while(*s>0)
    { write_data(*s++);
      delaym(100);
    }
 }
 // display string
 void disp(uchar ad, uchar *s)
 { write_command(ad);
   while(*s>0)
    { write_data(*s++);
     // delaym(100);
    }
 }