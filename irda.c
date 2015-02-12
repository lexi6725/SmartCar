#include "config.h"

uchar irtime = 0;
uchar irdata[33];
uchar ircode[4];

void DisableIRDA(void)
{
	IT0 &= ~EX0M0;
	Disable_EX0INT();
}

void EnableIRDA(void)
{
	IT0 = EX0M0;
	Enabel_EX0INT();
}

void ISR_IRDA_PulseWidth(void)
{
	irtime++;
}

void ISR_IRDA(void) interrupt 0		// ext0
{
	static uchar i;
	static bit startflag;
	
	if (startflag)
	{
		if (irtime<63&&irtime>=33)
			i = 0;
		irdata[i] = irtime;
		irtime = 0;
		i++;
		if (i == 33)
		{
			SystemFlag |= bIRDA;
			i = 0;
		}
	}
	else
	{
		irtime = 0;
		startflag = 1;
	}
}

void IrDataProcess(void)
{
	uchar i, j, k=1;
	uchar cord, value;
	
	for (i = 0; i < 4; ++i)
	{
		for(j = 1; j <= 8; ++j)
		{
			cord = irdata[k];
			value = value>>1;
			if(cord >= 7)
				value |= (1<<7);
			k++;
		}
		ircode[i] = value;
		value = 0;
	}
	SystemFlag &= ~bIRDA;
	DisableIRDA();
}

uchar checkdata(void)
{
	if (ircode[0] == ~ircode[1] && ircode[2] == ~ircode[3] && ircode[0] == 0x00)
	{
		return 0;
	}
	
	return 1;
}

void IrCmdProcess(void)
{
	switch(ircode[2])
	{
		case 0x07:
			Rate(1);
			break;
		case 0x15:
			Rate(1);
			break;
	}
	
	ircode[0] = 0;
	ircode[1] = 0;
	ircode[2] = 0;
	ircode[3] = 0;
}

void IrProcess(void)
{
	IrDataProcess();
	
	if (checkdata())
		return;
	
	IrCmdProcess();
}