#ifndef INIT_H
#define INIT_H

#include "common.h"


int initI2CDevice(const char *device, int addr){
    int fd = open(device, O_RDWR);
    if (fd < 0) {
        perror("Failed to open the i2c bus");
        return -1;
    }

    if (ioctl(fd, I2C_SLAVE, addr) < 0) {
        perror("Failed to acquire bus access and/or talk to slave");
        close(fd);
        return -1;
    }

    return fd;

}


#endif // INIT_H