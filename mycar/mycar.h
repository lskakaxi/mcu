#include <8052.h>

/* interrupt */
#define disable_irq() EA=0
#define enable_irq() EA=1

/* timer */
#include "timer.h"

/* tick */
#include "tick.h"

/* wdt */
void kick_wdt(void);
void wdt_init(void);

void mdelay(u16 ms);

/* work */
#include "queue.h"
