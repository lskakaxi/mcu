#ifdef _KEIL_C_
# include <REGX52.H>
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

/* uart */
#include "uart.h"

/* wdt */
void kick_wdt(void);
void wdt_init(void);

/* work */
#include "queue.h"

#include <stdio.h>

/* for i2c */
#define SDA P1_1
#define SCL P1_0

void init_mpu6050(void);
u16 mpu6050_get_data(u8 reg);
