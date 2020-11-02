#ifndef __FSM_H
#define __FSM_H


/* Types ---------------------------------------------------------------------*/
typedef short fsm_Signal;
typedef struct fsm_Event fsm_Event;
typedef struct fsm_Fsm fsm_Fsm;
typedef void (*fsm_State)(fsm_Fsm*, fsm_Event const*);

/* Event base class */
struct fsm_Event {
    fsm_Signal sig;
};

/* Finite State Machine base class */
struct fsm_Fsm {
    fsm_State state; /* the current state */
};


/* Public Functions ----------------------------------------------------------*/

/* "inlined" methods of Fsm class */
//#define FsmCtor_(me_, init_) ((me_)->state__ = (State)(init_))
//#define FsmInit(me_, e_)     (*(me_)->state__)((me_), (e_))
//#define FsmDispatch(me_, e_) (*(me_)->state__)((me_), (e_))
//#define FsmTran_(me_, targ_) ((me_)->state__ = (State)(targ_))
void fsm_FsmCtor(fsm_Fsm *me, fsm_State init);
void fsm_FsmInit(fsm_Fsm *me, fsm_Event const *e);
void fsm_FsmDispatch(fsm_Fsm *me, fsm_Event const *e);
void fsm_FsmTransition(fsm_Fsm *me, fsm_State target);

#endif // #ifndef __FSM_H
