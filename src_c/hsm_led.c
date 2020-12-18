#include "hsm_led.h"
#include "main.h"
#include "static_allocator.h"


/* Constants -----------------------------------------------------------------*/
#define HSM_LED_EVENT_BUFFER_SIZE   (3)


/* Function Prototypes -------------------------------------------------------*/
static void Led_State_Initial(hsmLed_Hsm *me, hsm_Event const *e);
static void Led_State_LedOn(hsmLed_Hsm *me, hsm_Event const *e);
static void Led_State_LedOff(hsmLed_Hsm *me, hsm_Event const *e);
static void Led_State_BlinkOn(hsmLed_Hsm *me, hsm_Event const *e);
static void Led_State_BlinkOff(hsmLed_Hsm *me, hsm_Event const *e);

static void SetLedOn(void);
static void SetLedOff(void);
static void TimerCallback(void * hsm);


/* Public Functions ----------------------------------------------------------*/
void hsmLed_Ctor( hsmLed_Hsm * me, uint32_t evt_buf_n_elem){
	hsm_Ctor(&me->base, (hsm_State) Led_State_Initial);
	me->evt_queue = queue_Constructor(evt_buf_n_elem, sizeof(hsmLed_Event));
	me->blink_timer = swtimer_Constructor();
}

void hsmLed_Init(hsmLed_Hsm * me){
	hsm_Init(&me->base);
}

void hsmLed_Run(hsmLed_Hsm * me){
	bool res;
	static hsmLed_Event evt;
	res = queue_Dequeue( me->evt_queue, &evt);
	if(res){
		hsm_Dispatch(&me->base, &evt.base);
	}
}

void hsmLed_SendEvent( hsmLed_Hsm * me, hsmLed_Event * evt ){
	queue_Enqueue( me->evt_queue, evt );
}




/* States Functions ----------------------------------------------------------*/

static void Led_State_Initial(hsmLed_Hsm *me, hsm_Event const *e) {    
	  switch (e->signal) {
		case hsmLed_INIT_SIG:
				hsm_Transition((hsm_Hsm*) me, (hsm_State) Led_State_LedOn);
				break;
    }
}

static void Led_State_LedOn(hsmLed_Hsm *me, hsm_Event const *e) {
    switch (e->signal) {
		case hsmLed_ENTRY_SIG:
				SetLedOn();
				break;
    case hsmLed_BUTT_PRESSED_SIG:
				swtimer_Start(me->blink_timer, 100, true, TimerCallback, me);
        hsm_Transition((hsm_Hsm*) me, (hsm_State) Led_State_BlinkOff);
        break;
    }
}

static void Led_State_LedOff(hsmLed_Hsm *me, hsm_Event const *e) {
    switch (e->signal) {
		case hsmLed_ENTRY_SIG:
				SetLedOff();
				swtimer_Stop(me->blink_timer);
				break;
    case hsmLed_BUTT_PRESSED_SIG:
        hsm_Transition((hsm_Hsm*) me, (hsm_State) Led_State_LedOn);
        break;
    }
}

static void Led_State_BlinkOff(hsmLed_Hsm *me, hsm_Event const *e) {
    switch (e->signal) {
		case hsmLed_ENTRY_SIG:
				SetLedOff();
				break;
    case hsmLed_BUTT_PRESSED_SIG:
        hsm_Transition((hsm_Hsm*) me, (hsm_State) Led_State_LedOff);
        break;
		case hsmLed_TIMEOUT_BLINK_SIG:
        hsm_Transition((hsm_Hsm*) me, (hsm_State) Led_State_BlinkOn);
        break;
    }
}

static void Led_State_BlinkOn(hsmLed_Hsm *me, hsm_Event const *e) {
    switch (e->signal) {
		case hsmLed_ENTRY_SIG:
				SetLedOn();
				break;
    case hsmLed_BUTT_PRESSED_SIG:
        hsm_Transition((hsm_Hsm*) me, (hsm_State) Led_State_LedOff);
        break;
		case hsmLed_TIMEOUT_BLINK_SIG:
        hsm_Transition((hsm_Hsm*) me, (hsm_State) Led_State_BlinkOff);
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
	static hsmLed_Event led_evt;
	hsm_EventSetSignal(&led_evt.base, hsmLed_TIMEOUT_BLINK_SIG);
	hsmLed_SendEvent( (hsmLed_Hsm*)data, &led_evt );
}
