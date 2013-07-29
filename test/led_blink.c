#include <8052.h>

#define LED0 P0_0
#define LED1 P1_0
#define LED2 P2_0
#define LEDS P1

unsigned char leds;
unsigned char count;
void delay(unsigned long t)
{
	while (t--);
}

void warning(void)
{
	if (count != 100)
		return;
	LEDS = 0x00;
	delay(30000);
	LEDS = 0xff;
	delay(30000);
	LEDS = 0x00;
	delay(30000);
	count = 0;
}

void timer1_hanlder(void) __interrupt (1) __using (1)
{
	count++;
	warning();
	LEDS = leds;
	TR0 = 0;
	TH0 = 0xd8;
	TL0 = 0xef;
	TR0 = 1;
}

void init_timer0()
{
	TR0 = 0;
	TMOD = (TMOD & 0xf0) | 1;
	TH0 = 0xd8;
	TL0 = 0xef;
	ET0 = 1;
	EA = 1;
	TR0 = 1;
}

void main()
{
	int right = 0;
	LEDS = 0xfe;
	init_timer0();
	while (1) {
		leds = LEDS;
		if (right) {
			leds >>= 1;
			leds |= 0x80;
		} else {
			leds <<= 1;
			leds |= 1;
		}
		LEDS = leds;
		if (leds == 0x7f)
			right = 1;;
		if (leds == 0xfe)
			right = 0;;
		delay(30000);
	}
}
