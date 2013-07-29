#include "mycar.h"

__code struct worker_tbl work_tbl[] = {
	{ led_low_worker,	500,	1000, true},
	{ led_high_worker,	0,	1000, true}
};

