#include "mycar.h"

u32 jiffies, wake_jiffies;
static void schedule(void);
void tick(void)
{
	s8 i = sizeof(work_tbl)/sizeof(struct worker_tbl) - 1;
	s8 n;
	u32 next_timing = 0;

	kick_wdt();
	jiffies++;
	schedule();
}

void setup_tick_timer(void)
{
	init_timer(0, MODE1_16b, CTL_SW, OP_CLOCK);
	set_timer(0, 0xffff - MS_CLOCK);
	start_timer(0);
}

static void schedule(void)
{
	disable_irq();

	for (; i >= 0; i--) {
		/* woker has delay of beginning */
		if (jiffies < work_tbl[i].delay)
				next_timing = work_tbl[i].delay;
		else if (work_tbl[i].repeat)
			next_timing = jiffies + work_tbl[i].timing -
				((jiffies - work_tbl[i].delay) % work_tbl[i].timing);
		else /* overrun the delay and no repeat */
			continue;

		if (wake_jiffies > next_timing) {
			wake_jiffies = next_timing;
			n = i;
		}
	}

	if (wake_jiffies == jiffies)
		workqueue_add(work_tbl[n].w);

	enable_irq();
}
