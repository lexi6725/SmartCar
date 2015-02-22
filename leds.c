#include "config.h"

sbit dula=P2^6;
sbit wela=P2^7;

sbit pwm=P0^0;
uchar code DigitTab[] = {CHAR_0, CHAR_1, CHAR_2, CHAR_3, CHAR_4, CHAR_5, CHAR_6, CHAR_7, CHAR_8, CHAR_9, CHAR_A, CHAR_B, CHAR_C, CHAR_D, CHAR_E, CHAR_F};


void DisableLEDs(void)
{
	P0=0x00;
	dula=1;
	wela=0;
	delay(10);
	dula=0;
	wela=0;
	delay(10);
	P0 = 0xff;
}

void RetryPWM(void)
{
	if (pwmFlag & PWMSTART)
	{
		pwm = 0;
	}
	else
	{
		pwm = 1;
	}
}

void SelectBit(uchar addr)
{
	SystemFlag |= bDisplay;
	//while(((pwmFlag&PWMSTART)&&(addr != 1)) || (!(pwmFlag&PWMSTART)&&(addr == 1)));
	wela = 0;
	P0 = 0x7e<<(addr-1);
	wela = 1;
	//wela = 0;
	SystemFlag &= ~bDisplay;
	RetryPWM();
}

void SendChar(uchar num)
{
	SystemFlag |= bDisplay;
	//while(((pwmFlag&PWMSTART)&&(DigitTab[num]&SEG_a)) || (!(pwmFlag&PWMSTART) && !(DigitTab[num]&SEG_a)));
	dula = 0;
	P0 = DigitTab[num];
	dula = 1;
	//dula = 0;
	SystemFlag &= ~bDisplay;
	RetryPWM();
}

void DisplayHex(uchar num, uchar addr)
{
	SendChar(num%0x10);
	SelectBit(addr);
	SendChar(num/0x10);
	SelectBit(addr+1);
}
/*
void DisplayDigital(uchar num, uchar addr)
{
	uchar i;
	for(i = 0; i < 3; ++i)
	{
		SelectBit(addr+i);
		SendChar(num%10);
		num /= 10;
	}	
}*/