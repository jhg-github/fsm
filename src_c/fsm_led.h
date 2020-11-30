#ifndef __FSM_LED_H
#define __FSM_LED_H

#include "fsm.h"
#include "queue.h"


/* Types ---------------------------------------------------------------------*/
typedef struct fsmLed_Fsm fsmLed_Fsm;
struct fsmLed_Fsm {
  fsm_Fsm base; /* extend the Fsm class */
	queue_t * evt_queue;
};

typedef struct fsmLed_Event fsmLed_Event;
struct fsmLed_Event {
    fsm_Event base; /* extend the Event class */
};

/* signals used by the Led FSM */
enum {
	fsmLed_BUTT_PRESSED_SIG
};


/* Public Functions ----------------------------------------------------------*/
void LedCtor( fsmLed_Fsm * me, uint32_t evt_buf_n_elem);
void Led_Init(fsmLed_Fsm * me);
void Led_Run( fsmLed_Fsm * me);
void Led_SendEvent( fsmLed_Fsm * me, fsmLed_Event * evt );


#endif // #ifndef __FSM_LED_H
