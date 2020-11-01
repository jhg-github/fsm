#include "fsm_test.h"
#include "fsm_led.h"


/**
 * Call this from main
 */
void fsm_test(void){
    Led led_fsm;
    LedEvt led_evt;

    LedCtor(&led_fsm);
    FsmInit(&led_fsm, 0);

    while(1){
        led_evt.super_.sig = TURN_ON_SIG;
        FsmDispatch((Fsm *)&led_fsm, (Event *)&led_evt);
        HAL_Delay(100);
        led_evt.super_.sig = TURN_OFF_SIG;
        FsmDispatch((Fsm *)&led_fsm, (Event *)&led_evt);
        HAL_Delay(500);
    }
}
