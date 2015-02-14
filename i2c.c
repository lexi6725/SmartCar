#include "config.h"

sbit sda = P2^0;
sbit scl = P2^1;

void StartI2C(void)
{
	sda = 1;
	scl = 1;
	delay_nop();
	sda = 0;
	delay_nop();
	scl = 0;
}

void StopI2C(void)
{
	sda = 0;
	delay_nop();
	scl = 1;
	delay_nop();
	sda = 1;
}

bit WriteByte(uchar byte)
{
	uchar i;
	bit ack;
	
	for(i = 0; i < 8; ++i)
	{
		sda = (bit)(byte & 0x80);
		_nop_();
		scl = 1;
		delay_nop();;
		scl = 0;
		byte <<= 1;
	}
	sda = 1;
	delay_nop();
	scl = 1;
	delay_nop();
	ack = sda;
	scl = 0;
	
	return ack;
}

uchar ReadByte(void)
{
	uchar byte, i;
	
	for (i = 0; i < 8; ++i)
	{
		scl = 1;
		byte <<= 1;
		byte |= sda;
		scl = 0;
	}
	
	return byte;
}

void WriteChar(uchar addr, uchar dat)
{
	StartI2C();
	WriteByte(0xa0);
	WriteByte(addr);
	WriteByte(dat);
	StopI2C();
	delayms(10);
}

uchar ReadChar(uchar addr)
{
	uchar dat;
	
	StartI2C();
	WriteByte(0xa0);
	WriteByte(addr);
	StartI2C();
	WriteByte(0xa1);
	dat = ReadByte();
	StopI2C();
	
	return dat;
}