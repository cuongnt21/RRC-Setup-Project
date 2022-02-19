#include "eNB.h"

using namespace std;

eNB::eNB(): baseDevice(), listen_socket(-1) {}

void eNB::listenSignal(){
    if((listen_socket = socket(AF_INET, SOCK_STREAM, 0))< 0){
        cout << "eNB: Socket not created" << endl;
        return;
    }

    if (bind(listen_socket, (struct sockaddr*) &eNB_addr, sizeof(eNB_addr))<0){
        cout << "eNB: Bind failed" << endl;
        return;
    }

    if (listen(listen_socket, 10) < 0){
        cout << "eNB: Listen failed" << endl;
        return;
    }

    // while(1){
    cout << "eNB: Start listening" << endl;
    
    // Accept the request and return a new socket
    while(1){
        com_socket = accept(listen_socket, (struct sockaddr*)NULL, NULL);
        if (com_socket != -1){
            break;
        }
    }
    
    // Listen
    read(com_socket, received_buffer, sizeof(received_buffer));
    cout << "eNB: Receive packet" << endl;
    
    // Decode
    unsigned char *p = &received_buffer[0];
    RRCMessage_t *mess_rcv = new RRCMessage_t();
    asn_dec_rval_t rval;
    rval = ber_decode(0, &asn_DEF_RRCMessage, (void **)&mess_rcv, p, 1024);
    if(rval.code != RC_OK) {
        cout << "eNB: Broken encoding" << endl;
        return;
    } else {
        cout << "eNB: Decoding successfully" << endl;
        printMess(received_buffer, 24);
    }

    // Check the messid
    if (mess_rcv->messid == ID_rrcSetupRequest){
        rrcMethod();
    } else{
        cout << "eNB: Dont know that packet" << endl;
    }
    // Close
    delete mess_rcv;
    close(com_socket);
}

void eNB::rrcMethod(){
     // Send the RRC connection setup
    RRCMessage_t *mess = new RRCMessage_t();
    unsigned char *p;
    mess = addData(mess);
    mess->messid = ID_rrcSetup;
    p = Message_encode(mess);
    for(int i=0; i<1024; i++){
        sent_buffer[i] = *(p+i);
    }
    free(p);
    delete mess;
    mess = nullptr;

    send(com_socket, sent_buffer, sizeof(sent_buffer), 0);
    cout << "eNB: Send RRC Connection Setup" << endl;;

    // Finally'
    // sleep(2);
    read(com_socket, received_buffer, sizeof(received_buffer));
    cout << "eNB: Receive packet successfully" << endl;   
    p = &received_buffer[0];
    
    RRCMessage_t *mess_rcv = new RRCMessage_t();
    asn_dec_rval_t rval;

    rval = ber_decode(0, &asn_DEF_RRCMessage, (void **)&mess_rcv, p, 1024);
    if(rval.code != RC_OK) {
        cout << "eNB: Broken encoding" << endl;
        return;
    } else {
        cout << "eNB: Decoding successfully" << endl;
        printMess(received_buffer, 24);
    }
    
    if (mess_rcv->messid == ID_rrcSetupComplete){
        cout << "eNB: RRC Setup Complete => EXIT()" << endl;
    } else{
        cout << "eNB: Dont know that packet" << endl;
    }
    delete mess_rcv;


    return;
    // Process
}

void* tListenSignal(void * arg){
    eNB* p = (eNB*) arg;
    p->listenSignal();
    return arg;
}