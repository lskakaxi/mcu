#include "mycar.h"
#include <stdio.h>

/* interrupt vector */
#ifndef _KEIL_C_
void timer0_isr(void) __interrupt (1) __using (1);
void timer1_isr(void) __interrupt (3) __using (2);
#endif

int main(void)
{
	disable_irq();
	wdt_init();
	workqueue_init();
	enable_irq();
	setup_tick_timer();
	uart_init();

	/* loop here */
	workqueue_run();

	return 0;
}


