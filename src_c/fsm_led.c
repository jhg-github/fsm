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
void LedCtor( fsmLed_Fsm * me) {
	fsm_Ctor(&me->base, (fsm_State) Led_initial);
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
