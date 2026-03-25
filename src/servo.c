#include "servo.h"


static int numMap(int value, int fromLow, int fromHigh, int toLow, int toHigh) {
    return (toHigh - toLow) * (value - fromLow) / (fromHigh - fromLow) + toLow;
}

int setServo1(int fd, int angle) {
    if (angle < 0) angle = 0;
    if (angle > 180) angle = 180;

    int pulse = numMap(angle, 0, 180, 500, 2500);
    printf("Setting servo 1 to angle %d with pulse %d\n", angle, pulse);
    return writeReg(fd, CMD_SERVO1, (uint16_t)pulse);
}
