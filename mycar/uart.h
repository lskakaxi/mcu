#ifndef _UART_H
#define _UART_H
#include "typedef.h"

#define BUF_SIZE	15

struct buf_index {
	u8 p;
	u8 v;
};

void uart_init(void);

#endif