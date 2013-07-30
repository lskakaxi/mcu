#include "work.h"
#include "mycar.h"

void led_high_worker(void)
{
	P1_2 = 1;
}

void led_low_worker(void)
{
	P1_2 = 0;
}
__code struct worker_entry work_tbl[] = {
	{ led_low_worker,	5,	10, true},
	{ led_high_worker,	0,	10, true}
};

__code u8 worker_num = sizeof(work_tbl) / sizeof(struct worker_entry);
