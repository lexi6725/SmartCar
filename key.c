#include "config.h"

uchar KeyFlag = 0;
uchar keytime[4];

uchar Bit2Int(uchar Bit)
{
	uchar i = 0;
	while(Bit != 0)
	{
		Bit /= 2;
		++i;
	}
	return i-1;
}

void ISR_KEY(void)
{
	uchar key = Bit2Int(KeyFlag&0x0f);
	
	if (key < 4)
	{
		if (keytime[key]++ >= KEYDELAYTIME)
		{
			KeyFlag |= (1<<key);
			keytime[key] = 0;
		}
		else
		{
			KeyFlag &= ~(1<<key);
			keytime[key] = 0;
		}
	}
}

void KeyCheck(void)
{
	uchar i;
	for (i = 0; i < 4; ++i)
	{
		if (P3&(1<<(i+4)))
			KeyFlag |= (1<<i);
	}
}