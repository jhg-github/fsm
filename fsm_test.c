#include "fsm_test.h"
#include "fsm_led.h"
#include "main.h"

/**
 * Call this from main
 */
void fsm_test(void){
    fsm_LedFsm led_fsm;
    fsm_LedEvt led_evt;

    LedCtor(&led_fsm);
    fsm_FsmInit((fsm_Fsm *)&led_fsm, 0);

    while(1){
        led_evt.base.sig = fsm_led_TURN_ON_SIG;
        fsm_FsmDispatch((fsm_Fsm *)&led_fsm, (fsm_Event *)&led_evt);
        HAL_Delay(500);
        led_evt.base.sig = fsm_led_TURN_OFF_SIG;
        fsm_FsmDispatch((fsm_Fsm *)&led_fsm, (fsm_Event *)&led_evt);
        HAL_Delay(50);
    }
}
