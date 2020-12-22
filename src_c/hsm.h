#ifndef __HSM_H
#define __HSM_H


/* Types ---------------------------------------------------------------------*/
typedef short hsm_Signal;
typedef struct hsm_Event hsm_Event;
typedef struct hsm_Hsm hsm_Hsm;

//typedef void (*hsm_State)(hsm_Hsm*, hsm_Event const*);
typedef struct hsm_State hsm_State;
typedef hsm_State (*hsm_StateFunc)(hsm_Hsm*, hsm_Event const*);
struct hsm_State{
	hsm_StateFunc state_func;
};


/* Event base class */
struct hsm_Event {
    hsm_Signal signal;
};

/* Finite State Machine base class */
struct hsm_Hsm {
    hsm_State state; /* the current state */
};

/* signals used by the Led FSM */
enum {
	hsm_INIT_SIG,
	hsm_ENTRY_SIG,
	hsm_EXIT_SIG
};


/* Public Functions ----------------------------------------------------------*/
void hsm_Ctor(hsm_Hsm *me, hsm_State init);
void hsm_Init(hsm_Hsm *me);
void hsm_Dispatch(hsm_Hsm *me, hsm_Event const *e);
void hsm_Transition(hsm_Hsm *me, hsm_State target);

void hsm_EventSetSignal(hsm_Event *me, hsm_Signal signal);

#endif // #ifndef __HSM_H
