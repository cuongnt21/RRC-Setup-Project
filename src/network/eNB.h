#ifndef ENB_H
#define ENB_H

#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include "baseDevice.h"
#include "RRCMessage.h"
#include "ownFunction.h"
using namespace std;

class eNB: public baseDevice{
protected:
    int listen_socket;

public:
    eNB();
    void listenSignal();
    void rrcMethod();
};

void* tListenSignal(void * arg);

#endif