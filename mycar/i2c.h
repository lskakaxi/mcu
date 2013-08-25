#ifndef _I2C_H
#define _I2C_H
#include "typedef.h"

void i2c_start();
void i2c_stop();
void i2c_send_ack(bit ack);
bit i2c_recv_ack();
void i2c_send_byte(u8 dat);
u8 i2c_recv_byte();
#endif
