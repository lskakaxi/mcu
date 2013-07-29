#ifndef _TIMER_H
#define _TIMER_H
#include "typedef.h" 

#define OSC 11052000
#ifndef OSC
# define OSC 12000000
#endif

#define CLOCK (1.0f/(OSC/12.0f))
#define MS_CLOCK ((u32)((1.0f/1000.0f)/CLOCK+0.5))
#define MODE0_MAX_MS (0x1fff/MS_CLOCK)
#define MODE1_MAX_MS (0xffff/MS_CLOCK)
#define MODE2_MAX_MS (0xff/MS_CLOCK)
#define MODE3_MAX_MS (0xff/MS_CLOCK)

#define TIMER0_CB_HOOK tick()

typedef enum {
	/*
	 * Mode 0: 8-bit timer/counter (TH0) with 5-bit prescaler (TL0).
	 * Mode 1: 16-bit timer/counter.
	 * Mode 2: 8-bit auto-reload timer/counter (TL0). Reloaded from TH0 at overflow.
	 * Mode 3(timer0): TL0 is an 8-bit timer/counter.
	 *         TH0 is an 8-bit timer using timer 1’s TR0 and TF0 bits.
	 * Mode 3(timer1): timer 1 halted. Retains count.
	 */
	MODE0_13b = 0,
	MODE1_16b,
	MODE2_8b_AUTOLOAD,
	MODE3_8b_DOUBLE,
	MODE3_8b_HALT = MODE3_8b_DOUBLE
} timer_mode;

typedef enum {
	/* GATEx=0, TRx bit start the timer */
	CTL_SW = 0,
	/* GATEx=1, TRx bit and INTx# high start timer */
	CTL_INT
} control_mode;

typedef enum {
	/* C/Tx#=0, timer count divided-down clock */
	OP_CLOCK = 0,
	/* C/Tx#=1, timer count negative transitions on external pin Tx */
	OP_PULSE
} operation_mode;

void init_timer(u8 a, timer_mode b, control_mode c, operation_mode d);
void set_timer(u8, u16);
void start_timer(u8);
u16 stop_timer(u8);
void start_counter(u8);
u16 stop_counter(u8);
#endif
