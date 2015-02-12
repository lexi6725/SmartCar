#include "config.h"

uchar KeyFlag = 0;
uchar keytime[4];


/*
 * Name: ISR_KEY(void)
 * Function: fixed time to check Key push down flag
 * Argu: void
 * Ret: void
 */
void ISR_KEY(void)
{
	uchar key;
	
	for (key = 0; key < KEYNUM; ++key)
	{
		if (KeyFlag&(1<<(4+key)))
		{
			if (keytime[key]++ >= KEYDELAYTIME)
			{
				KeyFlag |= (1<<(4+key));
				keytime[key] = 0;
			}
		}
		else
		{
			keytime[key] = 0;
		}
	}
}

/*
 * name: KeyCheck()
 * Function: check Key S2-S5 is push down ... 
 * Argu: void
 * Return: void
 */
void KeyCheck(void)
{
	uchar i;
	
	for (i = 0; i < KEYNUM; ++i)
	{
		// MAP: S2: P3^4, S3:P3^5, S4:P3^6, S5:P3^7
		if (P3&(1<<(i+4)))		
			KeyFlag |= (1<<i);	// set flag key bit
		else
			KeyFlag &= ~(1<<i);
		
	}
}