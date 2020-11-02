#include "fsm.h"


/* Public Functions ----------------------------------------------------------*/

/* "inlined" methods of Fsm class */
//#define FsmCtor_(me_, init_) ((me_)->state__ = (State)(init_))
//#define FsmInit(me_, e_)     (*(me_)->state__)((me_), (e_))
//#define FsmDispatch(me_, e_) (*(me_)->state__)((me_), (e_))
//#define FsmTran_(me_, targ_) ((me_)->state__ = (State)(targ_))

void fsm_FsmCtor(fsm_Fsm *me, fsm_State init) {
    me->state = init;
}

void fsm_FsmInit(fsm_Fsm *me, fsm_Event const *e) {
    me->state(me, e);
}

void fsm_FsmDispatch(fsm_Fsm *me, fsm_Event const *e) {
    me->state(me, e);
}

void fsm_FsmTransition(fsm_Fsm *me, fsm_State target) {
    me->state = target;
}

