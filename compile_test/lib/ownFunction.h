#ifndef	_ownFunction_H_
#define	_ownFunction_H_


// #include <asn_application.h>
#include <Rectangle.h>

#ifdef __cplusplus
extern "C" {
#endif

static int save_to_file(const void *data, size_t size, void *key);

unsigned char * Rectangle_encode(Rectangle_t *rect);


#ifdef __cplusplus
}
#endif

#endif