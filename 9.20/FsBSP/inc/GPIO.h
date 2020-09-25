#ifndef	__GPIO_H
#define	__GPIO_H

#include <STC15F2K60S2.h>

#define	GPIO_PullUp		0	//
#define	GPIO_HighZ		1	//
#define	GPIO_OUT_OD		2	//
#define	GPIO_OUT_PP		3	//

#define	GPIO_Pin_0		0x01	//
#define	GPIO_Pin_1		0x02	//
#define	GPIO_Pin_2		0x04	//
#define	GPIO_Pin_3		0x08	//
#define	GPIO_Pin_4		0x10	//
#define	GPIO_Pin_5		0x20	//
#define	GPIO_Pin_6		0x40	//
#define	GPIO_Pin_7		0x80	//
#define	GPIO_Pin_All	0xFF	//
	
#define	GPIO_P0			0		//
#define	GPIO_P1			1
#define	GPIO_P2			2
#define	GPIO_P3			3
#define	GPIO_P4			4
#define	GPIO_P5			5

#define LOW   0   //
#define HIGH  1   //

typedef struct
{
	u8	Mode;		//
	u8	Pin;		//
} GPIO_InitTypeDef;

u8	GPIO_Inilize(u8 GPIO, GPIO_InitTypeDef *GPIOx);
u8 GPIO_WritePin(u8 GPIO , u8 Pinx , bit Level);
bit GPIO_ReadPin(u8 GPIO , u8 Pinx);
u8 GPIO_Read8bit(u8 GPIO);
 
#endif
