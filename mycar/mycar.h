#ifdef _KEIL_C_
# include <REGX51.H>
#else
# include <8052.h>
#endif

/* interrupt */
#define disable_irq() EA=0
#define enable_irq() EA=1
#define irq_save(f) do { f = EA; EA = 0; } while(0)
#define irq_restore(f) do { EA = f; } while(0)

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
