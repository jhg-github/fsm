#include "fsm_led.h"
#include "main.h"

void SetLedOn(void) {
    HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_SET);
}
void SetLedOff(void) {
    HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);
}

void LedCtor(Led *me) {
//    FsmCtor_(&me->super_, &Led_initial);
    FsmCtor_(&me->super_, (State) Led_initial);
}

void Led_initial(Led *me, Event const *e) {
    SetLedOn();
//    FsmTran_((Fsm *)me, &Led_on);
    FsmTran_((Fsm*) me, (State) Led_on);
}

void Led_on(Led *me, Event const *e) {
    switch (e->sig) {
    case TURN_OFF_SIG:
        SetLedOff();
//        FsmTran_((Fsm *)me, &Led_off);
        FsmTran_((Fsm*) me, (State) Led_off);
        break;
    }
}

void Led_off(Led *me, Event const *e) {
    switch (e->sig) {
    case TURN_ON_SIG:
        SetLedOn();
//        FsmTran_((Fsm *)me, &Led_on);
        FsmTran_((Fsm*) me, (State) Led_on);
        break;
    }
}
