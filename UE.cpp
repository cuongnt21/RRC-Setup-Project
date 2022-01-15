#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include <iostream>

#define PORT 5000
using namespace std;

int RRC(){
    // Declare parameters
    int com_socket = -1;
    struct sockaddr_in eNB_addr;

    char sent_buffer[1024], received_buffer[1024];
    string msg;
    // strcpy(sent_buffer, &msg[0]);

    memset(received_buffer, 0, sizeof(received_buffer));
    memset(sent_buffer, 0, sizeof(sent_buffer));
    memset(&eNB_addr, 0, sizeof(eNB_addr));

    com_socket = socket(AF_INET, SOCK_STREAM, 0);
    eNB_addr.sin_family = AF_INET;
    eNB_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    eNB_addr.sin_port = htons(PORT);

    if(connect(com_socket, (struct sockaddr *)&eNB_addr, sizeof(eNB_addr))<0)
    {
        printf("Connection failed due to port and ip problems\n");
        return 1;
    }
    
    // Send the RRC connection request
    msg = "RRC Connection ReQuest";
    strcpy(sent_buffer, &msg[0]);
    send(com_socket, sent_buffer, strlen(sent_buffer), 0);
    cout << "Send RRC Connection ReQuest" << endl;
    
    // After that wait for the RRC connection setup
    read(com_socket, received_buffer, sizeof(received_buffer) - 1);
    cout << "receive packet:" << received_buffer << endl;
    
    //Finally, 
    msg = "RRC Connection Setup Complete";
    strcpy(sent_buffer, &msg[0]);
    send(com_socket, sent_buffer, strlen(sent_buffer), 0);
    cout << "Send RRC Connection Setup Complete" << endl;

    // Close
    close(com_socket);

    return 0;
}

int main(){
    RRC();
    return 0;

}