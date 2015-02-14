#include "config.h"

uchar PWM = 0x1a;
uchar SystemFlag = 0;
int second_count = 0;

sbit dula=P2^6;
sbit wela=P2^7;


void SystemInit(void)
{
	P1 = 0xff;
	EnableIRDA();
	InitTimer();
	DisableLEDs();
	StartPWM();
}

void main()
{
	SystemInit();
	
	while(1)
	{
		//DisplayHex(PWM, 1);
		
		if (SystemFlag & bIRDA)
		{
			IrProcess();
			EnableIRDA();
		}
		
		RateProcess();			// Deal With PWM Speed
		
		if (SystemFlag & bSecond)
			SecondProcess();
	}
	
}

void ISR_Second(void)
{
	if(second_count++ > 7812)
	{
		second_count = 0;
		SystemFlag |= bSecond;
	}
}

void SecondProcess(void)
{
	DisplayHex(SystemFlag, 1);		// Display SystemFlag For Debug
	SystemFlag &= ~bSecond;
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
/*
void delay_nop(void)
{
	_nop_();
	_nop_();
	_nop_();
	_nop_();
}*/