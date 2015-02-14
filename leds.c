#include "config.h"

sbit dula=P2^6;
sbit wela=P2^7;

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

void SelectBit(uchar addr)
{
	while(((pwmFlag&PWMSTART)&&(DigitTab[addr]&SEG_a)) || (!(pwmFlag&PWMSTART) && !(DigitTab[addr]&SEG_a)));
	wela = 0;
	P0 = 0x7e<<(addr-1);
	wela = 1;
	wela = 0;
}

void SendChar(uchar num)
{
	while(((pwmFlag&PWMSTART)&&(DigitTab[num]&SEG_a)) || (!(pwmFlag&PWMSTART) && !(DigitTab[num]&SEG_a)));
	dula = 0;
	P0 = DigitTab[num];
	dula = 1;
	dula = 0;
}

void DisplayHex(uchar num, uchar addr)
{
	SendChar(num&0xf);
	SelectBit(addr);
	SendChar((num&0xf0)>>4);
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