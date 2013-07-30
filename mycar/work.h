#ifndef _WORK_H
#define _WORK_H
#include "typedef.h"

typedef void (*worker)(void);

struct worker_entry {
	worker w;
	u32 delay;
	u32 timing;
	bool repeat;
};

extern __code struct worker_entry work_tbl[];
extern __code u8 worker_num;
#endif
