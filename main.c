#include "config.h"

uchar PWM = 0x3;

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
	InitTimer();
	DisableLED();
}

void main()
{
	uchar key;
	SystemInit();
	
	while(1)
	{
		ISR_KEY();
		key = 0;
		ISR_IRDA();
		delayms(100);
	}
	
}



void delayms(uchar ms)
{
	unsigned char i ;
	while(ms--)
	{
		for(i = 0 ; i < 120 ; i++) ;
	}
}

void delay(uchar t)
{ 
	int k;
	for (k = 0; k < 10*t; ++k);
}