#include "i2c.h"
#include "mpu6050.h"

void write_reg(u8 reg, u8 dat)
{
    i2c_start();
    i2c_send_byte(SlaveAddr);
    i2c_send_byte(reg);
    i2c_send_byte(dat);
    i2c_stop();
}

u8 read_reg(u8 reg)
{
    u8 dat;
    i2c_start();
    i2c_send_byte(SlaveAddr);
    i2c_send_byte(reg);
    i2c_start();
    i2c_send_byte(SlaveAddr+1);
    dat = i2c_recv_byte();
    i2c_send_ack(1);
    i2c_stop();
    return dat;
}

u16 mpu6050_get_data(u8 reg)
{
    u8 high, low;
    kick_wdt();
    high = read_reg(reg);
    low = read_reg(reg + 1);
    return (high << 8) | low;
}

void init_mpu6050(void)
{
    write_reg(PWR_MGMT_1, 0x00);
    write_reg(SMPLRT_DIV, 0x07);
    write_reg(CONFIG, 0x06);
    write_reg(GYRO_CONFIG, 0x18);
    write_reg(ACCEL_CONFIG, 0x01);
}
