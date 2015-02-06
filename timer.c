#include "config.h"

void InitTimer(void)
{
	// Timer0 & Timer1 Use Mode 0: 13Bit
	TMOD=0x00;
	
	// Timer0 1ms: 8192-1000 = 0x1c18
 	TH0=0x1c;           // 延时常数
    TL0=0x18;           // 频率调节
	
	// Timer1 0.5ms: 8192-512 = 0x7c80
    TH1=0xff;            // 脉宽调节
    TL1=0xff;
	
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
	//TR1= 0;
    TH0= 0x1c;
    TL0= 0x18;
	
    //TH1= PWM;
    //TR1= 1;
    if(ISR_PWM_FREQ())      //PWM 频率调节
	{
		TR1 = 0;
		TH1 = 0xff;
		TR1 = 1;
	}
}

void timer1() interrupt 3 
{
	//TR1=0 ;
    if(ISR_PWM_PulseWidth())     //脉宽调节
		TR1 = 0;
}