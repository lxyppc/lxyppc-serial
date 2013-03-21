#ifndef POLARSSL_MEM_H
#define POLARSSL_MEM_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#ifdef _MSC_VER
#include <basetsd.h>
typedef UINT32 uint32_t;
#else
#include <inttypes.h>
#endif


#ifdef __cplusplus
extern "C" {
#endif


/**
 * \brief          alloc memory from the pool
 *
 * \param ctx      Pointer to the memory pool
 * \param size     length of memory
 */
void* x_malloc( void* pool, size_t size );
void x_free( void* pool, void* p );
void* x_realloc(void* pool, void*p, size_t size);

void* x_mem_init(void);
void x_mem_free(void* pool);
void x_memset(void*p, int v, size_t len);
void x_memcpy(void* dest, const char* src, size_t len);
    
#if defined ( __CC_ARM )
#define  EMBEDDED_SYSTEM
#endif


#ifdef __cplusplus
}
#endif

#endif /* md5.h */

