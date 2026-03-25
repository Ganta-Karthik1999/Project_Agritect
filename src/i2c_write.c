#include "i2c_write.h"

int writeReg(int fd, uint8_t cmd, uint16_t value) {
    uint8_t buf[3];
    buf[0] = cmd;
    buf[1] = (value >> 8) & 0xFF;   // MSB
    buf[2] = value & 0xFF;          // LSB

    // Python code writes 3 times for reliability
    for (int i = 0; i < 3; i++) {
        if (write(fd, buf, 3) != 3) {
            perror("I2C write failed");
            return -1;
        }
        usleep(1000); // 1 ms
    }
    return 0;

}