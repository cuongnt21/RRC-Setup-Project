#include "UE.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

using namespace std;

UE::UE(): baseDevice(){}

void UE::rrcConnectionEstablish(){
    com_socket = socket(AF_INET, SOCK_STREAM, 0);

    while(connect(com_socket, (struct sockaddr *)&eNB_addr, sizeof(eNB_addr))<0){
        printf("UE: Connection failed due to port and ip problems\n");
    }

    // if(connect(com_socket, (struct sockaddr *)&eNB_addr, sizeof(eNB_addr))<0)
    // {
    //     printf("Connection failed due to port and ip problems\n");
    //     pthread_exit(NULL);
    // }
    
    // Send the RRC connection request
    msg = "RRC Connection ReQuest";
    strcpy(sent_buffer, &msg[0]);
    send(com_socket, sent_buffer, strlen(sent_buffer), 0);
    cout << "UE: Send RRC Connection ReQuest" << endl;
    
    // After that wait for the RRC connection setup
    read(com_socket, received_buffer, sizeof(received_buffer) - 1);
    cout << "UE: Receive packet " << received_buffer << endl;
    
    //Finally, 
    msg = "RRC Connection Setup Complete";
    strcpy(sent_buffer, &msg[0]);
    send(com_socket, sent_buffer, strlen(sent_buffer), 0);
    cout << "UE: Send RRC Connection Setup Complete" << endl;

    // Close
    close(com_socket);
}

void* tRcConnectionEstablish(void * arg){
    UE* p = (UE*) arg;
    p->rrcConnectionEstablish();
    return arg;
}
