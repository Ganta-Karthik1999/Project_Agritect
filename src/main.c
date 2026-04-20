#include "common.h"
#include "i2c_write.h"
#include "motor.h"
#include "init.h"
#include "servo.h"
#include "tcpserver.h"
#include "imu.h"


volatile sig_atomic_t running = 1;
volatile int active_connections = 0;
pthread_mutex_t count_mutex = PTHREAD_MUTEX_INITIALIZER;
int motor_fd = -1;

int main() {

    int sockfd =0, opt = 1;

    motor_fd = initI2CDevice(I2C_DEVICE, MDEV_ADDR);   // add this
    if (motor_fd < 0) {
        socket_close(&sockfd);
        return 1;
    }

    //  Initilizing the TCP Socket check the socket_utils.c file for full functionality
    if (socket_init(&sockfd, opt) != 0) {
        fprintf(stderr, "Socket init failed\n");
        return 1;
    }

    IMU_Init();

    while (running == 1)
    {
        //  Accepting the client connection 
        int clientfd = accept_client(sockfd);
        if (clientfd < 0) {
            fprintf(stderr, "Error accepting client connection\n");
            break;     
        
        }


        if(receive_commands(clientfd) < 0) {
            fprintf(stderr, "Error handling client connection\n");
            stopMotors(motor_fd);
            close(clientfd); 
            break;
        }
        if (start_imu_thread() != 0) {
            return -1;
        }

        sleep(1); // Sleep for a while before the next read
    }
    
    stopMotors(motor_fd);
    close(motor_fd);   
    // Closing the Socket
    socket_close(&sockfd);

    return 0;
}