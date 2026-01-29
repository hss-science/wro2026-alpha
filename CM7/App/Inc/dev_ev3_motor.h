/*
 * dev_ev3_motor.h
 *
 *  Created on: Jan 21, 2026
 *      Author: hayat
 */

#ifndef SRC_DEV_EV3_MOTOR_H_
#define SRC_DEV_EV3_MOTOR_H_

#include <stdint.h>
#include "main.h"
#include "i2c.h"
#include "gpio.h"
#include "hrtim.h"

typedef enum{
	DEV_MOTOR_1 = 0,
	DEV_MOTOR_2 = 1,
	DEV_MOTOR_3 = 2,
	DEV_MOTOR_4 = 3,
	DEV_MOTOR_5 = 4,
	DEV_MOTOR_6 = 5,
} dev_motor_t;

void dev_motor_set_power(dev_motor_t port, double power);
void dev_motor_stop(dev_motor_t port, double power);
int32_t dev_motor_get_counts(dev_motor_t port, double power);

#endif /* SRC_DEV_EV3_MOTOR_H_ */
