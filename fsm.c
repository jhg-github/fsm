#include "fsm.h"


/* Public Functions ----------------------------------------------------------*/
void fsm_Ctor(fsm_Fsm *me, fsm_State init) {
    me->state = init;
}

void fsm_Init(fsm_Fsm *me, fsm_Event const *e) {
    me->state(me, e);
}

void fsm_Dispatch(fsm_Fsm *me, fsm_Event const *e) {
    me->state(me, e);
}

void fsm_Transition(fsm_Fsm *me, fsm_State target) {
    me->state = target;
}

