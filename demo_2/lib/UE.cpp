#include "UE.h"
#include "RRCMessage.h"
#include "ownFunction.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

using namespace std;

UE::UE(): baseDevice(){}

void UE::rrcConnectionEstablish(){
    // Create socket and connect
    com_socket = socket(AF_INET, SOCK_STREAM, 0);
    while(connect(com_socket, (struct sockaddr *)&eNB_addr, sizeof(eNB_addr))<0){
        cout << "UE: Connection failed due to port and ip problems" << endl;
    }
    cout << "UE connect successfully" << endl;
    
    // Create and encode the message
    RRCMessage_t *mess = new RRCMessage_t();
    mess = addData(mess);
    mess->messid = ID_rrcSetupRequest;
    char *p;
    p = Message_encode(mess);
    for(int i=0; i<24; i++){
        sent_buffer[i] = *(p+i);
        // printf("%X ", sent_buffer[i]);
    }
    // Send the message
    send(com_socket, sent_buffer, sizeof(sent_buffer), 0);
    cout << "UE: Send RRC Setup Request" << endl;
    
    // After that wait for the RRC connection setup
    read(com_socket, received_buffer, sizeof(received_buffer) - 1);
    cout << "UE: Receive packet" << endl;
    p = &received_buffer[0];

    RRCMessage_t *mess_recei = new RRCMessage_t();
    asn_dec_rval_t rval;

    rval = ber_decode(0, &asn_DEF_RRCMessage, (void **)&mess_recei, p, 1024);
    if(rval.code != RC_OK) {
        printf("UE: Broken encoding");
    }

    if (mess_recei->messid == ID_rrcSetup){
        mess = addData(mess);
        mess->messid = ID_rrcSetupComplete;
        p = Message_encode(mess);
        for(int i=0; i<24; i++){
            sent_buffer[i] = *(p+i);
            printf("%X ", sent_buffer[i]);
        }
        printf("\n");

        send(com_socket, sent_buffer, sizeof(sent_buffer), 0);
        cout << "UE: Send RRC Connection Setup Complete" << endl;
    }

    // Close
    close(com_socket);
}

void* tRcConnectionEstablish(void * arg){
    UE* p = (UE*) arg;
    p->rrcConnectionEstablish();
    return arg;
}
