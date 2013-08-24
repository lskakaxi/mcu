#ifndef _WORK_H
#define _WORK_H
#include "typedef.h"

#define WORK_MAX	8
typedef void (*worker)(void);

struct worker_entry {
    worker w;		/* callback */
    u8 delay;		/* delay at beginning */
    u8 interval;/* timeing = interval * times */
    u8 times;
    bool repeat;/* once or repeat */
};

DECLARE_CODE_VAR(struct worker_entry, work_tbl[]);
DECLARE_CODE_VAR(u8, worker_num);

#endif
