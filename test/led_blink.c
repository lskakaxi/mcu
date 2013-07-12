#include <8052.h>

#define LED0 P0_0
#define LED1 P1_0
#define LED2 P2_0
#define LEDS P1

void delay(unsigned int t)
{
	while (t--);
}

void main()
{
	int right = 0;
	LEDS = 0xfe;
	while (1) {
		if (right) {
			LEDS >>= 1;
			LEDS |= 0x80;
		} else {
			LEDS <<= 1;
			LEDS |= 1;
		}
		if (LEDS == 0x7f)
			right = 1;;
		if (LEDS == 0xfe)
			right = 0;;
		delay(200000);
	}
}
