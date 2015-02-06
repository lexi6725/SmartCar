#ifndef __CONFIG_H_
#define __CONFIG_H_
#include<reg51.h>
#include<intrins.h>

typedef unsigned char uchar;

extern uchar PWM;

extern void delay(uchar t);
extern void delayms(uchar ms);
extern uchar ISR_PWM_FREQ(void);
extern uchar ISR_PWM_PulseWidth(void);
extern void Beep(void);
extern void ISR_IRDA(void);
extern uchar ISR_KEY(void);
extern void InitTimer(void);

#endif