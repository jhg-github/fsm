#include "fsm_led.h"
#include "main.h"


/* Function Prototypes -------------------------------------------------------*/
static void Led_initial(fsm_LedFsm *me, fsm_Event const *e);
static void Led_on(fsm_LedFsm *me, fsm_Event const *e);
static void Led_off(fsm_LedFsm *me, fsm_Event const *e);
static void SetLedOn(void);
static void SetLedOff(void);


/* Public Functions ----------------------------------------------------------*/
void LedCtor(fsm_LedFsm *me) {
//    FsmCtor_(&me->super_, &Led_initial);
    fsm_FsmCtor(&me->base, (fsm_State) Led_initial);
}


/* Private Functions ---------------------------------------------------------*/

static void SetLedOn(void) {
    HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_SET);
}
static void SetLedOff(void) {
    HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);
}



static void Led_initial(fsm_LedFsm *me, fsm_Event const *e) {
    SetLedOn();
//    FsmTran_((Fsm *)me, &Led_on);
    fsm_FsmTransition((fsm_Fsm*) me, (fsm_State) Led_on);
}

static void Led_on(fsm_LedFsm *me, fsm_Event const *e) {
    switch (e->sig) {
    case fsm_led_TURN_OFF_SIG:
        SetLedOff();
//        FsmTran_((Fsm *)me, &Led_off);
        fsm_FsmTransition((fsm_Fsm*) me, (fsm_State) Led_off);
        break;
    }
}

static void Led_off(fsm_LedFsm *me, fsm_Event const *e) {
    switch (e->sig) {
    case fsm_led_TURN_ON_SIG:
        SetLedOn();
//        FsmTran_((Fsm *)me, &Led_on);
        fsm_FsmTransition((fsm_Fsm*) me, (fsm_State) Led_on);
        break;
    }
}
