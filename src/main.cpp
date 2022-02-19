#include "UE.h"
#include "eNB.h"
#include "baseDevice.h"

using namespace std;

int main(){
    pthread_t thread1, thread2;
    UE *ueptr = new UE();
    eNB *enbptr = new eNB();
    
    pthread_create(&thread2, NULL, tRcConnectionEstablish, ueptr);
    pthread_create(&thread1, NULL, tListenSignal, enbptr);

    pthread_exit(NULL);
}