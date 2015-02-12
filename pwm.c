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
		//StartPWM();
		P0 = 0;
		freq = 0;
		pwmFlag |= PWMSTART;
		//P1 = ~pwmFlag;
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
		//P1 = ~pwmFlag;
		//StopPWM();
		P0 = 0xff;
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
		//DisplayHex(PWM, 1);
	}
	else			// increase speed
	{
		if(PWM > 2)
			PWM--;
		else
			Beep();
		//DisplayHex(PWM, 1);
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
		Rate(0);
		KeyFlag &= ~(KEY2ON);
	}
}