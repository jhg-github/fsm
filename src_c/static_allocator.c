/* Includes ------------------------------------------------------------------*/
#include "static_allocator.h"
#include <stdbool.h>
#include "assert.h"


/* Constants -----------------------------------------------------------------*/
#define SALLOC_N_BLOCKS 		(40)	// a block is a uint32_t to avoid alignment problems
#define SALLOC_BLOCK_SIZE		(4)


/* Variables -----------------------------------------------------------------*/
static uint32_t salloc_memory_buffer[SALLOC_N_BLOCKS];
static bool salloc_enabled = true;
static uint32_t salloc_free_index = 0;


/* Public Functions ----------------------------------------------------------*/

void * salloc_4bytes(uint32_t size_bytes){
    void *next_free;
    uint32_t n_blocks;
		if( size_bytes % 4 == 0){	// to make it aligned to 4 bytes Cortex-M
			n_blocks = size_bytes / 4;
		} else {
			n_blocks = (size_bytes / 4) + 1;  
		}
    ASSERT(salloc_enabled);
    if( (salloc_free_index + n_blocks) > SALLOC_N_BLOCKS ) {
        ASSERT(false);
    }
    next_free = &salloc_memory_buffer[salloc_free_index];
    salloc_free_index += n_blocks;
    return next_free;
}

void salloc_disable(void){
    salloc_enabled = false;
}
