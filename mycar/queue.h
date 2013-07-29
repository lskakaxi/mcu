#ifndef _WORKQUEUE_H
#define _WORKQUEUE_H

#include "mycar.h"

#ifndef QUEUELEN
#define QUEUELEN 6
#endif

void workqueue_init(void);
void workqueue_add(worker w);
void workqueue_run_one(void);
void workqueue_run(void);
#endif
