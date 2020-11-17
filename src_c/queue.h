#ifndef __FSM_EVENT_BUFFER_H
#define __FSM_EVENT_BUFFER_H


/* Includes ------------------------------------------------------------------*/
#include "fsm.h"
#include "main.h"


/**
 * @brief Circular queue
 * Properties:
 *  - Uses an array that is allocated statically
 *  - FIFO
 *  - If it is full the new event is not saved and error is returned * 
 */

/* Types ---------------------------------------------------------------------*/
typedef struct queue_t queue_t;


/* Public Functions ----------------------------------------------------------*/
queue_t * queue_Constructor(uint32_t n_elem, uint32_t size_elem_bytes);
bool queue_Enqueue(queue_t * me, void * elem);
bool queue_Dequeue(queue_t * me, void * elem);

/* Public Test Functions -------------------------------------------------------*/
void queue_test(void);



#endif // #ifndef __FSM_EVENT_BUFFER_H
