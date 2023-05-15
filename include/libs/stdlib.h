/* Ce fichier contient certaines focntions standards
contenu généralement dans la stdlib.*/

#ifndef _STDLIB_
#define _STDLIB_

#include <stdint.h>
#include <stddef.h>

void *memcpy(void *srcPtr, void *destPtr, size_t size);
void *memset(void *buffer, uint32_t value, size_t size);
uint32_t memcmp(const void *ptra, const void *ptrb, size_t size);

#endif
