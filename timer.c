#include "config.h"

uchar timer0_count = 0;

void InitTimer(void)
{
	// Timer0 & Timer1 Use Mode 0: 13Bit
	TMOD = (0|T0M0|T1M0);
	
	/*
	 * Timer0: 0.128ms Interrupt
	 */
 	TH0=TIMER0PRETH;      	// Frequency
    TL0=TIMER0PRETL;
	
    TH1=TIMER1PRETH;      	// Pulse Width
    TL1=TIMER1PRETL;
	
	Enable_Interrupt();		// Enabel Interrupt
	Enable_TIMER0_Int();	// Enabel Timer0 Interrupt
	Enable_TIMER1_Int();	// Enabel Timer0 Interrupt
    StartTimer0();			// Start Timer0
}

/*
 * Timer0: Use 0.128ms
 * 
 */
void timer0() interrupt 1 
{
    TH0= TIMER0PRETH;
    TL0= TIMER0PRETL;
	
	ISR_IRDA_PulseWidth();
	
	// ISR PWM Frequrey
    if(ISR_PWM_FREQ())      //PWM Frequency
	{
		pwmFlag |= PWMPULSE;
		DispFlag();
	}
	DispFlag();
	if (pwmFlag&PWMPULSE)
	{
		ISR_PWM_PulseWidth();
		DispFlag();
	}
	
	KeyCheck();
	ISR_KEY();
	
	if (SystemFlag&bDelay)		// Delay count
		timer0_count++;
	else
		timer0_count = 0;
	
	ISR_Second();
}

void timer1() interrupt 3 
{
	
}