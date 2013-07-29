#ifndef _TICK_H
#define _TICK_H
#include "typedef.h"

typedef void worker(void);

struct worker_tbl {
	worker w;
	u16 delay;
	u16 timing;
	bool repeat;
};

extern u32 jiffies;
extern u32 wake_jiffies;
extern struct worker_tbl work_tbl;

void tick(void);
void setup_tick_timer(void);
#endif
