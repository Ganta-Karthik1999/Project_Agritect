#include "common.h"
#include "command_parser.h"
#include "i2c_write.h"
#include "motor.h"
#include "servo.h"
#include "tcpserver.h"
#include "init.h"

int parsedata(const char* json_string) {
    int fd = initI2CDevice(I2C_DEVICE, MDEV_ADDR);
    if (fd < 0) {
        return -1;
    }

    if(strcmp(json_string, "w") == 0) {
        printf("Parsing command: %s\n", json_string);
        moveMotors(fd, 500, 500, 90);
    }
    else if(strcmp(json_string, "s") == 0){
        moveMotors(fd, -500, -500, 90);
    }
    else if(strcmp(json_string, "d") == 0){
        moveMotors(fd, 500 , 500, 45);
    }
    else if(strcmp(json_string, "a") == 0){
        moveMotors(fd, 500, 500, 135);
    }
    else if(strcmp(json_string, "q") == 0){
        stopMotors(fd);
    }
    return 0;
}

