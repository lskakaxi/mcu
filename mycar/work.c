#include "work.h"
#include "mycar.h"
#include "mpu6050.h"
#include <math.h>

#define WORK_LED P1_2
#define PIR_INPUT P1_6
#define WARN_CTL P1_7

/* thresold: 65535 / FSR / 4 */
#define ACCEL_FSR		4
#define ACCEL_THRES ((((u16)-1)/ACCEL_FSR)/4)

/* the whole detection status bits */
bit people_entering = 0;
bit people_nearby = 0;
bit need_warn = 0;
bit door_motion = 0;

void setup(void)
{
    /* enable pull-up resistor for input */
    PIR_INPUT = 1;
}

void led_high_worker(void)
{
    WORK_LED = 1;
}

void led_low_worker(void)
{
    WORK_LED = 0;
}

void serial_log(void)
{
    printf("%d,%d,%d,%d,%d,%d,\r\n",
            mpu6050_get_data(ACCEL_XOUT_H),
            mpu6050_get_data(ACCEL_YOUT_H),
            mpu6050_get_data(ACCEL_ZOUT_H),
            mpu6050_get_data(GYRO_XOUT_H),
            mpu6050_get_data(GYRO_YOUT_H),
            mpu6050_get_data(GYRO_ZOUT_H));
}

#define CALIBRA_TIMES 10
s16 accel_z_static = 0;
u8 cali_times = CALIBRA_TIMES;
s32 cali_sum = 0;
void calibration_accel_z(void)
{
	  /* had been calibrated */
    if (cali_times == 0)
		    return;
		
	  cali_sum += mpu6050_get_data(ACCEL_ZOUT_H);
		
		if (--cali_times == 0)
	      accel_z_static = cali_sum / CALIBRA_TIMES;
		printf("z static: %d, cali_sum: %d, thresold: %d\n",
		                  accel_z_static, cali_sum, ACCEL_THRES);
}

void detect_accel(void)
{
    s16 accel_z = mpu6050_get_data(ACCEL_ZOUT_H);
    if (!door_motion && abs(accel_z - accel_z_static) >= ACCEL_THRES) {
		    door_motion = 1;
			  printf("door motion, accel_z: %d\r\n", accel_z);
        if (people_nearby)
				    need_warn = 1;
    }
}

void detect_pir(void)
{
    if (!people_nearby && PIR_INPUT) {
			  printf("nearby\r\n");
		    people_nearby = 1;
		}
}

void warning(void)
{
    /* delay one tick high/low level */
    if (WARN_CTL == HIGH) {
		    WARN_CTL = LOW;
		    return;
		}
		/* if need warning, give one rising edge */
    if (need_warn) {
			  printf("warn once\r\n");
        WARN_CTL = HIGH;
			  need_warn = 0;
		}
}

void clear_all_status(void)
{
	  printf("clear_all\n\r");
    people_nearby = 0;
    need_warn = 0;
    door_motion = 0;
}

DEFINE_CODE_VAR(struct worker_entry, work_tbl[]) = {
	  { setup,                0,      0, 0, false},
    { led_low_worker,				100,	200, 1, true},
    { led_high_worker,			0,		200, 1, true},
//    { serial_log,									0,		10,  1, true},
    { detect_accel, 		  210, 		10,  1, true},
    { detect_pir, 			  210, 		10,  1, true},
    { warning, 					  210, 		50,  1, true},
    { calibration_accel_z,  5, 	  20,  1, true},
    { clear_all_status,   260,   100, 20, true},
};

DEFINE_CODE_VAR(u8,worker_num) = sizeof(work_tbl) / sizeof(struct worker_entry);
