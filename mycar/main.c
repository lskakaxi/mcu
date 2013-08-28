#include "mycar.h"

/* interrupt vector */
#ifndef _KEIL_C_
void timer0_isr(void) __interrupt (1) __using (1);
void timer1_isr(void) __interrupt (3) __using (2);
#endif

int main(void)
{
    uart_init();
    disable_irq();
    wdt_init();
    workqueue_init();
    enable_irq();
    setup_tick_timer();
    init_mpu6050();

    P1 = 0x55;
    /* loop here */
    workqueue_run();

    return 0;
}
