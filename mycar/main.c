#include "mycar.h"

/* interrupt vector */
void timer0_isr(void) __interrupt (1) __using (1);
void timer1_isr(void) __interrupt (3) __using (2);

int main(void)
{
	disable_irq();
	wdt_init();
	workqueue_init();
	enable_irq();
	setup_tick_timer();

	P1_1 = 0;

	/* loop here */
	workqueue_run();

	return 0;
}


