#include "config.h"

uchar freq = 0;
uchar pulse = 0;
sbit pwm=P0^0;
uchar pwmFlag = 0;

uchar ISR_PWM_FREQ(void)
{
	freq++;
	if (freq>=PWM_FREQ)
	{
		StartPWM();
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
		StopPWM();
		pulse = 0;
		return 1;
	}
	
	return 0;
}

void RateProcess(void)
{
	if (KeyFlag & KEY1ON)
	{
		if(PWM >= 1)
			PWM--;
		else
			Beep();
		KeyFlag &= ~(KEY1ON);
	}
	else if (KeyFlag & KEY2ON)
	{
		if (PWM < 0x20)
			PWM++;
		else
			Beep();
		KeyFlag &= ~(KEY1ON);
	}
}