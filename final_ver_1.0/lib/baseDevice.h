#ifndef BASEDEVICE_H
#define BASEDEVICE_H

#include <iostream>
#include <netinet/in.h>
using namespace std;

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