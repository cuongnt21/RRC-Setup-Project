#include <stdio.h>
#include <sys/types.h>
#include <Rectangle.h>

int main(){
    char buf[1024]; /* Temporary buffer */
    asn_dec_rval_t rval; /* Decoder return value */
    Rectangle_t *rectangle = 0 ; /* Type to decode. Note this 0 ! */

    FILE *fp;       /* Input file handler */
    size_t size;    /* Number of bytes read */
    char *filename; /* Input file name */

    filename = "file.bin";
    
    /* Open input file as read-only binary */
    fp = fopen(filename, "rb");
    if(!fp) {
        printf("Error open");
        exit(1);
    }

    /* Read up to the buffer size */
    size = fread(buf, 1, sizeof(buf), fp);
    fclose(fp);
    if(!size) {
        fprintf(stderr, "%s: Empty or broken\n", filename);
        exit(1);
    }
    
    // Print the buffer
    for(int i = 0; i<size; i++){
        printf("%u ", buf[i]);
    }
    printf("\n");
    // printf("%u\n", buf);

    /* Decode the input buffer as Rectangle type */
    rval = ber_decode(0, &asn_DEF_Rectangle, (void **)&rectangle, buf, size);
    if(rval.code != RC_OK) {
        fprintf(stderr, "%s: Broken Rectangle encoding at byte %ld\n", filename, (long)rval.consumed);
        exit(1);
    }
    
    printf("height: %zd\n", rectangle->height);
    printf("width: %zd\n", rectangle->width);

    return 0; /* Decoding finished successfully */
}