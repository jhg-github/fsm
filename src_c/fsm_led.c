#include "fsm_led.h"
#include "main.h"
#include "static_allocator.h"


/* Constants -----------------------------------------------------------------*/
#define FSM_LED_EVENT_BUFFER_SIZE   (3)


/* Function Prototypes -------------------------------------------------------*/
static void Led_State_Initial(fsmLed_Fsm *me, fsm_Event const *e);
static void Led_State_LedOn(fsmLed_Fsm *me, fsm_Event const *e);
static void Led_State_LedOff(fsmLed_Fsm *me, fsm_Event const *e);
static void Led_State_BlinkOn(fsmLed_Fsm *me, fsm_Event const *e);
static void Led_State_BlinkOff(fsmLed_Fsm *me, fsm_Event const *e);

static void SetLedOn(void);
static void SetLedOff(void);
static void TimerCallback(void * fsm);


/* Public Functions ----------------------------------------------------------*/
void fsmLed_Ctor( fsmLed_Fsm * me, uint32_t evt_buf_n_elem){
	fsm_Ctor(&me->base, (fsm_State) Led_State_Initial);
	me->evt_queue = queue_Constructor(evt_buf_n_elem, sizeof(fsmLed_Event));
	me->blink_timer = swtimer_Constructor();
}

void fsmLed_Init(fsmLed_Fsm * me){
	fsm_Init(&me->base, 0);
}

void fsmLed_Run(fsmLed_Fsm * me){
	bool res;
	static fsmLed_Event evt;
	res = queue_Dequeue( me->evt_queue, &evt);
	if(res){
		fsm_Dispatch(&me->base, &evt.base);
	}
}

void fsmLed_SendEvent( fsmLed_Fsm * me, fsmLed_Event * evt ){
	queue_Enqueue( me->evt_queue, evt );
}




/* States Functions ----------------------------------------------------------*/

static void Led_State_Initial(fsmLed_Fsm *me, fsm_Event const *e) {
    SetLedOn();
    fsm_Transition((fsm_Fsm*) me, (fsm_State) Led_State_LedOn);
}

static void Led_State_LedOn(fsmLed_Fsm *me, fsm_Event const *e) {
    switch (e->signal) {
    case fsmLed_BUTT_PRESSED_SIG:
        SetLedOff();
				swtimer_Start(me->blink_timer, 100, true, TimerCallback, me);
        fsm_Transition((fsm_Fsm*) me, (fsm_State) Led_State_BlinkOff);
        break;
    }
}

static void Led_State_LedOff(fsmLed_Fsm *me, fsm_Event const *e) {
    switch (e->signal) {
    case fsmLed_BUTT_PRESSED_SIG:
        SetLedOn();
        fsm_Transition((fsm_Fsm*) me, (fsm_State) Led_State_LedOn);
        break;
    }
}

static void Led_State_BlinkOn(fsmLed_Fsm *me, fsm_Event const *e) {
    switch (e->signal) {
    case fsmLed_BUTT_PRESSED_SIG:
        SetLedOff();
				swtimer_Stop(me->blink_timer);
        fsm_Transition((fsm_Fsm*) me, (fsm_State) Led_State_LedOff);
        break;
		case fsmLed_TIMEOUT_BLINK_SIG:
        SetLedOff();
        fsm_Transition((fsm_Fsm*) me, (fsm_State) Led_State_BlinkOff);
        break;
    }
}

static void Led_State_BlinkOff(fsmLed_Fsm *me, fsm_Event const *e) {
    switch (e->signal) {
    case fsmLed_BUTT_PRESSED_SIG:
        SetLedOff();
				swtimer_Stop(me->blink_timer);
        fsm_Transition((fsm_Fsm*) me, (fsm_State) Led_State_LedOff);
        break;
		case fsmLed_TIMEOUT_BLINK_SIG:
        SetLedOn();
        fsm_Transition((fsm_Fsm*) me, (fsm_State) Led_State_BlinkOn);
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

static void TimerCallback(void * data){
	static fsmLed_Event led_evt;
	fsm_EventSetSignal(&led_evt.base, fsmLed_TIMEOUT_BLINK_SIG);
	fsmLed_SendEvent( (fsmLed_Fsm*)data, &led_evt );
}
