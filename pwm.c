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
		pwmFlag |= PWMSTART;
		return 1;
	}
	
	return 0;
}

uchar ISR_PWM_PulseWidth(void)
{
	pulse++;
	if(pulse>=PWM)
	{
		pwmFlag &= ~PWMPULSE;
		pwmFlag &= ~PWMSTART;
		StopPWM();
		pulse = 0;
		return 1;
	}
	
	return 0;
}

void Rate(uchar type)
{
	if (type)		// reduce speed
	{
		if (PWM < 0x20)
			PWM++;
		else
			Beep();
	}
	else			// increase speed
	{
		if(PWM > 2)
			PWM--;
		else
			Beep();
	}
}

void RateProcess(void)
{
	if (KeyFlag & KEY1ON)
	{
		Rate(1);
		KeyFlag &= ~(KEY1ON);
	}
	else if (KeyFlag & KEY2ON)
	{
		KeyFlag &= ~(KEY1ON);
	}
}