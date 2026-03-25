#ifndef MOTOR_H
#define MOTOR_H

#include "common.h"
#include "i2c_write.h"
#include "servo.h"

#define CMD_PWM1   4
#define CMD_PWM2   5
#define CMD_DIR1   6
#define CMD_DIR2   7


int moveMotors(int fd, int left_pwm, int right_pwm, int steering_angle);

int stopMotors(int fd);


#endif // MOTOR_H