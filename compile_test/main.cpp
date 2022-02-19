#include <stdio.h>
#include <sys/types.h>
#include <iostream>
#include "Rectangle.h"
#include "ownFunction.h"

using namespace std;

int main(){
    cout << "extern c" << endl;
    Rectangle_t *rect = new Rectangle_t();

    /* Initialize the Rectangle members */
    rect->height = 500; /* any random value */
    rect->width = 700; /* any random value */

    unsigned char *p;
    p = Rectangle_encode(rect);
    
    // Print the buffer
    // 20 la vi du the
    for(int i = 0; i<20; i++){
        if (*(p + i) <16){
            printf("0%X ", *(p + i));
        } else {
            printf("%X ", *(p + i));
        }
    }
    printf("\n");

    Rectangle_t *rect_recei = new Rectangle_t();
    asn_dec_rval_t rval;

    rval = ber_decode(0, &asn_DEF_Rectangle, (void **)&rect_recei, p, 1024);
    if(rval.code != RC_OK) {
        printf("Broken encoding");
        return 0;
    }

    // rect_recei = Rectangle_decode(rect_recei, p, 1024);
    printf("height: %zd\n", rect_recei->height);
    printf("width: %zd\n", rect_recei->width);

    return 0;
}