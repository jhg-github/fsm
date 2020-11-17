/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include "queue.h"
#include "static_allocator.h"
#include "assert.h"


/* Types ---------------------------------------------------------------------*/
struct queue_t {
  void * buffer;  
	int buffer_size;
  int max_n_elem;
	int elem_size_bytes;
	int write_idx;
	int read_idx;
	int n_elem;
	int mark_max_n_elem;
};


/* Public Functions ----------------------------------------------------------*/
queue_t * queue_Constructor(uint32_t max_n_elem, uint32_t size_elem_bytes){
  queue_t * queue;
  
  ASSERT(max_n_elem && size_elem_bytes);
  
  queue = salloc_4bytes(sizeof(queue_t));
	queue->buffer_size = max_n_elem*size_elem_bytes;
  queue->buffer = salloc_4bytes(queue->buffer_size);
  queue->max_n_elem = max_n_elem;
	queue->elem_size_bytes = size_elem_bytes;
	queue->write_idx = -1;
	queue->read_idx = 0;
	queue->n_elem = 0;
	queue->mark_max_n_elem = 0;
  return queue;
}


bool queue_Enqueue(queue_t * me, void * elem){
	uint32_t dest;
	
	ASSERT(me && elem);
	
	if(me->n_elem == me->max_n_elem){
		return false;	// fail buffer full
	}
	me->write_idx = (me->write_idx + 1) % me->max_n_elem;
	dest = (uint32_t)(me->buffer) + (me->write_idx*me->elem_size_bytes);
	memcpy((void *)dest, elem, me->elem_size_bytes);
	me->n_elem +=1;
	if(me->n_elem > me->mark_max_n_elem){
		me->mark_max_n_elem = me->n_elem;
	}
	return true; // ok
}

bool queue_Dequeue(queue_t * me, void * elem){
	uint32_t src;
	
	ASSERT(me);

	if(me->n_elem == 0){
		return false;	// fail buffer empty
	}
	src = (uint32_t)(me->buffer) + (me->read_idx*me->elem_size_bytes);
	memcpy(elem, (void *)src, me->elem_size_bytes);
	me->read_idx = (me->read_idx + 1) % me->max_n_elem;
	me->n_elem -=1;
	return true; // ok
}



/* Public Test Functions -------------------------------------------------------*/
typedef struct queue_test_elem_t{
	uint8_t a;
} queue_test_elem_t;

static volatile queue_test_elem_t queue_test_elem;
static volatile bool queue_test_res;
static queue_t * queue_test_queue;

void queue_test(void){	
	queue_test_queue = queue_Constructor(3, sizeof(queue_test_elem_t));
	
	queue_test_res = queue_Dequeue(queue_test_queue, (void *)&queue_test_elem);
	ASSERT(queue_test_res == false);
	
	queue_test_elem.a=3;
	queue_test_res = queue_Enqueue(queue_test_queue, (void *)&queue_test_elem);
	ASSERT(queue_test_res == true);
	
	queue_test_res = queue_Dequeue(queue_test_queue, (void *)&queue_test_elem);
	ASSERT(queue_test_res == true);
	ASSERT(queue_test_elem.a == 3);
	
	queue_test_res = queue_Dequeue(queue_test_queue, (void *)&queue_test_elem);
	ASSERT(queue_test_res == false);
	
	queue_test_elem.a=5;
	queue_test_res = queue_Enqueue(queue_test_queue, (void *)&queue_test_elem);
	ASSERT(queue_test_res == true);

	queue_test_elem.a=7;
	queue_test_res = queue_Enqueue(queue_test_queue, (void *)&queue_test_elem);
	ASSERT(queue_test_res == true);
	
	queue_test_elem.a=9;
	queue_test_res = queue_Enqueue(queue_test_queue, (void *)&queue_test_elem);
	ASSERT(queue_test_res == true);
	
	queue_test_elem.a=1;
	queue_test_res = queue_Enqueue(queue_test_queue, (void *)&queue_test_elem);
	ASSERT(queue_test_res == false);
	
	queue_test_res = queue_Dequeue(queue_test_queue, (void *)&queue_test_elem);
	ASSERT(queue_test_res == true);
	ASSERT(queue_test_elem.a == 5);

	queue_test_res = queue_Dequeue(queue_test_queue, (void *)&queue_test_elem);
	ASSERT(queue_test_res == true);
	ASSERT(queue_test_elem.a == 7);
	
	queue_test_res = queue_Dequeue(queue_test_queue, (void *)&queue_test_elem);
	ASSERT(queue_test_res == true);
	ASSERT(queue_test_elem.a == 9);
	
	queue_test_res = queue_Dequeue(queue_test_queue, (void *)&queue_test_elem);
	ASSERT(queue_test_res == false);
}


