/* Includes ------------------------------------------------------------------*/
#include "fsm.h"


/* Constants -----------------------------------------------------------------*/
static fsm_Event const initEvt = { fsm_INIT_SIG };
static fsm_Event const entryEvt = { fsm_ENTRY_SIG };
static fsm_Event const exitEvt = { fsm_EXIT_SIG };


/* Public Functions ----------------------------------------------------------*/
void fsm_Ctor(fsm_Fsm *me, fsm_State init) {
  me->state = init;
}

void fsm_Init(fsm_Fsm *me) {
  me->state(me, &initEvt);
}

void fsm_Dispatch(fsm_Fsm *me, fsm_Event const *e) {
	me->state(me, e);
}

void fsm_Transition(fsm_Fsm *me, fsm_State target) {
	fsm_Dispatch(me, &exitEvt);
	me->state = target;
	fsm_Dispatch(me, &entryEvt);
}

void fsm_EventSetSignal(fsm_Event *me, fsm_Signal signal){
	me->signal = signal;
}
