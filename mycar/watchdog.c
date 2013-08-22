#include "mycar.h"

#ifdef _KEIL_C_
sfr WDTRST	= 0xa6;
#else
__sfr __at 0xa6 WDTRST;
#endif

void kick_wdt(void)
{
	WDTRST = 0x1e;
	WDTRST = 0xe1;
}

void wdt_init(void)
{
	kick_wdt();
}
