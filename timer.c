#include "config.h"

void InitTimer(void)
{
	// Timer0 & Timer1 Use Mode 0: 13Bit
	TMOD=0x00;
	
	// Timer0 1ms: 8192-1024 = 0x1c00
 	TH0=0xf0;           // 延时常数
    TL0=0x00;           // 频率调节
	
	// Timer1 0.5ms: 8192-512 = 0x7c80
    TH1=0xff;            // 脉宽调节
    TL1=0x00;
	
	EA=1;
	ET0=1;
	ET1=1;
    TR0=1;				// 关闭定时器1
}

/*
 * Timer0: Use 1ms
 * 
 */
void timer0() interrupt 1 
{
    TH0= 0xe0;
    TL0= 0x00;
	
    if(ISR_PWM_FREQ())      //PWM 频率调节
	{
		TR1 = 0;
		TH1 = 0xfe;
		TR1 = 1;
	}
		
}

void timer1() interrupt 3 
{
    if(ISR_PWM_PulseWidth())     //脉宽调节
		TR1 = 0;
	else
	{
		TH1 = 0xfe;
	}
}