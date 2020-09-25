#include "24c02.h"

void AT24c02_Write(uchar addw,uchar add,uchar dat)
{
	IIC_Start();
	IIC_SendByte(addw);
	IIC_WaitAck();
	IIC_SendByte(add);
	IIC_WaitAck();
	IIC_SendByte(dat);
	IIC_WaitAck();
	IIC_Stop();
}

uchar AT24c02_Read(uchar addw,uchar add,uchar addr)
{
	unsigned char dat;
	IIC_Start();
	IIC_SendByte(addw);
  IIC_WaitAck();
	IIC_SendByte(add);
  IIC_WaitAck();
	IIC_Start();
	IIC_SendByte(addr);
	IIC_WaitAck();
	dat = IIC_ReadByte();
	IIC_Ack(1);
	IIC_Stop();
	return dat;
}

void AT24c02_WritePage(uchar addw,uchar add,uchar *p,uchar count)
{
	uchar i;
	IIC_Start();
	IIC_SendByte(addw);
	IIC_WaitAck();
	IIC_SendByte(add);
	IIC_WaitAck();
	for(i=0;i<count;i++)
	{
		IIC_SendByte(*p);
		IIC_WaitAck();
		p++;
	}
	IIC_Stop();
}

void AT24c02_ReadPage(uchar addw,uchar add,uchar addr,uchar *a,uchar count)
{
	uchar i;
	IIC_Start();
	IIC_SendByte(addw);
  IIC_WaitAck();
	IIC_SendByte(add);
	IIC_WaitAck();
	IIC_Start();
	IIC_SendByte(addr);
	IIC_WaitAck();
	for(i=0;i<count-1;i++)
	{
		*a = IIC_ReadByte();
		IIC_Ack(0);
		a++;
	}
	*a = IIC_ReadByte();
	IIC_Ack(1);
	IIC_Stop();
}

void AT_WritePage_LedOn(uchar *p)
{
	AT24c02_WritePage(0xa0,0x08,p,3);
}

void AT_WritePage_LedOff(uchar *p)
{
	AT24c02_WritePage(0xa0,0x10,p,3);
}