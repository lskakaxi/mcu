#include "mycar.h"
#include "work.h"

u32 jiffies;
u8 expire_interval[WORK_MAX];
u8 expire_times[WORK_MAX];
bit first_time = 1;

static void schedule(void);
void tick(void)
{
    P1_7 = !P1_7;
    jiffies++;
    schedule();
}

u32 cpu_clock(void)
{
    u32 jiff;
    ET0 = 0;
    jiff = jiffies;
    ET0 = 1;
    return jiff;
}

void setup_tick_timer(void)
{
    init_timer(0, MODE1_16b, CTL_SW, OP_CLOCK);
    set_timer(0, 0xffff - TEN_MS_CLOCK);
    start_timer(0);
}

static void schedule(void)
{
    u8 i;
    if (first_time) {
        for (i = 0; i < worker_num; i++) {
            expire_interval[i] = work_tbl[i].delay;
            expire_times[i] = 1;
            if (!expire_interval[i]) {
                expire_interval[i] = work_tbl[i].interval;
                expire_times[i] = work_tbl[i].times;
            }
        }
        first_time = 0;
    } else {
        for (i = 0; i < worker_num; i++) {
            if (expire_interval[i] == 1 && expire_times[i] == 1) {
                workqueue_add(i);
                expire_interval[i] = work_tbl[i].interval;
                expire_times[i] = work_tbl[i].times;
            } else if (!expire_interval[i]) {
                expire_times[i]--;
                expire_interval[i] = work_tbl[i].interval;
            } else
                expire_interval[i]--;
        }
    }
}

void pm_idle(u8 sleep_tick)
{
    sleep_tick = sleep_tick;
}
