#include "i2c.h"

void Delay1us()		//@12.000MHz
{
	_nop_();
}
 
void I2C_Start()
{
   SDA = 1;
	 SCL = 1;
	 Delay1us();
	 SDA = 0;
	 Delay1us();
	 SCL = 0;
	 Delay1us();
}	

void I2C_Stop()
{
	 SDA = 0;
	 SCL = 1;
	 Delay1us();
	 SDA = 1;
	 Delay1us();
}

void I2C_Ack(u8 ack)
{
	if(ack)
		SDA=1;
	else
		SDA=0;
	SCL=0;
	Delay1us();
	SCL=1;
	Delay1us();
	SCL=0;
}

bit I2C_WaitAck()
{
	u8 i=200;
	SDA=1;
	Delay1us();
	SCL=1;
	while(SDA)
	{
		i--;
		if(!i)
		{
			IIC_Stop();
			return 0;
		}
	}
	SCL=0;
	SDA=1;
	return 1;
}

void I2C_SendByte(u8 dat)
{
	u8 a=0;
	EA = 0;
	for(a=0;a<8;a++)
	 {	 
		 SDA=dat&0x80;
		 dat=dat<<1; 
		 Delay1us();
		 SCL = 1;
		 Delay1us();
		 SCL = 0;
		 Delay1us();
	 }
	 EA = 1;
}

u8 I2C_ReadByte()
{
	u8 a=0,dat=0;
	EA = 0;
	SDA = 1;
	Delay1us();
	for(a=0;a<8;a++)
	{
		SCL = 1;
		Delay1us();
		dat<<=1;
		dat|=SDA;
		Delay1us();
		SCL = 0;
		Delay1us();
	}
	EA = 1;
	return dat;
}
