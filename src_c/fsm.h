#ifndef __FSM_H
#define __FSM_H


/* Types ---------------------------------------------------------------------*/
typedef short fsm_Signal;
typedef struct fsm_Event fsm_Event;
typedef struct fsm_Fsm fsm_Fsm;
typedef void (*fsm_State)(fsm_Fsm*, fsm_Event const*);

/* Event base class */
struct fsm_Event {
    fsm_Signal signal;
};

/* Finite State Machine base class */
struct fsm_Fsm {
    fsm_State state; /* the current state */
};

/* signals used by the Led FSM */
enum {
	fsm_INIT_SIG,
	fsm_ENTRY_SIG,
	fsm_EXIT_SIG
};


/* Public Functions ----------------------------------------------------------*/
void fsm_Ctor(fsm_Fsm *me, fsm_State init);
void fsm_Init(fsm_Fsm *me);
void fsm_Dispatch(fsm_Fsm *me, fsm_Event const *e);
void fsm_Transition(fsm_Fsm *me, fsm_State target);

void fsm_EventSetSignal(fsm_Event *me, fsm_Signal signal);

#endif // #ifndef __FSM_H
