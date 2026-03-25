#ifndef INIT_H
#define INIT_H


#define I2C_DEVICE "/dev/i2c-1"
#define MDEV_ADDR  0x18


int initI2CDevice(const char *device, int addr);



#endif // INIT_H