#include "baseDevice.h"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>

using namespace std;

#define PORT 5000

baseDevice::baseDevice(){
    com_socket = -1;

    memset(received_buffer, 0, sizeof(received_buffer));
    memset(sent_buffer, 0, sizeof(sent_buffer));
    memset(&eNB_addr, 0, sizeof(eNB_addr));
    
    eNB_addr.sin_family = AF_INET;
    eNB_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    eNB_addr.sin_port = htons(PORT);

    msg = "";
}