#ifndef UE_H
#define UE_H

#include <iostream>
#include <netinet/in.h>
#include "baseDevice.h"
using namespace std;

class UE: public baseDevice{
public:
    UE();
    void rrcConnectionEstablish();
};

void* tRcConnectionEstablish(void * arg);

#endif