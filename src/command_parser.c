#include "common.h"
#include "command_parser.h"
#include "i2c_write.h"
#include "motor.h"
#include "servo.h"
#include "tcpserver.h"

int parsedata(const char *json_string) {
    int fd = initI2CDevice(I2C_DEVICE, MDEV_ADDR);
    if (fd < 0) {
        return -1;
    }

    if(strcmp(json_string, "F") == 0) {
        printf("Parsing command: %s\n", json_string);
        moveMotors(fd, 1000, 1000, 90);
    }
    else if(strcmp(json_string, "B") == 0){
        moveMotors(fd, -1000, -1000, 90);
    }
    else if(strcmp(json_string, "L") == 0){
        moveMotors(fd, 1000, 1000, 45);
    }
    else if(strcmp(json_string, "R") == 0){
        moveMotors(fd, 1000, 1000, 135);
    }
    else if(strcmp(json_string, "S") == 0){
        stopMotors(fd);
    }
    return 0;
}

