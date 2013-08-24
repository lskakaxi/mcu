#include "mycar.h"

/* set timer2 as Baud genterator.
 * set UART to mode 1, 8N1.
 * set baud as 9600
 */
void uart_init(void)
{
    SCON = 0x50;		/* uart in mode 1 (8 bit), REN=1 */
    T2CON &= 0xF0; /* EXEN2=0; TR2=0; C/T2#=0; CP/RL2#=0; */
    T2CON |= 0x30; /* RCLK = 1; TCLK=1; */
    TH2 = 0xFF; /* init value */
    TL2 = 0xFD; /* init value */
    RCAP2H = 0xFF; /* reload value, 115200 Bds at 11.059MHz */
    RCAP2L = 0xFD; /* reload value, 115200 Bds at 11.059MHz */
    /* don't use interrupt */
#if 0
    ES = 1; /* Enable serial interrupt */
    EA = 1; /* Enable global interrupt */
#endif
    TR2 = 1; /* Timer 2 run */
    TI = 1; /* send first char */
}

#ifndef _KEIL_C_
void putchar(char c) {
    while (!TI);
    TI = 0;
    SBUF = c;
}

char getchar() {
    char c;
    while (!RI);
    RI = 0;
    c = SBUF;
    return c;
}
#endif
