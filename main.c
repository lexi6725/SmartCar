#include "config.h"

unsigned char PWM = 0x3;

void SystemInit(void)
{
}

void main()
{
	uchar key;
	SystemInit();
	
	while(1)
	{
		key = ISR_KEY();
	}
	
}

void timer0() interrupt 1 
{
}

void timer1() interrupt 3 
{
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
   while(t--)   ;
 }