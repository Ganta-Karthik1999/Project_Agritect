#include "common.h"
#include "i2c_write.h"
#include "motor.h"
#include "init.h"
#include "servo.h"


int main() {

    int fd = initI2CDevice(I2C_DEVICE, MDEV_ADDR);
    if (fd < 0) {
        return -1;
    }

    printf(" The servo angle is %d \n",setServo1(fd, 90));

    moveMotors(fd, 1000, 1000, 90);
    sleep(1);
    moveMotors(fd, -500, -500, 90);
    sleep(1);
    stopMotors(fd);

    return 0;
}