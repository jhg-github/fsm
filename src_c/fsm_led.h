#ifndef __FSM_LED_H
#define __FSM_LED_H

#include "fsm.h"


/* Types ---------------------------------------------------------------------*/
typedef struct fsmLed_Fsm fsmLed_Fsm;
struct fsmLed_Fsm {
    fsm_Fsm base; /* extend the Fsm class */
/* ... other attributes of Led */
};

typedef struct fsmLed_Event fsmLed_Event;
struct fsmLed_Event {
    fsm_Event base; /* extend the Event class */
/* ... other attributes of LedEvt */
};

/* signals used by the Led FSM */
enum {
    fsmLed_TURN_ON_SIG,
		fsmLed_TURN_OFF_SIG,
};

/* Public Functions ----------------------------------------------------------*/
void LedCtor(fsmLed_Fsm *me);




#endif // #ifndef __FSM_LED_H