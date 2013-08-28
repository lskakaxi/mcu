#include "work.h"
#include "mycar.h"
#include "mpu6050.h"

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
    printf("%ld\n\r", mpu6050_get_data(0x3b));
    printf("%ld\n\r", mpu6050_get_data(0x3d));
    printf("%ld\n\r", mpu6050_get_data(0x3f));
    /*
    printf("%d,%d,%d,%d,%d,%d\r\n",
            mpu6050_get_data(ACCEL_XOUT_H),
            mpu6050_get_data(ACCEL_YOUT_H),
            mpu6050_get_data(ACCEL_ZOUT_H),
            mpu6050_get_data(GYRO_XOUT_H),
            mpu6050_get_data(GYRO_YOUT_H),
            mpu6050_get_data(GYRO_ZOUT_H));
	    */
}

DEFINE_CODE_VAR(struct worker_entry, work_tbl[]) = {
    { led_low_worker,	100,	200, 1, true},
    { led_high_worker,	0,	200, 1, true},
    { log,		0,	100,   1, true}
};

DEFINE_CODE_VAR(u8,worker_num) = sizeof(work_tbl) / sizeof(struct worker_entry);
