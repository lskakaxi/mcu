#include "mycar.h"
#include "queue.h"
#include "work.h"

u8 workqueue[QUEUELEN];
/* 0 ~ 2 bit: in queue index
 * 3 ~ 5 bit: out queue index
 * limit to 8 worker
 */
struct {
	u8 in:3;
	u8 unused:1;
	u8 out:3;
} wq_index;

void workqueue_init(void)
{
	u8 i;
	for (i = 0; i < QUEUELEN; i++)
		workqueue[i] = 0xff;
	wq_index.in = 0x7;
	wq_index.out = 0;
}

void workqueue_add(u8 w)
{
	u8 in_index, out_index;

	wq_index.in++;
	in_index = wq_index.in;
	out_index = wq_index.out;
	if ((in_index == out_index) &&
		workqueue[out_index] != 0xff) {
		wq_index.in = in_index - 1;
		/* if queue is full, just ignore new worker */
		goto ret;
	}
	workqueue[in_index] = w;
ret:
}

void workqueue_run_one(void)
{
	__sbit int_flag;
	u8 out_index = wq_index.out;
	u8 w = workqueue[out_index];
	worker fn = work_tbl[w].w;

	if (w != 0xff) {
		if (out_index == 4)
			P1_6 = 0;

		irq_save(int_flag);
		workqueue[out_index] = 0xff;
		wq_index.out = out_index + 1;
		irq_restore(int_flag);
		fn();
		if (out_index == 4)
			P1_5 = 0;
	}
}

void workqueue_run(void)
{
	while (1) {
		workqueue_run_one();
	}
}
