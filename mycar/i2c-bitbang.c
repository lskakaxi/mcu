#include "mycar.h"
#include "typedef.h"
#include "delay.h"
#include "i2c.h"

//#define I2CSPEED 400
#if (I2CSPEED==400)
# define LDELAY(); delay3us();
#else
# define LDELAY(); delay10us();
#endif

void i2c_start();
void i2c_stop();
void i2c_send_ack(bit ack);
bit i2c_recv_ack();
void i2c_send_byte(u8 dat);
u8 i2c_recv_byte();

void i2c_start()
{
    SDA = 1;
    SCL = 1;
    LDELAY();
    SDA = 0;
    LDELAY();
    SCL = 0;
}

void i2c_stop()
{
    SDA = 0;
    SCL = 1;
    LDELAY();
    SDA = 1;
    LDELAY();
}

void i2c_send_ack(bit ack)
{
    SDA = ack;
    SCL = 1;
    LDELAY();
    SCL = 0;
    LDELAY();
}

bit i2c_recv_ack()
{
    SCL = 1;
    LDELAY();
    CY = SDA;
    SCL = 0;
    LDELAY();
    return CY;
}

void i2c_send_byte(u8 date)
{
    u8 i;
    for (i = 0; i < 8; i++) {
        date <<= 1;
        SDA = CY;
        SCL = 1;
        LDELAY();
        SCL = 0;
        LDELAY();
    }
    i2c_recv_ack();
}

u8 i2c_recv_byte()
{
    u8 i;
    u8 dat = 0;
    SDA = 1;    /* enable internal pull-up resistor for input */
    for (i = 0; i < 8; i++) {
        dat <<= 1;
        SCL = 1;
        LDELAY();
        dat |= SDA;
        SCL = 0;
        LDELAY();
    }
    return dat;
}
