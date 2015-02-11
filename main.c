#include "config.h"

uchar PWM = 0x70;
uchar SystemFlag = 0;

sbit dula=P2^6;
sbit wela=P2^7;

void DisableLED()
{
	P0=0x00;
	dula=1;
	wela=0;
	delay(10);
	dula=0;
	wela=0;
	delay(10);
}	

void SystemInit(void)
{
	P1 = 0xff;
	InitIRDA();
	InitTimer();
	DisableLED();
}

void main()
{
	SystemInit();
	
	while(1)
	{
		KeyCheck();
		
		if (SystemFlag & bIRDA)
			IrProcess();
		
		delayms(100);
		
		RateProcess();
	}
	
}



void delayms(uchar ms)
{
	SystemFlag |= bDelay;
	while(1)
	{
		if (timer0_count > ms*8)
		{
			SystemFlag &= ~bDelay;
			return;
		}
	}
}

void delay(uchar t)
{ 
	while(--t);
}