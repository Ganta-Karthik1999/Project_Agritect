#ifndef TCPSERVER_H
#define TCPSERVER_H

#include "common.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <errno.h>
#include <pthread.h>
#include <string.h>

extern volatile sig_atomic_t running;
extern volatile int active_connections;
extern pthread_mutex_t count_mutex;

void handle_sigint(int sig);


/**
 * @brief Initializes the TCP server socket and required system resources.
 * **/
int socket_init(int *sockfd, int opt);

/**
 *  @brief Accepts the client connection.
 * 
 * **/
int accept_client(int sockfd);


/**
 * @brief Thread routine to handle a single client connection.
 * 
 * **/
void *handle_client(void *arg);

/**
 * @brief Cleanly shuts down the server and releases allocated resources.
 * 
 * **/
void socket_close();


int receive_commands(int clientfd);


#endif // TCPSERVER_H

