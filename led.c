#include "config.h"

sbit diola = P2^5;
static uchar keydisp;

void DisplayLED(uchar Bits)
{
	diola = 0;
	P1 = Bits;
	diola = 1;
	diola = 0;
}

void DisplayLEDFlag(uchar flag)
{
	uchar i;
	for(i = 0; i < 8; ++i)
		if(flag&(1<<i))
			keydisp |= (1<<i);
		else
			keydisp &= ~(1<<i);
	DisplayLED(~keydisp);
}