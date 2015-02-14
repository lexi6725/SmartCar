#include "config.h"

sbit diola = P2^5;

void DisplayLED(uchar Bits)
{
	diola = 0;
	P1 = Bits;
	diola = 1;
	diola = 0;
}

void DisplayLEDFlag(uchar flag)
{
	DisplayLED(~flag);
}