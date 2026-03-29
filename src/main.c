#include "common.h"
#include "i2c_write.h"
#include "motor.h"
#include "init.h"
#include "servo.h"
#include "tcpserver.h"



volatile sig_atomic_t running = 1;
volatile int active_connections = 0;
pthread_mutex_t count_mutex = PTHREAD_MUTEX_INITIALIZER;


int main() {

    int sockfd =0, opt = 1;

    //  Initilazing the TCP Socket check the socket_utils.c file for full functionality
    if (socket_init(&sockfd, opt) != 0) {
        fprintf(stderr, "Socket init failed\n");
        return 1;
    }


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
            break;
        }

        

    }
    

    // Closing the Socket
    socket_close(&sockfd);

    return 0;
}