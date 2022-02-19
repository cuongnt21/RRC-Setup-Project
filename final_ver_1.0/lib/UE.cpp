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
    if((com_socket = socket(AF_INET, SOCK_STREAM, 0))< 0){
        cout << "UE: Socket not created" << endl;
        return;
    }

    while(connect(com_socket, (struct sockaddr *)&eNB_addr, sizeof(eNB_addr))<0){
        cout << "UE: Connection failed due to port and ip problems" << endl;
        sleep(1);
    }
    cout << "UE: Connect successfully" << endl;
    
    // Create and encode the message
    RRCMessage_t *mess = new RRCMessage_t();
    mess = addData(mess);
    mess->messid = ID_rrcSetupRequest;
    unsigned char *p;
    p = Message_encode(mess);
    for(int i=0; i<1024; i++){
        sent_buffer[i] = *(p+i);
    }

    // Send the message
    send(com_socket, sent_buffer, sizeof(sent_buffer), 0);
    cout << "UE: Send RRC Setup Request" << endl;
    
    // After that wait for the RRC connection setup
    sleep(1);
    read(com_socket, received_buffer, sizeof(received_buffer));
    cout << "UE: Receive packet" << endl;
    p = &received_buffer[0];

    RRCMessage_t *mess_recei = new RRCMessage_t();
    asn_dec_rval_t rval;

    rval = ber_decode(0, &asn_DEF_RRCMessage, (void **)&mess_recei, p, 1024);
    if(rval.code != RC_OK) {
        cout << "UE: Broken encoding" << endl;
        return;
    } else {
        cout << "UE: Decoding successfully" << endl;
        printMess(received_buffer, 24);
    }

    if (mess_recei->messid == ID_rrcSetup){
        mess = addData(mess);
        mess->messid = ID_rrcSetupComplete;
        p = Message_encode(mess);
        for(int i=0; i<1024; i++){
            sent_buffer[i] = *(p+i);
        }

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
