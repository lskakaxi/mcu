#include "mycar.h"
#include "work.h"

u32 jiffies, wake_jiffies = -1;
static void schedule(void);
void tick(void)
{
	kick_wdt();
	jiffies++;
	schedule();
	P1_7 = !P1_7;
}

void setup_tick_timer(void)
{
	init_timer(0, MODE1_16b, CTL_SW, OP_CLOCK);
	set_timer(0, 0xffff - MS_CLOCK);
	start_timer(0);
}

s8 last_worker;
static void schedule(void)
{
	s8 i = worker_num - 1;
	u32 next_timing = 0;
	const struct worker_entry *w_entry;

	/* NOTICE: we already in irq, no disable_irq needed */
	for ( ; i >= 0; i--) {
		w_entry = &work_tbl[i];
		/* woker has delay of beginning */
		if (jiffies < w_entry->delay)
			next_timing = w_entry->delay;
		else if (w_entry->repeat)
			next_timing = jiffies + w_entry->timing -
				((jiffies - w_entry->delay) % w_entry->timing);
		else /* overrun the delay and no repeat */
			continue;

		if (wake_jiffies > next_timing) {
			wake_jiffies = next_timing;
			last_worker = i;
		}
	}

	if (wake_jiffies == jiffies) {
		workqueue_add(last_worker);
		/* need re-calc wake_jiffies */
		wake_jiffies = -1;
	}

	pm_idle(wake_jiffies - jiffies);
}

void pm_idle(u8 sleep_tick)
{
	sleep_tick = sleep_tick;
}
