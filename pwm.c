#include "config.h"

uchar freq = 0;
uchar pulse = 0;
sbit pwm=P0^0;

uchar ISR_PWM_FREQ(void)
{
	freq++;
	if (freq>=0x10)
	{
		pwm |= 1;
		freq = 0;
		return 1;
	}
	
	return 0;
}

uchar ISR_PWM_PulseWidth(void)
{
	pulse++;
	if(pulse>=PWM)
	{
		pwm = 0;
		pulse = 0;
		return 1;
	}
	
	return 0;
}