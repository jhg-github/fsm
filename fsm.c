#include "fsm.h"

/* "inlined" methods of Fsm class */
//#define FsmCtor_(me_, init_) ((me_)->state__ = (State)(init_))
//#define FsmInit(me_, e_)     (*(me_)->state__)((me_), (e_))
//#define FsmDispatch(me_, e_) (*(me_)->state__)((me_), (e_))
//#define FsmTran_(me_, targ_) ((me_)->state__ = (State)(targ_))

void FsmCtor_(Fsm *me, State init) {
    me->state__ = init;
}

void FsmInit(Fsm *me, Event const *e) {
    me->state__(me, e);
}

void FsmDispatch(Fsm *me, Event const *e) {
    me->state__(me, e);
}

void FsmTran_(Fsm *me, State target) {
    me->state__ = target;
}

