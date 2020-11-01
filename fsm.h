#ifndef __FSM_H
#define __FSM_H

typedef short Signal;
typedef struct Event Event;
typedef struct Fsm Fsm;
typedef void (*State)(Fsm*, Event const*);

/* Event base class */
struct Event {
    Signal sig;
};

/* Finite State Machine base class */
struct Fsm {
    State state__; /* the current state */
};

/* "inlined" methods of Fsm class */
//#define FsmCtor_(me_, init_) ((me_)->state__ = (State)(init_))
//#define FsmInit(me_, e_)     (*(me_)->state__)((me_), (e_))
//#define FsmDispatch(me_, e_) (*(me_)->state__)((me_), (e_))
//#define FsmTran_(me_, targ_) ((me_)->state__ = (State)(targ_))
void FsmCtor_(Fsm *me, State init);
void FsmInit(Fsm *me, Event const *e);
void FsmDispatch(Fsm *me, Event const *e);
void FsmTran_(Fsm *me, State target);

#endif // #ifndef __FSM_H
