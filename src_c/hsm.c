/* Includes ------------------------------------------------------------------*/
#include "hsm.h"
#include "main.h"


/* Constants -----------------------------------------------------------------*/
static hsm_Event const initEvt = { hsm_INIT_SIG };
static hsm_Event const entryEvt = { hsm_ENTRY_SIG };
static hsm_Event const exitEvt = { hsm_EXIT_SIG };


/* Public Functions ----------------------------------------------------------*/
void hsm_Ctor(hsm_Hsm *me, hsm_State init) {
  me->state = init;
}

void hsm_Init(hsm_Hsm *me) {
  me->state.state_func(me, &initEvt);
}

void hsm_Dispatch(hsm_Hsm *me, hsm_Event const *e) {
	hsm_State next = me->state;
	do{
		next = next.state_func(me, e);
	} while( next.state_func != NULL);
}

void hsm_Transition(hsm_Hsm *me, hsm_State target) {
	hsm_Dispatch(me, &exitEvt);
	me->state = target;
	hsm_Dispatch(me, &entryEvt);
}

void hsm_EventSetSignal(hsm_Event *me, hsm_Signal signal){
	me->signal = signal;
}
