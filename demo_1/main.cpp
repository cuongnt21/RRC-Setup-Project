#include "UE.h"
#include "eNB.h"
#include "baseDevice.h"

using namespace std;

int main(){
    pthread_t thread1, thread2;
    baseDevice *p;

    p = new UE();
    pthread_create(&thread2, NULL, tRcConnectionEstablish, p);
    p = new eNB();
    pthread_create(&thread1, NULL, tListenSignal, p);

    pthread_exit(NULL);
}