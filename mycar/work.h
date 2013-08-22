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

DECLARE_CODE_VAR(struct worker_entry, work_tbl[]);
DECLARE_CODE_VAR(u8, worker_num);

#endif
