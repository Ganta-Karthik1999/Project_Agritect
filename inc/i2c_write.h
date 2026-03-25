#ifndef I2C_WRITE_H
#define I2C_WRITE_H

#include "common.h"

int writeReg(int fd, uint8_t cmd, uint16_t value);

#endif // I2C_WRITE_H