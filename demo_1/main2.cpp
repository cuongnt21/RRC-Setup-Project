// just for testing
#include <iostream>
#include "UE.h"
#include "eNB.h"
#include <unistd.h>
#include <string.h>

using namespace std;

#define PORT 5000

int main(){
    UE myUE;
    eNB myeNB;
    myUE.rrcConnectionEstablish();
    // myeNB.listenSignal();
    
    
    
    // char buffer[1024];
    // string t = "1200 Hello World";

    // memset(buffer, 0, sizeof(buffer));
    // strcpy(buffer, &t[0]);
    // cout << buffer << endl;
    // cout << strcmp(buffer, "1200 Hello World") << endl;
    return 0;
}