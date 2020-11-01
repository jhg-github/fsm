#ifndef __FSM_LED_H
#define __FSM_LED_H

#include "fsm.h"

typedef struct Led Led;
struct Led {
    Fsm super_; /* extend the Fsm class */
/* ... other attributes of Led */
};

void LedCtor(Led *me);
void Led_initial(Led *me, Event const *e);
void Led_on(Led *me, Event const *e);
void Led_off(Led *me, Event const *e);

typedef struct LedEvt LedEvt;
struct LedEvt {
    Event super_; /* extend the Event class */
/* ... other attributes of LedEvt */
};

/* signals used by the Led FSM */
enum {
    TURN_ON_SIG, TURN_OFF_SIG,
};

#endif // #ifndef __FSM_LED_H
