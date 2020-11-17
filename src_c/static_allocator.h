#ifndef __STATIC_ALLOCATOR_H
#define __STATIC_ALLOCATOR_H


/* Includes ------------------------------------------------------------------*/
#include "main.h"


/* Public Functions ----------------------------------------------------------*/

void * salloc_4bytes(uint32_t size_bytes);
void salloc_disable(void);

#endif // #ifndef __STATIC_ALLOCATOR_H
