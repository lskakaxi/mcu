#include "mycar.h"

/* forbid called in interrupt handler */
void mdelay(u16 time)
{
	u16 delay_jiffies;
	delay_jiffies = jiffies + time;
	while (jiffies < delay_jiffies) {
		/* TODO: enter sleep mode */
		if (delay_jiffies - jiffies > 0xff)
			pm_idle(0xff);
		else
			pm_idle(delay_jiffies - jiffies);
	}
}
