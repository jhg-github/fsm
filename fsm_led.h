#ifndef __FSM_LED_H
#define __FSM_LED_H

#include "fsm.h"


/* Types ---------------------------------------------------------------------*/
typedef struct fsm_LedFsm fsm_LedFsm;
struct fsm_LedFsm {
    fsm_Fsm base; /* extend the Fsm class */
/* ... other attributes of Led */
};

typedef struct fsm_LedEvt fsm_LedEvt;
struct fsm_LedEvt {
    fsm_Event base; /* extend the Event class */
/* ... other attributes of LedEvt */
};

/* signals used by the Led FSM */
enum {
    fsm_led_TURN_ON_SIG,
		fsm_led_TURN_OFF_SIG,
};

/* Public Functions ----------------------------------------------------------*/
void LedCtor(fsm_LedFsm *me);




#endif // #ifndef __FSM_LED_H
