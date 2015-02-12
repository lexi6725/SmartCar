#include "config.h"

sbit dula=P2^6;
sbit wela=P2^7;

void EnableLEDs(void)
{

}

void DisableLEDs(void)
{
	P0=0x00;
	dula=1;
	wela=0;
	delay(10);
	dula=0;
	wela=0;
	delay(10);
}

void SelectBit(uchar addr)
{
	wela = 0;
	P0 = addr;
	wela = 1;
}

void SendChar(uchar n)
{
	dula = 0;
	P0 = n;
	dula = 1;
}

void DisplayHex(uchar num, uchar addr)
{
	while(((pwmFlag&PWMSTART)&&(num&0x1)) || (!(pwmFlag&PWMSTART) && !(num&0x1)));
	
	SelectBit(addr);
	SendChar(num);
}

void DisplayDigital(uchar num, uchar addr)
{
	SelectBit(addr);
	SendChar(num);
}