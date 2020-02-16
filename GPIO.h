#include	"GPIO.h"


//========================================================================
// º¯Êý: u8	GPIO_Inilize(u8 GPIO, GPIO_InitTypeDef *GPIOx)
// ÃèÊö: ³õÊ¼»¯IO¿Ú.
// ²ÎÊý: GPIOx: ½á¹¹²ÎÊý,Çë²Î¿¼timer.hÀïµÄ¶¨Òå.
// ·µ»Ø: ³É¹¦·µ»Ø0, ¿Õ²Ù×÷·µ»Ø1,´íÎó·µ»Ø2.
// °æ±¾: V1.0, 2012-10-22
//========================================================================
u8	GPIO_Inilize(u8 GPIO, GPIO_InitTypeDef *GPIOx)
{
	if(GPIO > GPIO_P5)				return 1;	//¿Õ²Ù×÷
	if(GPIOx->Mode > GPIO_OUT_PP)	return 2;	//´íÎó
	if(GPIO == GPIO_P0)
	{
		if(GPIOx->Mode == GPIO_PullUp)		P0M1 &= ~GPIOx->Pin,	P0M0 &= ~GPIOx->Pin;	 //ÉÏÀ­×¼Ë«Ïò¿Ú
		if(GPIOx->Mode == GPIO_HighZ)		P0M1 |=  GPIOx->Pin,	P0M0 &= ~GPIOx->Pin;	 //¸¡¿ÕÊäÈë
		if(GPIOx->Mode == GPIO_OUT_OD)		P0M1 |=  GPIOx->Pin,	P0M0 |=  GPIOx->Pin;	 //¿ªÂ©Êä³ö
		if(GPIOx->Mode == GPIO_OUT_PP)		P0M1 &= ~GPIOx->Pin,	P0M0 |=  GPIOx->Pin;	 //ÍÆÍìÊä³ö
	}
	if(GPIO == GPIO_P1)
	{
		if(GPIOx->Mode == GPIO_PullUp)		P1M1 &= ~GPIOx->Pin,	P1M0 &= ~GPIOx->Pin;	 //ÉÏÀ­×¼Ë«Ïò¿Ú
		if(GPIOx->Mode == GPIO_HighZ)		P1M1 |=  GPIOx->Pin,	P1M0 &= ~GPIOx->Pin;	 //¸¡¿ÕÊäÈë
		if(GPIOx->Mode == GPIO_OUT_OD)		P1M1 |=  GPIOx->Pin,	P1M0 |=  GPIOx->Pin;	 //¿ªÂ©Êä³ö
		if(GPIOx->Mode == GPIO_OUT_PP)		P1M1 &= ~GPIOx->Pin,	P1M0 |=  GPIOx->Pin;	 //ÍÆÍìÊä³ö
	}
	if(GPIO == GPIO_P2)
	{
		if(GPIOx->Mode == GPIO_PullUp)		P2M1 &= ~GPIOx->Pin,	P2M0 &= ~GPIOx->Pin;	 //ÉÏÀ­×¼Ë«Ïò¿Ú
		if(GPIOx->Mode == GPIO_HighZ)		P2M1 |=  GPIOx->Pin,	P2M0 &= ~GPIOx->Pin;	 //¸¡¿ÕÊäÈë
		if(GPIOx->Mode == GPIO_OUT_OD)		P2M1 |=  GPIOx->Pin,	P2M0 |=  GPIOx->Pin;	 //¿ªÂ©Êä³ö
		if(GPIOx->Mode == GPIO_OUT_PP)		P2M1 &= ~GPIOx->Pin,	P2M0 |=  GPIOx->Pin;	 //ÍÆÍìÊä³ö
	}
	if(GPIO == GPIO_P3)
	{
		if(GPIOx->Mode == GPIO_PullUp)		P3M1 &= ~GPIOx->Pin,	P3M0 &= ~GPIOx->Pin;	 //ÉÏÀ­×¼Ë«Ïò¿Ú
		if(GPIOx->Mode == GPIO_HighZ)		P3M1 |=  GPIOx->Pin,	P3M0 &= ~GPIOx->Pin;	 //¸¡¿ÕÊäÈë
		if(GPIOx->Mode == GPIO_OUT_OD)		P3M1 |=  GPIOx->Pin,	P3M0 |=  GPIOx->Pin;	 //¿ªÂ©Êä³ö
		if(GPIOx->Mode == GPIO_OUT_PP)		P3M1 &= ~GPIOx->Pin,	P3M0 |=  GPIOx->Pin;	 //ÍÆÍìÊä³ö
	}
	if(GPIO == GPIO_P4)
	{
		if(GPIOx->Mode == GPIO_PullUp)		P4M1 &= ~GPIOx->Pin,	P4M0 &= ~GPIOx->Pin;	 //ÉÏÀ­×¼Ë«Ïò¿Ú
		if(GPIOx->Mode == GPIO_HighZ)		P4M1 |=  GPIOx->Pin,	P4M0 &= ~GPIOx->Pin;	 //¸¡¿ÕÊäÈë
		if(GPIOx->Mode == GPIO_OUT_OD)		P4M1 |=  GPIOx->Pin,	P4M0 |=  GPIOx->Pin;	 //¿ªÂ©Êä³ö
		if(GPIOx->Mode == GPIO_OUT_PP)		P4M1 &= ~GPIOx->Pin,	P4M0 |=  GPIOx->Pin;	 //ÍÆÍìÊä³ö
	}
	if(GPIO == GPIO_P5)
	{
		if(GPIOx->Mode == GPIO_PullUp)		P5M1 &= ~GPIOx->Pin,	P5M0 &= ~GPIOx->Pin;	 //ÉÏÀ­×¼Ë«Ïò¿Ú
		if(GPIOx->Mode == GPIO_HighZ)		P5M1 |=  GPIOx->Pin,	P5M0 &= ~GPIOx->Pin;	 //¸¡¿ÕÊäÈë
		if(GPIOx->Mode == GPIO_OUT_OD)		P5M1 |=  GPIOx->Pin,	P5M0 |=  GPIOx->Pin;	 //¿ªÂ©Êä³ö
		if(GPIOx->Mode == GPIO_OUT_PP)		P5M1 &= ~GPIOx->Pin,	P5M0 |=  GPIOx->Pin;	 //ÍÆÍìÊä³ö
	}
	return 0;	//³É¹¦
}
//========================================================================
// º¯Êý: void GPIO_WritePin(u8 GPIO , u8 Pinx , bit Level)
// ÃèÊö: ÊµÏÖÒý½Å¸ßµÍµçÆ½
// ²ÎÊý: GPIO £ºÑ¡ÔñP0,P1,P2,P3¶Ë¿Ú
//       Pinx £ºPx^0~Px^7 
//       Level: LOW 0 £¬HIGH  1
// ·µ»Ø: ÎÞ
// °æ±¾: V1.0, 2012-10-22
//========================================================================
u8 GPIO_WritePin(u8 GPIO , u8 Pinx , bit Level)
 { 
	 if(GPIO > GPIO_P5)				return 1;	//¿Õ²Ù×÷
	 if(Pinx > GPIO_Pin_All)	return 2;	//´íÎó
	 if(GPIO == GPIO_P0)
	  {
	   if(Level)
		  P0 &= (~Pinx);
	   else
	    P0 |= Pinx;
    }
	 if(GPIO == GPIO_P1)
	  {
	   if(Level)
		  P1 &= (~Pinx);
	   else
	    P1 |= Pinx ;
    }
		if(GPIO == GPIO_P2)
	  {
	   if(Level)
		  P2 &= (~Pinx);
	   else
	    P2 |= Pinx;
    }
		if(GPIO == GPIO_P3)
	  {
	   if(Level)
		  P3 &= (~Pinx);
	   else
	    P3 |= Pinx;
    }
		if(GPIO == GPIO_P3)
	  {
	   if(Level)
		  P4 &= (~Pinx);
	   else
	    P4 |= Pinx;
    }
		if(GPIO == GPIO_P3)
	  {
	   if(Level)
		  P5 &= (~Pinx);
	   else
	    P5 |= Pinx;
    }
		return 0;
 }
 
