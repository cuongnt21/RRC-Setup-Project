#include "eNB.h"
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
        read(com_socket, received_buffer, sizeof(received_buffer) - 1);
        cout << "eNB: Receive packet " << received_buffer << endl;
        if (strcmp(received_buffer, "RRC Connection ReQuest") == 0){
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
    msg = "RRC Connection Setup";
    strcpy(sent_buffer, &msg[0]);
    send(com_socket, sent_buffer, sizeof(sent_buffer) - 1, 0);
    cout << "eNB: Send RRC Connection Setup" << endl;

    // Finally, 
    read(com_socket, received_buffer, sizeof(received_buffer) - 1);
    cout << "eNB: Receive packet " << received_buffer << endl;
}

void* tListenSignal(void * arg){
    eNB* p = (eNB*) arg;
    p->listenSignal();
    return arg;
}