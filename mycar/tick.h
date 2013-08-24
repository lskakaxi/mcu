#ifndef _TICK_H
#define _TICK_H
#include "typedef.h"

extern u32 jiffies;

void tick(void);
u32 cpu_clock(void);
void setup_tick_timer(void);
void pm_idle(u8 sleep_tick);
#endif
