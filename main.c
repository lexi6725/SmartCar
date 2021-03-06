#include "config.h"

uchar PWM = 0x10;
uchar SystemFlag = 0;

sbit dula=P2^6;
sbit wela=P2^7;


/*void DisableLED()
{
	P0=0x00;
	dula=1;
	wela=0;
	delay(10);
	dula=0;
	wela=0;
	delay(10);
}	*/

void SystemInit(void)
{
	P1 = 0xff;
	EnableIRDA();
	InitTimer();
	//DisableLED();
	DisableLEDs();
}

void main()
{
	SystemInit();
	
	while(1)
	{
		//KeyCheck();
		//DisplayHex(KeyFlag, 1);
		//DisplayHex(SystemFlag, 3);
		//DisplayHex(pwmFlag, 5);
		
		if (SystemFlag & bIRDA)
		{
			IrProcess();
			EnableIRDA();
		}
		
		//delayms(100);
		
		RateProcess();
	}
	
}



void delayms(uchar ms)
{
	SystemFlag |= bDelay;
	while(1)
	{
		if (timer0_count > ms)
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