#ifndef _WORKQUEUE_H
#define _WORKQUEUE_H

#include "work.h"

#ifndef QUEUELEN
#define QUEUELEN 8
#endif

void workqueue_init(void);
void workqueue_add(u8 w);
void workqueue_run_one(void);
void workqueue_run(void);
#endif
