#ifndef _TICK_H
#define _TICK_H
#include "typedef.h"

extern u32 jiffies;
extern u32 wake_jiffies;

void tick(void);
void setup_tick_timer(void);
void pm_idle(u8 sleep_tick);
#endif
