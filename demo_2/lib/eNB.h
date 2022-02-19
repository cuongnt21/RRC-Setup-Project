#ifndef ENB_H
#define ENB_H

#include <iostream>
#include <netinet/in.h>
#include "baseDevice.h"
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