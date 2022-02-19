#include <stdio.h>
#include <sys/types.h>
#include <Rectangle.h>

static int save_to_file(const void *data, size_t size, void *key) {
    FILE *fp = key;
    return (fwrite(data, 1, size, fp) == size) ? 0 : -1;
}

unsigned char * Rectangle_encode(Rectangle_t *rect){
    asn_enc_rval_t er;
    static unsigned char buffer[1024];
    for(int i = 0; i<1024; i++){
        buffer[i] = 0;
    }

    FILE *fp = fopen("file.bin", "wb");
    if(!fp) {
        printf("Error open file\n");
        exit(1);
    }
    er = der_encode(&asn_DEF_Rectangle, rect, save_to_file, fp);
    fclose(fp);

    if(er.encoded == -1) {
        fprintf(stderr, "Failed to encode %s\n", asn_DEF_Rectangle.name);
        exit(1);
    } else {
        fprintf(stderr, "%s encoded in %zd bytes\n", asn_DEF_Rectangle.name, er.encoded);
    }

    fp = fopen("file.bin", "rb");
    fread(buffer,sizeof(buffer),1,fp);
    fclose(fp);
    
    return &buffer;
}