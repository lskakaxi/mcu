#include "mycar.h"

__sfr __at 0xa6 WDTRST;

void kick_wdt(void)
{
	WDTRST = 0x1e;
	WDTRST = 0xe1;
}

void wdt_init(void)
{
	kick_wdt();
}
