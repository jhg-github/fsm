#ifndef __FSM_EVENT_BUFFER_H
#define __FSM_EVENT_BUFFER_H


/* Includes ------------------------------------------------------------------*/
#include "fsm.h"
#include "main.h"


/**
 * @brief Event buffer is a ring buffer to keep incoming events until they are consumed
 * Properties:
 *  - Uses an array that is allocated statically
 *  - FIFO
 *  - If it is full the new event is not saved and error is returned * 
 */

/* Types ---------------------------------------------------------------------*/
typedef struct fsm_event_buf_t fsm_event_buf_t;
typedef fsm_event_buf_t * fsm_event_buf_handle_t;


/* Public Functions ----------------------------------------------------------*/
fsm_event_buf_handle_t fsm_event_buffer_Constructor(uint32_t n_elem, uint32_t size_elem_bytes);




#endif // #ifndef __FSM_EVENT_BUFFER_H
