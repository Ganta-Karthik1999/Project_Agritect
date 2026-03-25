#ifndef SERVO_H
#define SERVO_H
#include "common.h"
#include "i2c_write.h"

#define CMD_SERVO1 0

int setServo1(int fd, int angle);

// numMap is an internal helper; no external prototype needed.

#endif // SERVO_H