#include <stdio.h>
#include <sys/types.h>
#include <Rectangle.h>

static int save_to_file(const void *data, size_t size, void *key) {
    FILE *fp = key;
    return (fwrite(data, 1, size, fp) == size) ? 0 : -1;
}

int main(){
    Rectangle_t *rect;
    asn_enc_rval_t er;

    /* Allocate the Rectangle_t */
    rect = calloc(1, sizeof(Rectangle_t)); /* not malloc! */
    if(!rect) {
        perror("calloc() failed");
        exit(1);
    }

    /* Initialize the Rectangle members */
    rect->height = 100; /* any random value */
    rect->width = 150; /* any random value */

    FILE *fp = fopen("file.bin", "wb");

    if(!fp) {
        // perror(filename);
        exit(1);
    }
    er = der_encode(&asn_DEF_Rectangle, rect, save_to_file, fp);
    fclose(fp);

    if(er.encoded == -1) {
        fprintf(stderr, "Failed to encode %s\n", asn_DEF_Rectangle.name);
    } else {
        fprintf(stderr, "%s encoded in %zd bytes\n", asn_DEF_Rectangle.name, er.encoded);
    }

    int n = er.encoded;
    static unsigned char buffer[n];
    for(int i = 0; i<n; i++){
        buffer[i] = 0;
    }
    fp = fopen("file.bin", "rb");

    fread(buffer,sizeof(buffer),1,fp);
    fclose(fp);
    for(int i = 0; i<n; i++){
        if (buffer[i] <16){
            printf("0%X ", buffer[i]);
        } else {
            printf("%X ", buffer[i]);
        }
    }
    printf("\n");
    return 0;
}