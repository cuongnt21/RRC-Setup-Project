#include <stdio.h>
#include <sys/types.h>
#include <iostream>
#include "RRCMessage.h"
#include "ownFunction.h"

using namespace std;

int main(){
    RRCMessage_t *mess = new RRCMessage_t();
    mess = addData(mess);
    mess->messid = ID_rrcSetupComplete;

    unsigned char *p;
    p = Message_encode(mess);
    
    // Print the buffer
    // 20 la vi du the
    for(int i = 0; i<24; i++){
        if (*(p + i) <16){
            printf("0%X ", *(p + i));
        } else {
            printf("%X ", *(p + i));
        }
    }
    printf("\n");

    RRCMessage_t *mess_recei = new RRCMessage_t();
    asn_dec_rval_t rval;

    rval = ber_decode(0, &asn_DEF_RRCMessage, (void **)&mess_recei, p, 1024);
    if(rval.code != RC_OK) {
        printf("Broken encoding");
        return 0;
    }
    if (mess_recei->messid == ID_rrcSetupComplete){
        cout << mess_recei->messid << endl;
    }

    return 0;
}