#include "config.h"

uchar freq = 0;
uchar pulse = 0;
sbit pwm=P0^0;
uchar pwmFlag = 0;

/*
 * Name: ISR_PWM_FREQ
 * Func: Interrupt Server for PWM frequency
 * Args: void
 * Ret: Frequency OK Or Not
 */
uchar ISR_PWM_FREQ(void)
{
	if (!PWMisRun())
	{
		pwmFlag &= ~(PWMSTART|PWMPULSE);
		pwm = 1;
		return 0;
	}
	
	freq++;
	if (freq>=PWM_FREQ)	// Timer0 * PWM_FREQ = 0.128ms * 32 = 4.096ms = 244
	{
		pwm = 0;			// Start out PWM
		freq = 0;
		pwmFlag |= PWMSTART;	// Set Start PWM Flag
		return 1;
	}
	
	return 0;
}


/*
 * Name: ISR_PWM_PulseWidth
 * Func: Server For PWM Pulse Width
 * Args: void
 * Ret:  Pulse Width OK or Not
 */
uchar ISR_PWM_PulseWidth(void)
{
	pulse++;
	if(pulse>=PWM)			// Speed Controller
	{
		pwmFlag &= ~PWMPULSE;
		pwmFlag &= ~PWMSTART;
		pwm = 0x1;			// Stop out PWM
		pulse = 0;
		return 1;
	}
	
	return 0;
}

void Rate(uchar type)
{
	if (type)		// reduce speed
	{
		if (PWM < 0x20)		// Min Speed
			PWM++;
		else
			Beep();
	}
	else			// increase speed
	{
		if(PWM > 2)
			PWM--;			// Max Speed
		else
			Beep();
	}
}

void RateProcess(void)
{
	if (KeyFlag & KEY1ON)		// reduce speed key
	{
		Rate(1);
		KeyFlag &= ~(KEY1ON);
	}
	else if (KeyFlag & KEY2ON)	// increase speed key
	{
		Rate(0);
		KeyFlag &= ~(KEY2ON);
	}
	if (KeyFlag & KEY3ON)		// stop pwm key
	{
		StopPWM();
		pwm = 1;
		KeyFlag &= ~(KEY3ON);
	}
	if (KeyFlag & KEY4ON)		// start pwm key
	{
		StartPWM();
		KeyFlag &= ~(KEY4ON);
	}
}