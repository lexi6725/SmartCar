#include "config.h"

uchar PWM = 0xff;

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
	DisableLED();
	InitTimer();
}

void main()
{
	uchar key;
	SystemInit();
	
	while(1)
	{
		key = ISR_KEY();
		if (key == '+')
		{
			if (PWM < 0xff)
				PWM++;
			else
				Beep();
		}
		else if (key == '-')
		{
			if (PWM > 2) 
				PWM--;
			else
				Beep();
		}
		ISR_IRDA();
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
	for (k = 0; k < 100*t; ++k);
}