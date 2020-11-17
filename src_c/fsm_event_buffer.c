/* Includes ------------------------------------------------------------------*/
#include "fsm_event_buffer.h"
#include "static_allocator.h"
#include "assert.h"


/* Types ---------------------------------------------------------------------*/
struct fsm_event_buf_t {
    void * buffer;  
    uint32_t n_elem;
};


/* Public Functions ----------------------------------------------------------*/
fsm_event_buf_handle_t fsm_event_buffer_Constructor(uint32_t n_elem, uint32_t size_elem_bytes){
  fsm_event_buf_handle_t evt_buf;
  
//  ASSERT(n_elem && size_elem_bytes);
//  
//  evt_buf = salloc(sizeof(fsm_event_buf_t));
//  evt_buf->buffer = salloc(n_elem*size_elem_bytes);
//  evt_buf->n_elem = n_elem;
  return evt_buf;
}
