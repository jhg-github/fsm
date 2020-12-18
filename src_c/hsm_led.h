#ifndef __HSM_LED_H
#define __HSM_LED_H

#include "hsm.h"
#include "queue.h"
#include "swtimer.h"


/* Types ---------------------------------------------------------------------*/
typedef struct hsmLed_Hsm hsmLed_Hsm;
struct hsmLed_Hsm {
  hsm_Hsm base; /* extend the Hsm class */
	queue_t * evt_queue;
	swtimer_t * blink_timer;
};

typedef struct hsmLed_Event hsmLed_Event;
struct hsmLed_Event {
    hsm_Event base; /* extend the Event class */
};

/* signals used by the Led FSM */
enum {
	hsmLed_INIT_SIG = hsm_INIT_SIG,			// must be the same on all hsm
	hsmLed_ENTRY_SIG = hsm_ENTRY_SIG,		// must be the same on all hsm
	hsmLed_EXIT_SIG = hsm_EXIT_SIG,			// must be the same on all hsm
	hsmLed_BUTT_PRESSED_SIG,
	hsmLed_TIMEOUT_BLINK_SIG
};


/* Public Functions ----------------------------------------------------------*/
void hsmLed_Ctor( hsmLed_Hsm * me, uint32_t evt_buf_n_elem);
void hsmLed_Init(hsmLed_Hsm * me);
void hsmLed_Run( hsmLed_Hsm * me);
void hsmLed_SendEvent( hsmLed_Hsm * me, hsmLed_Event * evt );


#endif // #ifndef __HSM_LED_H
