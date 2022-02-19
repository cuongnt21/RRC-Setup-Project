#ifndef BASEDEVICE_H
#define BASEDEVICE_H

#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
using namespace std;

#define PORT 5000

class baseDevice{
protected:
    int com_socket;
    struct sockaddr_in eNB_addr;
    unsigned char sent_buffer[1024], received_buffer[1024];
    string msg;

public:
    baseDevice();
};

#endif