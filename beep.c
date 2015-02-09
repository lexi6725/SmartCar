#include "config.h"

sbit  BEEP =P2^3;

void Beep(void)
{
	unsigned char i;
	for (i=0;i<10;i++)
	{
		delay(1);
		BEEP=!BEEP;
	} 
	BEEP=1;
	delayms(1);
}