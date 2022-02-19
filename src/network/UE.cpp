#include "UE.h"

using namespace std;

UE::UE(): baseDevice(){}

void UE::rrcConnectionEstablish(){
    RRCMessage_t *mess_send = new RRCMessage_t();
    RRCMessage_t *mess_rcv = new RRCMessage_t();
    unsigned char *p = nullptr;
    asn_dec_rval_t rval;

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
    mess_send = addData(mess_send);
    mess_send->messid = ID_rrcSetupRequest;
    p = Message_encode(mess_send);
    for(int i=0; i<1024; i++){
        sent_buffer[i] = *(p+i);
    }
    free(p);

    // Send the message
    send(com_socket, sent_buffer, sizeof(sent_buffer), 0);
    cout << "UE: Send RRC Setup Request" << endl;
    
    // After that wait for the RRC connection setup
    sleep(1);
    read(com_socket, received_buffer, sizeof(received_buffer));
    cout << "UE: Receive packet" << endl;
    p = &received_buffer[0];

    rval = ber_decode(0, &asn_DEF_RRCMessage, (void **)&mess_rcv, p, 1024);
    if(rval.code != RC_OK) {
        cout << "UE: Broken encoding" << endl;
        return;
    } else {
        cout << "UE: Decoding successfully" << endl;
        printMess(received_buffer, 24);
    }

    if (mess_rcv->messid == ID_rrcSetup){
        mess_send = addData(mess_send);
        mess_send->messid = ID_rrcSetupComplete;
        p = Message_encode(mess_send);
        for(int i=0; i<1024; i++){
            sent_buffer[i] = *(p+i);
        }
        free(p);

        send(com_socket, sent_buffer, sizeof(sent_buffer), 0);
        cout << "UE: Send RRC Connection Setup Complete" << endl;
    }

    // Close
    delete mess_send;
    delete mess_rcv;

    close(com_socket);
}

void* tRcConnectionEstablish(void * arg){
    UE* p = (UE*) arg;
    p->rrcConnectionEstablish();
    return arg;
}
