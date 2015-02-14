#ifndef __CONFIG_H_
#define __CONFIG_H_
#include <reg51.h>
#include <intrins.h>

typedef unsigned char uchar;

// System Flag
extern uchar SystemFlag;
#define bSecond		(1<<5)
#define bIRDA		(1<<6)
#define bDelay		(1<<7)

// Define Timer0 and Timer1 Preset value
#define TIMER0PRETH	0xF8	// Timer0 0.128ms: 8192-256 = 0x1F00 / 0x20 = 0xF8
#define TIMER0PRETL	0x00
#define TIMER1PRETH	0xC1	// Timer1 0.016ms: 8192- 32 = 0x1FE0 / 0x20 = 0xFF
#define TIMER1PRETL	0x10

// Timer Mode Define
#define T0M0	0x00
#define T0M1	0x01
#define T0M2	0x02
#define T0M3	0x03
#define T1M0	0x00
#define T1M1	0x04
#define T1M2	0x08
#define T1M3	0x0c

// PWM
extern uchar PWM;			// Speed Control
extern uchar pwmFlag;		// PWM Status Flag
extern bit pwmstartflag;
#define PWMPULSE	(1<<0)
#define PWMSTART	(1<<1)
#define PWMRUN		(1<<2)
#define PWM_FREQ	32		// Timer0 * PWM_FREQ = 0.128 * 32 = 4.096 ms  PWM Freq = 1000/4.096 = 244Hz
#define StartPWM()	(pwmFlag |= PWMRUN)
#define StopPWM()	(pwmFlag &= !PWMRUN)
#define PWMisRun()	(pwmFlag & PWMRUN)

// Key
extern uchar KeyFlag;
#define KEYNUM			4
#define KEYDELAYTIME	0xA0	// 80 * 0.128ms = 10.24ms
#define KEY1DOWN	(1<<0)
#define KEY2DOWN	(1<<1)
#define KEY3DOWN	(1<<2)
#define KEY4DOWN	(1<<3)
#define KEY1ON		(1<<4)
#define KEY2ON		(1<<5)
#define KEY3ON		(1<<6)
#define KEY4ON		(1<<7)

//******** Interrupt************************* 
//Timer
#define Enable_Interrupt()	(EA = 1);
#define Enable_TIMER0_Int()		(ET0 = 1);
#define Enable_TIMER1_Int()		(ET1 = 1);
#define StartTimer0()			(TR0 = 1);
#define StopTimer0()			(TR0 = 0);
#define StartTimer1()			(TR1 = 1);
#define StopTimer1()			(TR1 = 0);
// extra interrupt
#define Enabel_EX0INT()			(EX0 = 1);
#define Disable_EX0INT()		(EX0 &= ~1);
#define EX0M0					(1<<0)

// *********** Digital LEDs **************** //
#define SEG_a		(1<<0)
#define SEG_b		(1<<1)
#define SEG_c		(1<<2)
#define SEG_d		(1<<3)
#define SEG_e		(1<<4)
#define SEG_f		(1<<5)
#define SEG_g		(1<<6)
#define SEG_point	(1<<7)

#define CHAR_0	(SEG_a|SEG_b|SEG_c|SEG_d|SEG_e|SEG_f)
#define CHAR_1	(SEG_b|SEG_c)
#define CHAR_2	(SEG_a|SEG_b|SEG_d|SEG_e|SEG_g)
#define CHAR_3	(SEG_a|SEG_b|SEG_d|SEG_c|SEG_g)
#define CHAR_4	(SEG_b|SEG_c|SEG_f|SEG_g)
#define CHAR_5	(SEG_a|SEG_c|SEG_d|SEG_f|SEG_g)
#define CHAR_6	(SEG_a|SEG_c|SEG_d|SEG_e|SEG_f|SEG_g)
#define CHAR_7	(SEG_a|SEG_b|SEG_c)
#define CHAR_8	(SEG_a|SEG_b|SEG_c|SEG_d|SEG_e|SEG_f|SEG_g)
#define CHAR_9	(SEG_a|SEG_b|SEG_c|SEG_d|SEG_f|SEG_g)
#define CHAR_A	(SEG_a|SEG_b|SEG_c|SEG_e|SEG_f|SEG_g)
#define CHAR_B	(SEG_c|SEG_d|SEG_e|SEG_f|SEG_g)
#define CHAR_C	(SEG_a|SEG_d|SEG_e|SEG_f)
#define CHAR_D	(SEG_b|SEG_c|SEG_d|SEG_e|SEG_g)
#define CHAR_E	(SEG_a|SEG_d|SEG_e|SEG_f|SEG_g)
#define CHAR_F	(SEG_a|SEG_e|SEG_f|SEG_g)

//************** Eight LED ***************//
extern void DisplayLEDFlag(uchar flag);
extern void DisplayLED(uchar flag);


// Delay
extern uchar timer0_count;		// Use to Delay() count

extern void delay(uchar t);
extern void delayms(uchar ms);
extern void delay_nop(void);

extern uchar ISR_PWM_FREQ(void);
extern uchar ISR_PWM_PulseWidth(void);
extern void ISR_IRDA(void);
extern void ISR_KEY(void);
extern void ISR_Second(void);

extern void InitTimer(void);
extern void Beep(void);
extern void KeyCheck(void);
extern void KeyInit(void);
extern void Rate(uchar type);
extern void RateProcess(void);
extern void EnableIRDA(void);
extern void DisableIRDA(void);
extern void IrProcess(void);
extern void ISR_IRDA_PulseWidth(void);
extern void DisplayHex(uchar num, uchar addr);
extern void DisableLEDs(void);
extern void SecondProcess(void);
#endif