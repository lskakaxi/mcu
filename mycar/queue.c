#include "queue.h"

worker workqueue[QUEUELEN];
/* high 4 bit: index of next to run worker in queue;
 * low 4 bit: index of added worker in queue;
 * limit to 16 worker
 */
struct {
	u8 next:4;
	u8 added:4;
} wq_index;

void workqueue_init(void)
{
	u8 i;
	for (i = 0; i < QUEUELEN; i++)
		workqueue[i] = (worker) 0;
	wq_index.added = 0xf;
	wq_index.next = 0;
}

void workqueue_add(worker w)
{
	disable_irq();
	wq_index.added++;
	if (wq_index.next == wq_index.added &&
			workqueue[wq_index.next]) {
		wq_index.added--;
		enable_irq();
		/* if queue is full, just ignore new worker */
		return;
	}
	workqueue[wq_index.added] = w;
	enable_irq();
}

void workqueue_run_one(void)
{
	worker w = workqueue[wq_index.next];
	if (w) {
		workqueue[wq_index.next++] = 0;
		w();
	}
}

void workqueue_run(void)
{
	while (1) {
		workqueue_run_one();
	}
}
