/* Includes ------------------------------------------------------------------*/
#include "fsm_test.h"
#include "fsm_led.h"
#include "main.h"
#include "assert.h"
#include "static_allocator.h"


/**
 * Call this from main
 */
void fsm_test(void){
	fsmLed_Fsm led_fsm;
	fsmLed_Event led_evt;

	LedCtor(&led_fsm);
	fsm_Init((fsm_Fsm *)&led_fsm, 0);

	while(1){
		fsm_EventSetSignal((fsm_Event *)&led_evt, fsmLed_TURN_ON_SIG);
		fsm_Dispatch((fsm_Fsm *)&led_fsm, (fsm_Event *)&led_evt);
		HAL_Delay(50);
		fsm_EventSetSignal((fsm_Event *)&led_evt, fsmLed_TURN_OFF_SIG);
		fsm_Dispatch((fsm_Fsm *)&led_fsm, (fsm_Event *)&led_evt);
		HAL_Delay(50);
	}
}
