#include "fsm_led.h"
#include "main.h"
#include "static_allocator.h"


/* Constants -----------------------------------------------------------------*/
#define FSM_LED_EVENT_BUFFER_SIZE   (3)


/* Function Prototypes -------------------------------------------------------*/
static void Led_initial(fsmLed_Fsm *me, fsm_Event const *e);
static void Led_on(fsmLed_Fsm *me, fsm_Event const *e);
static void Led_off(fsmLed_Fsm *me, fsm_Event const *e);
static void SetLedOn(void);
static void SetLedOff(void);


/* Public Functions ----------------------------------------------------------*/
void LedCtor( fsmLed_Fsm * me, uint32_t evt_buf_n_elem){
	fsm_Ctor(&me->base, (fsm_State) Led_initial);
	me->evt_queue = queue_Constructor(evt_buf_n_elem, sizeof(fsmLed_Event));
}

void Led_Init(fsmLed_Fsm * me){
	fsm_Init(&me->base, 0);
}

void Led_Run(fsmLed_Fsm * me){
	bool res;
	static fsmLed_Event evt;
	res = queue_Dequeue( me->evt_queue, &evt);
	if(res){
		fsm_Dispatch(&me->base, &evt.base);
	}
}

void Led_SendEvent( fsmLed_Fsm * me, fsmLed_Event * evt ){
	queue_Enqueue( me->evt_queue, evt );
}




/* States Functions ----------------------------------------------------------*/

static void Led_initial(fsmLed_Fsm *me, fsm_Event const *e) {
    SetLedOn();
    fsm_Transition((fsm_Fsm*) me, (fsm_State) Led_on);
}

static void Led_on(fsmLed_Fsm *me, fsm_Event const *e) {
    switch (e->signal) {
    case fsmLed_TURN_OFF_SIG:
        SetLedOff();
        fsm_Transition((fsm_Fsm*) me, (fsm_State) Led_off);
        break;
    }
}

static void Led_off(fsmLed_Fsm *me, fsm_Event const *e) {
    switch (e->signal) {
    case fsmLed_TURN_ON_SIG:
        SetLedOn();
        fsm_Transition((fsm_Fsm*) me, (fsm_State) Led_on);
        break;
    }
}


/* Private Functions ---------------------------------------------------------*/

static void SetLedOn(void) {
    HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_SET);
}
static void SetLedOff(void) {
    HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);
}
