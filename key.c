#include "config.h"

sbit  S2 =P3^4 ;
sbit  S3 =P3^5 ;

uchar ISR_KEY(void)
{
	int i = 2;
	if (S2 == 0)
	{
		delayms(10);
		if (S2 == 0)
			return '-';
	}
	if (S3 == 0)
	{
		delayms(10);
		if (S3 == 0)
			return '+';
	}
	
	return 0;
}