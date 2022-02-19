#ifndef UE_H
#define UE_H

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include "baseDevice.h"
#include "RRCMessage.h"
#include "ownFunction.h"

using namespace std;

class UE: public baseDevice{
public:
    UE();
    void rrcConnectionEstablish();
};

void* tRcConnectionEstablish(void * arg);

#endif