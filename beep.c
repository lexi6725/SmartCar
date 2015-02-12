#include "config.h"

sbit  BEEP =P2^3;

void Beep(void)
{
	unsigned char i;
	for (i=0;i<100;i++)
	{
		delay(100);
		BEEP=!BEEP;
	} 
	BEEP=1;
	delayms(10);
}