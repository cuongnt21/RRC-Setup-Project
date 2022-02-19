#include "eNB.h"
#include "RRCMessage.h"
#include "ownFunction.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

using namespace std;

eNB::eNB(): baseDevice(), listen_socket(-1) {}

void eNB::listenSignal(){
    listen_socket = socket(AF_INET, SOCK_STREAM, 0);
    bind(listen_socket, (struct sockaddr*) &eNB_addr, sizeof(eNB_addr));
    listen(listen_socket, 10);
    // while(1){
    cout << "eNB: Start listening" << endl;
    
    // Accept the request and return a new socket
    com_socket = accept(listen_socket, (struct sockaddr*)NULL, NULL);
    
    // Listen
    // sleep(1);
    read(com_socket, received_buffer, sizeof(received_buffer));
    cout << "eNB: Receive packet" << endl;
    // for(int i=0; i<24; i++){
    //     printf("%X ", received_buffer[i]);
    // }
    
    // Decode
    char *p = &received_buffer[0];

    RRCMessage_t *mess_recei = new RRCMessage_t();
    asn_dec_rval_t rval;

    rval = ber_decode(0, &asn_DEF_RRCMessage, (void **)&mess_recei, p, 1024);
    if(rval.code != RC_OK) {
        cout << "eNB: Broken encoding" << endl;
        // return 0;
    }
    cout << "eNB: Decode successfully" << endl;

    if (mess_recei->messid == ID_rrcSetupRequest){
        rrcMethod();
    } else{
        cout << "eNB: Dont know that packet" << endl;
    }
    // Close
    close(com_socket);
    // }
}

void eNB::rrcMethod(){
     // Send the RRC connection setup
    RRCMessage_t *mess = new RRCMessage_t();
    mess = addData(mess);
    mess->messid = ID_rrcSetup;
    char *p;
    p = Message_encode(mess);
    for(int i=0; i<24; i++){
        sent_buffer[i] = *(p+i);
        // printf("%X ", sent_buffer[i]);
    }
    // printf("\n");
    send(com_socket, sent_buffer, sizeof(sent_buffer) - 1, 0);
    cout << "eNB: Send RRC Connection Setup" << endl;;

    // Finally,
    // for(int i=0; i<1024; i++){
    //     received_buffer[i] = 0;
    //     // printf("%X ", received_buffer[i]);
    // }

    // sleep(2);
    read(com_socket, received_buffer, sizeof(received_buffer));
    cout << "eNB: Receive packet successfully" << endl;

    
    for(int i=0; i<24; i++){
        printf("%X ", received_buffer[i]);
    }
    printf("\n");
    
    p = &received_buffer[0];
    
    RRCMessage_t *mess_recei = new RRCMessage_t();
    asn_dec_rval_t rval;

    rval = ber_decode(0, &asn_DEF_RRCMessage, (void **)&mess_recei, p, 1024);
    if(rval.code != RC_OK) {
        cout << "eNB: Broken encoding" << endl;
        // return 0;
    }
    
    if (mess_recei->messid == ID_rrcSetupComplete){
        cout << "eNB: RRC Setup Complete => EXIT" << endl;
    } else{
        cout << "eNB: Dont know that packet" << endl;
    }
    // Process
}

void* tListenSignal(void * arg){
    eNB* p = (eNB*) arg;
    p->listenSignal();
    return arg;
}