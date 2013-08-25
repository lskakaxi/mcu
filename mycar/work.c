#include "work.h"
#include "mycar.h"

void led_high_worker(void)
{
    P1_2 = 1;
}

void led_low_worker(void)
{
    P1_2 = 0;
}

void log(void)
{
    printf("os time:%ld\r\n", cpu_clock());
    printf("accel xout: %d\r\n", mpu6050_get_data(0x3B));
    printf("gyro xout: %d\r\n", mpu6050_get_data(0x43));
}

DEFINE_CODE_VAR(struct worker_entry, work_tbl[]) = {
    { led_low_worker,	100,	200, 1, true},
    { led_high_worker,	0,	200, 1, true},
    { log,	0,	100, 1, true}
};

DEFINE_CODE_VAR(u8,worker_num) = sizeof(work_tbl) / sizeof(struct worker_entry);
