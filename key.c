#include "config.h"

sbit  S2 =P3^4 ;
sbit  S3 =P3^5 ;

void ISR_KEY(void)
{
	do{
		if (PWM >= 0x2)
		{
			PWM--;
			delayms(10);
		}
		else
			Beep();
	}while(S3==0);
	
	do{
		if (PWM <= 0xff)
		{
			PWM++;
			delayms(10);
		}
		else
			Beep();
	}while(S2==0);
}