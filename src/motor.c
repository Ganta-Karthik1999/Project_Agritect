#include "motor.h"


int moveMotors(int fd, int left_pwm, int right_pwm, int steering_angle) {
    if (setServo1(fd, steering_angle) < 0)
        return -1;

    if (left_pwm > 0) {
        if (writeReg(fd, CMD_DIR2, 1) < 0) return -1;
        if (writeReg(fd, CMD_PWM2, (uint16_t)left_pwm) < 0) return -1;
    } else {
        if (writeReg(fd, CMD_DIR2, 0) < 0) return -1;
        if (writeReg(fd, CMD_PWM2, (uint16_t)abs(left_pwm)) < 0) return -1;
    }

    if (right_pwm > 0) {
        if (writeReg(fd, CMD_DIR1, 1) < 0) return -1;
        if (writeReg(fd, CMD_PWM1, (uint16_t)right_pwm) < 0) return -1;
    } else {
        if (writeReg(fd, CMD_DIR1, 0) < 0) return -1;
        if (writeReg(fd, CMD_PWM1, (uint16_t)abs(right_pwm)) < 0) return -1;
    }

    return 0;
}


int stopMotors(int fd) {
    if (writeReg(fd, CMD_PWM1, 0) < 0) return -1;
    if (writeReg(fd, CMD_PWM2, 0) < 0) return -1;
    return 0;
}



