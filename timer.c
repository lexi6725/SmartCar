#include "config.h"

uchar timer0_count = 0;

void InitTimer(void)
{
	// Timer0 & Timer1 Use Mode 0: 13Bit
	TMOD = (0|T0M0|T1M0);
	
 	TH0=TIMER0PRETH;      // 延时常数
    TL0=TIMER0PRETL;           // 频率调节
	
    TH1=TIMER1PRETH;      // 脉宽调节
    TL1=TIMER1PRETL;
	
	Enable_Interrupt();
	Enable_TIMER0_Int();
	Enable_TIMER1_Int();
    StartTimer0();				// 关闭定时器1
}

/*
 * Timer0: Use 1ms
 * 
 */
void timer0() interrupt 1 
{
    TH0= TIMER0PRETH;
    TL0= TIMER0PRETL;
	
	// ISR PWM Frequrey
    if(ISR_PWM_FREQ())      //PWM 频率调节
	{
		/*StopTimer1();
		TH1 = TIMER1PRE;
		StartTimer1();*/
		pwmFlag |= PWMPULSE;
	}
	if (pwmFlag&PWMPULSE)
	{
		if(ISR_PWM_PulseWidth())
			pwmFlag &= ~PWMPULSE;
	}
	
	if (KeyFlag & 0x0f)
	{
		ISR_KEY();
	}
	
	if (SystemFlag&bDelay)
		timer0_count++;
	else
		timer0_count = 0;
}

void timer1() interrupt 3 
{
	// ISR PWM PluseWidth
    /*if(ISR_PWM_PulseWidth())     //脉宽调节
	{
		StopTimer1();
	}
	else
	{
		TH1 = TIMER1PRE;
	}*/
	
}