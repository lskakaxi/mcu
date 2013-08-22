/* Timer 0,1 API for 89S52
 * Author: shuox.liu@gmail.com
 * Date: 2013-07-27 02:50
 *
 * When timer0 in mode3, only support one 8-bit timer
 */
#include "mycar.h"
#include "timer.h"

u16 timer0_value;
u16 timer1_value;
void init_timer(u8 timer,
		timer_mode t_mode,
		control_mode c_mode,
		operation_mode o_mode)
{
	u8 reg;

	reg = TMOD;
	switch (timer) {
	default:
	case 0:
		TR0 = 0;
		if (t_mode & 1) reg |= T0_M0;
		else reg &= ~T0_M0;

		if (t_mode >> 1) reg |= T0_M1;
		else reg &= ~T0_M1;
		
		if (o_mode)	reg |= T0_CT;
		else reg &= ~T0_CT;

		if (c_mode) reg |= T0_GATE;
		else reg &= ~T0_GATE;

		TH0 = TL0 = 0;
		break;
	case 1:
		TR1 = 0;
		if (t_mode & 1) reg |= T1_M0;
		else reg &= ~T1_M0;
		
		if (t_mode >> 1) reg |= T1_M1;
		else reg &= ~T1_M1;

		if (o_mode) reg |= T1_CT;
		else reg &= ~T1_CT;
		
		if (c_mode) reg |= T1_GATE;
		else reg &= ~T1_GATE;

		TH1 = TL1 = 0;
		break;
	}
	TMOD = reg;
}

void set_timer(u8 timer, u16 count)
{
	timer_mode mode;

	switch (timer) {
	default:
	case 0:
		mode = TMOD & (T0_M1 | T0_M0);
		switch (mode) {
		case MODE0_13b:
			TL0 = count & 0x1f;
			TH0 = count >> 5;
			break;
		default:
		case MODE1_16b:
			TH0 = count >> 8;
		case MODE2_8b_AUTOLOAD:
		case MODE3_8b_DOUBLE:
			TL0 = count & 0xff;
		}
		timer0_value = count;
		break;
	case 1:
		mode = TMOD & (T1_M1 | T1_M0);
		switch (mode) {
		case MODE0_13b:
			TL1 = count & 0x1f;
			TH1 = count >> 5;
			break;
		default:
		case MODE1_16b:
			TH1 = count >> 8;
		case MODE2_8b_AUTOLOAD:
			TL1 = count & 0xff;
		}
		timer1_value = count;
		break;
	}
}

void start_timer(u8 timer)
{
	timer_mode mode;

	switch (timer) {
	default:
	case 0:
		ET0 = 1; TR0 = 1; break;
	case 1:
		/* timer0.1 use timer1's TR,.. */
		mode = TMOD & (T0_M1 | T0_M0);
		if (mode == MODE3_8b_DOUBLE) {
			/* default use mode 1 */
			TMOD = (TMOD & ~T1_M1) | T1_M0;
		} else {
			ET1 = 1;
			TR1 = 1;
		}

		break;
	}
}

u16 stop_timer(u8 timer)
{
	timer_mode mode;
	u16 ret;

	switch (timer) {
	default:
	case 0:
		TR0 = 0;
		mode = TMOD & (T0_M1 | T0_M0);
		switch (mode) {
		case MODE0_13b:
			ret = (u16)((u8)TH0 << 5) + TL0 & 0x1f;
			break;
		default:
		case MODE1_16b:
			ret = (u16)(TH0 << 8) + TL0;
			break;
		case MODE2_8b_AUTOLOAD:
			ret = (u16)TL0 & 0xff;
			break;
		case MODE3_8b_DOUBLE:
			ret = (u16)TL0 & 0xff;
			break;
		}
		break;
	case 1:
		mode = TMOD & (T0_M1 | T0_M0);
		if (mode == MODE3_8b_DOUBLE) {
			TMOD = (TMOD | T1_M1 | T1_M0);
			return 0;
		}
		TR1 = 0;
		mode = TMOD & (T1_M1 | T1_M0);
		switch (mode) {
		case MODE0_13b:
			ret = (u16)((u8)TH1 << 5) + TL1 & 0x1f;
			break;
		default:
		case MODE1_16b:
			ret = (u16)(TH1 << 8) + TL1;
			break;
		case MODE2_8b_AUTOLOAD:
			ret = (u16)TL1 & 0xff;
			break;
		case MODE3_8b_HALT:
			ret = 0;
			break;
		}

		ret = (u16)(TH1 << 8) + TL1;
		break;
	}

	return ret;
}

void start_counter(u8 timer)
{
	init_timer(timer, MODE1_16b, CTL_SW, OP_PULSE);
	start_timer(timer);
}

u16 stop_counter(u8 timer)
{
	return stop_timer(timer);
}

#ifdef _KEIL_C_
void timer0_isr(void) interrupt 1
#else
void timer0_isr(void) __interrupt (1)
#endif
{
	/* enable timer0 firstly */
	TR0 = 0;
	set_timer(0, timer0_value);
	TR0 = 1;
	/* add hook time consume in this timer period */
#ifdef TIMER0_CB_HOOK
	TIMER0_CB_HOOK;
#endif
}

#ifdef _KEIL_C_
void timer1_isr(void) interrupt 3 using 2
#else
void timer1_isr(void) __interrupt (3) __using (2)
#endif
{
	/* enable timer1 firstly */
	TR1 = 0;
	set_timer(1, timer1_value);
	TR1 = 1;
	/* add hook time consume in this timer period */
#ifdef TIMER1_CB_HOOK
	TIMER1_CB_HOOK;
#endif
}

