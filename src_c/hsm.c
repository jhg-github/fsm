/* Includes ------------------------------------------------------------------*/
#include "hsm.h"


/* Constants -----------------------------------------------------------------*/
static hsm_Event const initEvt = { hsm_INIT_SIG };
static hsm_Event const entryEvt = { hsm_ENTRY_SIG };
static hsm_Event const exitEvt = { hsm_EXIT_SIG };


/* Public Functions ----------------------------------------------------------*/
void hsm_Ctor(hsm_Hsm *me, hsm_State init) {
  me->state = init;
}

void hsm_Init(hsm_Hsm *me) {
  me->state(me, &initEvt);
}

void hsm_Dispatch(hsm_Hsm *me, hsm_Event const *e) {
	me->state(me, e);
}

void hsm_Transition(hsm_Hsm *me, hsm_State target) {
	hsm_Dispatch(me, &exitEvt);
	me->state = target;
	hsm_Dispatch(me, &entryEvt);
}

void hsm_EventSetSignal(hsm_Event *me, hsm_Signal signal){
	me->signal = signal;
}
