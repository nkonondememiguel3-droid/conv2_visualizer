#ifndef config_h
#define config_h

#include <stdlib.h>

struct nk_context;

void load_font( struct nk_context *ctx );

// allocators for arena
void *alloc_mkl( size_t bytes, void *user_data );
void *realloc_mkl( void *ptr, size_t new_size, void *user_data );
void free_mkl( void *ptr, void *user_data );

#endif // config_h
